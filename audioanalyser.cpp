#include "audioanalyser.h"

AudioAnalyser::AudioAnalyser()
{

    m_sndBuffer = new sf::SoundBuffer();
    m_sound = new sf::Sound();

    m_winSize = 1024; // window size
    m_hopSize = m_winSize / 4; // hop size
    m_samplerate = 44100; // samplerate

    m_noiseThreshold = 50;
    m_minBestNoteCount = 10;

    //create pitch object
    m_aubioPitchObject = new_aubio_pitch ("fcomb", m_winSize, m_hopSize, m_samplerate);
    //Create tss object
    //m_aubioTssObject = new_aubio_tss(m_winSize,m_hopSize);

}

std::vector<NoteData> * AudioAnalyser::loadSound(std::string _filePath){
    QDir dir;
    std::string path = dir.currentPath().toStdString()+"/"+_filePath;
    qDebug() << path.c_str();

    bool res = false;
    try{
        res = m_sndBuffer->loadFromFile(path);
    }catch( std::exception & e){
        qDebug() << e.what();
    }

    if( res ){
        qDebug() << "Succeeded To Load File";
        m_sound = new sf::Sound();
        m_sound->setBuffer(*m_sndBuffer);
        processSound();
        //sound->play();
    }else{
        qDebug() << "Failed To Load File";
    }
    return m_notes;
}

void AudioAnalyser::processSound(){

    //Go through the entire audio and process sample frames
    const short int* samples = m_sndBuffer->getSamples();
    m_totalSize = m_sndBuffer->getSampleCount();

    findNotes(samples);
}

/**
 * Process the window frame a find the note
 */
int AudioAnalyser::computeNote(fvec_t * _frameSample){

    fvec_t *out = new_fvec (1); // output candidates

    //do the pitch detection process
    aubio_pitch_do(m_aubioPitchObject,_frameSample,out);

    float pitch = out->data[0];
    if( pitch > 1000)
        pitch = pitch / 100;
    int note = log( pitch/440.0)/log(2) * 12 + 69;

    //qDebug() << "pitch " << pitch << "; note " << note;

    del_fvec(out);
    return note;
}

void AudioAnalyser::findNotes(const short int * _audio){

    m_notes = new std::vector<NoteData>();
    // create a vector to hold each frame sample of m_hopSize length
    fvec_t *input = new_fvec (m_hopSize); // input buffer

    //index of the current signal value
    int index = 0;
    //Length counter of the current sample
    int curSampleCount = 0;

    NoteData * curNote = new NoteData();
    std::map<std::string,int> * notesBufferCount = new std::map<std::string,int>();


    //go through every audio value
    while(index < m_totalSize ){
        curSampleCount++;
        index++;
        //store a frame of m_hopSize length as input
        input->data[curSampleCount] = *(_audio + index);
        //when we have filled the input data
        if( curSampleCount >= (int) m_hopSize ){
            curSampleCount =0;

            //compute average db level of the sample
            smpl_t db = aubio_level_detection(input,0);
            //qDebug() << db << "  " << index;

            //if the value of db is high enough
            if( db > m_noiseThreshold){
                //compute note for this frame sample
                int newNote = computeNote(input);

                //qDebug() << "db " << db << " at " << (index-m_hopSize) ;
                //here we have a potential note
                //if a note has already began ( no silence )
                if( curNote->begin >=0 ){
                    //check if the note hasn't changed
                    //1.if(note has changed){
                    //2.store currentNote
                    //3.begin a new one

                //if this is a new note after a silence
                }else{
                    //Begin new note
                    curNote->begin = index;
                    curNote->note = newNote;
                    notesBufferCount->clear();
                }

                //note count for this frame
                std::string noteS = std::to_string(newNote);
                if( (*notesBufferCount)[noteS] == 0)
                    (*notesBufferCount)[noteS] = 1;
                else
                    (*notesBufferCount)[noteS]++;

            //if this is the end of an note ( = new silence as though a note was playing )
            }else {
                //end of a note
                if(curNote->begin >=0){
                    qDebug() << "END NOTE";
                    curNote->end = index;
                    //build new note a store it
                    storeNote(curNote,notesBufferCount);
                    //reset curNote
                    curNote->begin = -1;
                }
            }
        }
    }
    //delete curNote;
    //delete notesBufferCount;
    del_fvec(input);
}

//Store new note in the array ( a copy of the node is made )
void AudioAnalyser::storeNote(NoteData * _inputNote, std::map<std::string,int> * _notesBufferCount ){
    //we have stored notes values found by pitch,
    //now we want the best one ( most found )
    int bestNote = findBestNote(_notesBufferCount);
    if( bestNote < 0 ){
        return;
    }

    NoteData * newNoteData = new NoteData();
    //sample rate for time calculation
    newNoteData->setSampleRate(m_samplerate);
    //note frame
    newNoteData->begin = _inputNote->begin;
    newNoteData->end = _inputNote->end;
    newNoteData->note = bestNote;
    m_notes->push_back(*newNoteData);

    qDebug() << "note " << newNoteData->begin << " " << newNoteData->end <<" " << newNoteData->note;

    _notesBufferCount->clear();
}

int AudioAnalyser::getTotalSize(){
    return m_totalSize;
}

AudioAnalyser::~AudioAnalyser()
{
    del_aubio_pitch( m_aubioPitchObject);
    //del_aubio_tss(m_aubioTssObject);
}

//=========== UTILS ====================

// Put _input values in _output
void AudioAnalyser::fillInputData( short int * _input, fvec_t * _output, int _count){
    int i = 0;
    short int temp;
    while(i < _count){
        temp = *(_input+i);
        _output->data[i] = temp;
        i++;
    }
}

// Find best note within the ones stored for the current frame ( with max count )
int AudioAnalyser::findBestNote(std::map<std::string,int> * _map){
    int maxNoteCount = 0;
    std::string noteS = "-1";
    std::map<std::string,int>::iterator it;
    for( it = _map->begin(); it != _map->end(); it++){
        //qDebug() << "note : " << it->first.c_str() << " count : " << it->second;
        if( it->second > maxNoteCount && it->second >= m_minBestNoteCount ){
            maxNoteCount = it->second;
            noteS = it->first;
            qDebug() << "note : " << it->first.c_str() << " count : " << it->second;
        }
    }
    return atoi(noteS.c_str());
}

int AudioAnalyser::findMaxAbs(fvec_t * _vec, int _length){
    int i=0; int maxIndex = -1;
    float f = 0; float max = 0;
    while(i < _length){
        f = _vec->data[i];
        f = abs(f);
        if( f > max ){
            max = f;
            maxIndex = 0;
        }
        i++;
    }
    return maxIndex;
}


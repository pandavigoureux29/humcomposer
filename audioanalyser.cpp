#include "audioanalyser.h"

AudioAnalyser::AudioAnalyser()
{

    m_sndBuffer = new sf::SoundBuffer();
    m_sound = new sf::Sound();

    m_winSize = 1024; // window size
    m_hopSize = m_winSize / 4; // hop size
    m_samplerate = 44100; // samplerate

    m_noiseTreshold = 30;

    //create pitch object
    m_aubioPitchObject = new_aubio_pitch ("fcomb", m_winSize, m_hopSize, m_samplerate);
    //Create tss object
    m_aubioTssObject = new_aubio_tss(m_winSize,m_hopSize);

}

void AudioAnalyser::loadSound(){
    QDir dir;
    std::string path = dir.currentPath().toStdString()+"/la.wav";

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
}

void AudioAnalyser::processSound(){

    //Go through the entire audio and process sample frames
    const short int* samples = m_sndBuffer->getSamples();
    int totalSize = m_sndBuffer->getSampleCount();

    findNotes(samples,totalSize);
}

/**
 * Process the window frame a find the note
 */
int AudioAnalyser::computeNote(fvec_t * _frameSample, int _count){

    fvec_t *out = new_fvec (1); // output candidates

    //do the pitch detection process
    aubio_pitch_do(m_aubioPitchObject,_frameSample,out);

    float pitch = out->data[0];
    if( pitch > 1000)
        pitch = pitch / 100;
    int note = log( pitch/440.0)/log(2) * 12 + 69;

    qDebug() << "pitch " << pitch << "; note " << note;

    del_fvec(out);
    return note;
}

void AudioAnalyser::findNotes(const short int * _audio,int _length){

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
    while(index < _length ){
        curSampleCount++;
        index++;
        //store a frame of m_hopSize length as input
        input->data[curSampleCount] = *(_audio + index);
        //when we have filled the input data
        if( curSampleCount >= m_hopSize ){
            curSampleCount =0;

            //compute average db level of the sample
            smpl_t db = aubio_level_detection(input,0);

            //if the value of db is high enough
            if( db > m_noiseTreshold){
                //compute note for this frame sample
                int newNote = computeNote(input,m_hopSize);

                //qDebug() << "db " << db << " at " << (index-m_hopSize) ;
                //here we have a potential note
                //if a note has already began
                if( curNote->begin >=0 ){
                    //do nothing
                //if this is a new note
                }else{
                    //store the last one
                    //HERE TO DO

                    //Begin new note
                    curNote->begin = index;
                    curNote->note = newNote;
                }

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
                    int bestNote = findMaxCountNote(notesBufferCount);
                    //build new note
                    NoteData * newNoteData = new NoteData();
                    newNoteData->begin = curNote->begin;
                    newNoteData->end = curNote->end;
                    newNoteData->note = bestNote;
                    m_notes->push_back(*newNoteData);
                    qDebug() << "note " << newNoteData->note;
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

AudioAnalyser::~AudioAnalyser()
{
    del_aubio_pitch( m_aubioPitchObject);
    del_aubio_tss(m_aubioTssObject);
}

//=========== UTILS ====================


void AudioAnalyser::fillInputData( short int * _input, fvec_t * _output, int _count){
    int i = 0;
    short int temp;
    while(i < _count){
        temp = *(_input+i);
        _output->data[i] = temp;
        i++;
    }
}

int AudioAnalyser::findMaxCountNote(std::map<std::string,int> * _map){
    int maxNoteCount = 0;
    std::string noteS = "-1";
    std::map<std::string,int>::iterator it;
    for( it = _map->begin(); it != _map->end(); it++){
        if( it->second > maxNoteCount ){
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


#include "audioanalyser.h"
#include "controllers/maincontroller.h"

AudioAnalyser::AudioAnalyser(MainController * _mainCtrl)
{
    m_mainController = _mainCtrl;

    m_notesBufferCount = new std::map<std::string,int>();
    m_notes = new std::vector<NoteData>();

    m_winSize = 512; // window size
    m_hopSize = m_winSize / 4; // hop size
    m_samplerate = 44100; // samplerate

    m_noiseThreshold = 10;
    m_minBestNoteCount = 10;

    //create pitch object
    m_aubioPitchObject = new_aubio_pitch ("fcomb", m_winSize, m_hopSize, m_samplerate);

    //Create tss object
    //m_aubioTssObject = new_aubio_tss(m_winSize,m_hopSize);

    //shift check variables
    m_shiftCheckErrorCount =0; //count the error shift
    m_shiftCheckRange = 15; // the shift checking must be done on 20 conscutive values
    m_shiftCheckBuffer = new std::map<std::string,int>();

}


std::vector<NoteData> * AudioAnalyser::processSound(std::vector<short int> * _samples){
    //m_notes->clear();

    qDebug() << m_noiseThreshold;

    m_totalSize = _samples->size();
    //Go through the entire audio and process sample frames
    findNotes(_samples);

    return m_notes;
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

/**
 * Procss the entitre audio sample to find notes
 */
void AudioAnalyser::findNotes(std::vector<short int> * _audio){

    m_notes->clear();
    m_notesBufferCount->clear();
    // create a vector to hold each frame sample of m_hopSize length
    fvec_t *input = new_fvec (m_hopSize); // input buffer

    //index of the current signal value
    int index = 0;
    //Length counter of the current sample
    int curSampleCount = 0;

    NoteData * curNote = new NoteData();

    //go through every audio value
    while(index < _audio->size() -1 ){
        curSampleCount++;
        index++;
        //store a frame of m_hopSize length as input
        input->data[curSampleCount] = _audio->at(index);
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

                //qDebug() << "db " << db << " at " << ((float)index-m_hopSize)/(float)44100 << " n:" << newNote ;
                //here we have a potential note
                //if a note has already began ( no silence )
                if( curNote->begin >=0 ){
                    bool shifted = shiftCheck(newNote,index);
                    //check if the note hasn't changed
                    //if(note has changed){
                    //qDebug() << " BEST" << bestNote;
                    if( shifted ){
                        qDebug() << " SHIFTED ";
                        //1.store note
                        curNote->end = m_shiftBeginIndex;
                        storeNote(curNote);
                        curNote->begin = -1;
                        //2.begin a new one
                        curNote->begin = m_shiftBeginIndex;
                        curNote->note = 0;
                    }
                //if this is a new note after a silence
                }else{
                    //Begin new note
                    curNote->begin = index;
                    curNote->note = newNote;
                }

                //note count for this frame
                std::string noteS = std::to_string(newNote);
                if( (*m_notesBufferCount)[noteS] == 0)
                    (*m_notesBufferCount)[noteS] = 1;
                else
                    (*m_notesBufferCount)[noteS]++;

            //if this is the end of an note ( = new silence as though a note was playing )
            }else {
                //end of a note
                if(curNote->begin >=0){
                    //qDebug() << "END NOTE";
                    curNote->end = index;
                    //build new note a store it
                    storeNote(curNote);
                    //reset curNote
                    curNote->begin = -1;
                }
            }
        }
    }

    //check for last note ( in case the sound didn't end with a silence )
    if( curNote->begin > 0 ){
        int bestEndNote = findBestNote(m_notesBufferCount,m_minBestNoteCount);
        curNote->end = m_totalSize-1;
        storeNote(curNote);
    }
    //delete curNote;
    //delete m_notesBufferCount;
    del_fvec(input);
}

//Store new note in the array ( a copy of the node is made )
void AudioAnalyser::storeNote(NoteData * _inputNote ){
    //we have stored notes values found by pitch,
    //now we want the best one ( most found )
    int bestNote = findBestNote(m_notesBufferCount,m_minBestNoteCount);
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

    m_notesBufferCount->clear();
}


/**
 * Checks if the note is shifting while playing
 * Actually checks if the sound playing is changing pitch while maintaining a constant db
 * As notes regularly variates, even within a same note, we need to do this process within a given range
 */
bool AudioAnalyser::shiftCheck(int _newNote,int _index){
    bool shifted = false;
    int currentBestNote = findBestNote(m_notesBufferCount,1);
    if( currentBestNote > 0){
        m_shiftBeginIndex = _index;
        m_shiftCheckCount ++;
        if( m_shiftCheckCount > m_shiftCheckRange ){
            int tempBestNote = findBestNote(m_shiftCheckBuffer,m_shiftCheckRange * 0.3);
            qDebug() << "SC best : " << tempBestNote << "against "<< currentBestNote << " at " << m_shiftBeginIndex;
            m_shiftCheckBuffer->clear();
            m_shiftCheckCount = 0;
            shifted = (tempBestNote != currentBestNote);
        }else{
            //note count for this frame
            std::string noteS = std::to_string(_newNote);
            if( (*m_shiftCheckBuffer)[noteS] == 0)
                (*m_shiftCheckBuffer)[noteS] = 1;
            else
                (*m_shiftCheckBuffer)[noteS]++;
        }
    }
    return shifted;
}

void AudioAnalyser::processAllNotes(std::vector<int> * _allNotes){

}

int AudioAnalyser::getTotalSize(){
    return m_totalSize;
}

AudioAnalyser::~AudioAnalyser()
{
    del_aubio_pitch( m_aubioPitchObject);
}


//=========== SETTERS / GETTERS =========

int AudioAnalyser::getNoiseThreshold(){
    return m_noiseThreshold;
}

void AudioAnalyser::setNoiseThreshold(int _value){
    m_noiseThreshold = _value;
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
int AudioAnalyser::findBestNote(std::map<std::string,int> * _map, int _minimumCount){
    int maxNoteCount = 0;
    std::string noteS = "-1";
    std::map<std::string,int>::iterator it;
    for( it = _map->begin(); it != _map->end(); it++){
        //qDebug() << "note : " << it->first.c_str() << " count : " << it->second;
        if( it->second > maxNoteCount && it->second >= _minimumCount ){
            maxNoteCount = it->second;
            noteS = it->first;
            //qDebug() << "note : " << it->first.c_str() << " count : " << it->second;
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


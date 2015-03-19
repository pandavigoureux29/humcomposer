#ifndef AUDIOANALYSER_H
#define AUDIOANALYSER_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QDir>
#include <math.h>
#include <map>

#include "notedata.h"
#include "aubio/aubio.h"


class MainController;

class AudioAnalyser
{
public:
    AudioAnalyser(MainController * _mainCtrl);
    ~AudioAnalyser();

    /**
     * Proccess buffers samples and create notes data
     */
    std::vector<NoteData> * processSound(std::vector<short int> * samples);
    int getTotalSize();
    void setNoiseThreshold(int value);
    int getNoiseThreshold();

private:
    MainController * m_mainController;
    short int * m_audio_sample ;

    /**
     * Fill the output fvec_t with values stored in input
     */
    void fillInputData( short int * input, fvec_t * output, int count);

    /**
     * Compute the note by pitch of the sample
     */
    int computeNote(fvec_t * frameSample);

    /**
     * Find notes in the audio sample provided
     */
    void findNotes(std::vector<short int> * audio);
    bool shiftCheck(int newNote,int _index);

    void processAllNotes(std::vector<int> * allNotes);

    void storeNote(NoteData * inputNote);

    //Aubio related variables
    uint_t m_winSize ; // window size
    uint_t m_hopSize ; // hop size
    uint_t m_samplerate ; // samplerate

    //the minimum value that will tell us if a note is considered as played
    int m_minBestNoteCount;
    //under the noise threshold db, we judge the sample audio as silent
    int m_noiseThreshold;

    //Shift Checking variables
    int m_shiftCheckRange;
    int m_shiftCheckCount;
    int m_shiftCheckErrorCount;
    int m_shiftBeginIndex ;
    int m_shiftBeginNote;
    std::map<std::string,int> * m_shiftCheckBuffer;

    std::vector<NoteData> * m_notes;
    std::map<std::string,int> * m_notesBufferCount;
    int m_totalSize;

    aubio_pitch_t * m_aubioPitchObject;
    //aubio_tss_t * m_aubioTssObject;

    //UTILS
    /**
     */
    int findMaxAbs(fvec_t * vec, int length);
    int findBestNote(std::map<std::string,int> * _map,int minimumCount);
};

#endif // AUDIOANALYSER_H

#ifndef AUDIOANALYSER_H
#define AUDIOANALYSER_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QDir>
#include <SFML/Audio.hpp>
#include <math.h>
#include <map>

#include "notedata.h"
#include "aubio/aubio.h"

class AudioAnalyser
{
public:
    AudioAnalyser();
    ~AudioAnalyser();
    std::vector<NoteData> * loadSound();
    int getTotalSize();

private:
    sf::SoundBuffer * m_sndBuffer;
    sf::Sound * m_sound;
    short int * m_audio_sample ;

    void processSound();
    void createAudioSample();
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
    void findNotes(const short int * audioSample);

    void storeNote(NoteData * inputNote,std::map<std::string,int> * notesBufferCount);

    //Aubio related variables
    uint_t m_winSize ; // window size
    uint_t m_hopSize ; // hop size
    uint_t m_samplerate ; // samplerate

    //the minimum value that will tell us if a note is considered as played
    int m_minBestNoteCount;
    //under the noise threshold db, we judge the sample audio as silent
    int m_noiseThreshold;

    std::vector<NoteData> * m_notes;
    int m_totalSize;

    aubio_pitch_t * m_aubioPitchObject;
    //aubio_tss_t * m_aubioTssObject;

    //UTILS
    /**
     */
    int findMaxAbs(fvec_t * vec, int length);
    int findBestNote(std::map<std::string,int> * _map);
};

#endif // AUDIOANALYSER_H

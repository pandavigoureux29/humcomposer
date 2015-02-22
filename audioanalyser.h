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
    void loadSound();

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
    int computeNote(fvec_t * frameSample, int count);
    /**
     * Find notes in the audio sample provided
     */
    void findNotes(const short int * audioSample, int length);

    uint_t m_winSize ; // window size
    uint_t m_hopSize ; // hop size
    uint_t m_samplerate ; // samplerate

    int m_noiseTreshold;

    std::vector<NoteData> * m_notes;

    aubio_pitch_t * m_aubioPitchObject;
    aubio_tss_t * m_aubioTssObject;

    //UTILS
    /**
     */
    int findMaxAbs(fvec_t * vec, int length);
    int findMaxCountNote(std::map<std::string,int> * _map);
};

#endif // AUDIOANALYSER_H

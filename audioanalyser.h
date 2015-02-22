#ifndef AUDIOANALYSER_H
#define AUDIOANALYSER_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QDir>
#include <SFML/Audio.hpp>
#include <math.h>

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
    void fillInputData( short int * input, fvec_t * output, int count);
    void processFrame(short int * frameSample, int count);
    void findVoices(const short int * audioSample, int length);

    uint_t m_winSize ; // window size
    uint_t m_hopSize ; // hop size
    uint_t m_samplerate ; // samplerate

    aubio_pitch_t * m_aubioPitchObject;
};

#endif // AUDIOANALYSER_H

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "tracksmanager.h"
#include "audioanalyser.h"
#include "midicomposer.h"
#include "midiplayer.h"

class MainController
{
public:
    MainController();
    ~MainController();
    void analyseSound(const short int * samples, int length);
    void buildMidiToTrack();
    void playMidi();


private :
    AudioAnalyser * m_audioAnalyser;
    MidiComposer * m_midiComposer;
    TracksManager * m_tracksManager;
    MidiPlayer * m_midiPlayer;
};

#endif // MAINCONTROLLER_H

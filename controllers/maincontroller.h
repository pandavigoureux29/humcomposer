#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "tracksmanager.h"
#include "audioanalyser.h"
#include "midicomposer.h"
#include "midiplayer.h"

class MainWindow;

class MainController
{
public:
    MainController(MainWindow * mainWindow);
    ~MainController();
    void analyseSound(const short int * samples, int length);
    void buildMidiToTrack();
    void playMidi();
    void stopMidi();

    //callbacks
    void onMainWindowReady();
    void onSoundAnalyseComplete();
    void onTrackAdded(unsigned int id);


private :
    MainWindow * m_mainWindow;

    AudioAnalyser * m_audioAnalyser;
    MidiComposer * m_midiComposer;
    TracksManager * m_tracksManager;
    MidiPlayer * m_midiPlayer;
};

#endif // MAINCONTROLLER_H

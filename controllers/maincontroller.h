#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "tracksmanager.h"
#include "audioanalyser.h"
#include "midicomposer.h"
#include "midiplayer.h"

class MainWindow;
class UIRecorder;

class MainController
{
public:
    MainController(MainWindow * mainWindow);
    ~MainController();
    void analyseSound(const short int * samples, int length, UIRecorder * _recorder=0);
    void buildMidiToTrack();
    void playMidi();
    void stopMidi();

    //callbacks
    void onMainWindowReady();
    void onSoundAnalyseComplete();
    void onTrackAdded(unsigned int id);


    //getters
    AudioAnalyser * getAudioAnalyser();


private :
    MainWindow * m_mainWindow;

    AudioAnalyser * m_audioAnalyser;
    MidiComposer * m_midiComposer;
    TracksManager * m_tracksManager;
    MidiPlayer * m_midiPlayer;
};

#endif // MAINCONTROLLER_H

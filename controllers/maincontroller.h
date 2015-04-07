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
    void analyseSound(std::vector<short int> * samples, UIRecorder * _recorder=0);
    void buildMidiToTrack();
    void playMidi();
    void stopMidi();

    void playTrack(Track * _track);

    //callbacks
    void onMainWindowReady();
    void onSoundAnalyseComplete();
    void onTrackAdded(unsigned int id);


    //getters
    AudioAnalyser * getAudioAnalyser();
    QString getDefaultFolder();
    QString getProjectFolder();

private :
    MainWindow * m_mainWindow;

    AudioAnalyser * m_audioAnalyser;
    MidiComposer * m_midiComposer;
    TracksManager * m_tracksManager;
    MidiPlayer * m_midiPlayer;

    //project
    QString m_defaultFolder;
    QString m_projectFolder;
};

#endif // MAINCONTROLLER_H

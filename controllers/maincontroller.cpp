#include "maincontroller.h"
#include "mainwindow.h"
#include "ui/uirecorder.h"

MainController::MainController(MainWindow * _mainWindow)
{
    m_mainWindow = _mainWindow;

    m_midiComposer = new MidiComposer(this);
    m_audioAnalyser = new AudioAnalyser(this);
    m_tracksManager = new TracksManager(this);
    m_midiPlayer = new MidiPlayer(this);

    m_defaultFolder = "UntitledProject";
}

void MainController::analyseSound(std::vector<short int> * samples,UIRecorder * _recorder){
    //std::vector< NoteData > * vecNotes = m_audioAnalyser->loadSound("sound.wav");
    //qDebug() << "vecnoteSize " << vecNotes->size();

    //Process samples to find notes
    std::vector< NoteData > * vecNotes = m_audioAnalyser->processSound(samples);
    qDebug() << "vecnoteSize " << vecNotes->size() ;

    int trackID = 0;

    //if no note found, this is a fail
    if( vecNotes->size() == 0 ){
        _recorder->onAnalyseFailed();
    }else{
        //send the notes to the track 0 (first) and refresh it (also temporary)
        m_tracksManager->buildMidiToTrack(trackID,vecNotes);
        //build the midi file
        //( temporary. We should build the entire track, not just the curren notes)
        m_midiComposer->buildMidiTrackFromData(m_tracksManager->getTrack(trackID),m_audioAnalyser->getTotalSize());
        m_mainWindow->refreshTrack(0);
    }
}

void MainController::playMidi(){
    m_midiPlayer->play("compo.mid");
}

void MainController::stopMidi(){
    m_midiPlayer->stop();
}

void MainController::playTrack(Track * _track){
    m_midiPlayer->playTrack(_track);
}

//============================================
//              CALLBACKS
//============================================

void MainController::onMainWindowReady(){
    m_tracksManager->addTrack();
}

void MainController::onSoundAnalyseComplete(){
    qDebug() << "ANAL COMPLETE";
}

//Called by TracksManager when a new track is added
void MainController::onTrackAdded(unsigned int _id){
   qDebug() << "[MC] track "<<_id<<" added";
   //proceed to add a UITrack
   m_mainWindow->addTrack(m_tracksManager->getTrack(_id));
}

//============================================
//              GETTERS
//============================================

AudioAnalyser * MainController::getAudioAnalyser(){
    return m_audioAnalyser;
}

QString MainController::getDefaultFolder(){
    return m_defaultFolder;
}

QString MainController::getProjectFolder(){
    if( m_projectFolder != NULL && m_projectFolder != "")
        return m_projectFolder;
    return m_defaultFolder;
}

MainController::~MainController()
{

}


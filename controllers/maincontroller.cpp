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
}

void MainController::analyseSound(const short int * _buffer,int _length,UIRecorder * _recorder){
    //std::vector< NoteData > * vecNotes = m_audioAnalyser->loadSound("sound.wav");
    //qDebug() << "vecnoteSize " << vecNotes->size();
    std::vector< NoteData > * vecNotes = m_audioAnalyser->processSound(_buffer,_length);
    qDebug() << "vecnoteSize " << vecNotes->size() ;

    if( vecNotes->size() == 0 ){
        _recorder->onAnalyseFailed();
    }else{
        m_midiComposer->buildMidiFromData(vecNotes,m_audioAnalyser->getTotalSize());
        m_tracksManager->buildMidiToTrack(0,vecNotes);
        m_mainWindow->refreshTrack(0);
    }
}

void MainController::playMidi(){
    m_midiPlayer->play("compo.mid");
}

void MainController::stopMidi(){
    m_midiPlayer->stop();
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

void MainController::onTrackAdded(unsigned int _id){
   qDebug() << "[MC] track "<<_id<<" added";
   m_mainWindow->addTrack(m_tracksManager->getTrack(_id));
}

//============================================
//              GETTERS
//============================================

AudioAnalyser * MainController::getAudioAnalyser(){
    return m_audioAnalyser;
}

MainController::~MainController()
{

}


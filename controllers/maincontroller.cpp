#include "maincontroller.h"

MainController::MainController()
{

    m_midiComposer = new MidiComposer();
    m_audioAnalyser = new AudioAnalyser();
    m_tracksManager = new TracksManager();
    m_midiPlayer = new MidiPlayer();
    playMidi();
}

void MainController::analyseSound(const short int * _buffer,int _length){
    std::vector< NoteData > * vecNotes = m_audioAnalyser->loadSound("sound.wav");
    qDebug() << "vecnoteSize " << vecNotes->size();
    //std::vector< NoteData > * vecNotes = m_audioAnalyser->processSound(_buffer,_length);
    //qDebug() << "vecnoteSize " << vecNotes->size();
    m_midiComposer->buildMidiFromData(vecNotes,m_audioAnalyser->getTotalSize());
}

void MainController::playMidi(){
    m_midiPlayer->play();
}

MainController::~MainController()
{

}


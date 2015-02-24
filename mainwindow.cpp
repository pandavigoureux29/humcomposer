#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_midiComposer = new MidiComposer();

    m_audioAnalyser = new AudioAnalyser();

    //ActionButtonsFrame * abFrame = new ActionButtonsFrame(this);

    //TRACKS
    QWidget * tracksPanel = new QWidget();
    QVBoxLayout * m_tracksLayout = new QVBoxLayout();
    //create a track
    UITrackFrame * trackPanel = new UITrackFrame();
    m_tracksLayout->addWidget(trackPanel);

    tracksPanel->setLayout(m_tracksLayout);

    //Set Central Widget
    this->setCentralWidget(tracksPanel);
    this->adjustSize();
}

void MainWindow::playMidi(){
    qDebug() << "play";
}

void MainWindow::analyseSound(){
    std::vector< NoteData > * vecNotes = m_audioAnalyser->loadSound("sound.wav");
    m_midiComposer->buildMidiFromData(vecNotes,m_audioAnalyser->getTotalSize());
}


void MainWindow::onRecordedFinished(int _track, sf::SoundBuffer _recorderBuffer){
    qDebug() << "SOUND RECORDED with samplecount = " << _recorderBuffer.getSampleCount();
}

MainWindow::~MainWindow()
{

}


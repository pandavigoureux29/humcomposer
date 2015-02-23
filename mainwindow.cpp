#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_midiComposer = new MidiComposer();

    m_audioAnalyser = new AudioAnalyser();

    ActionButtonsFrame * abFrame = new ActionButtonsFrame(this);
    this->setCentralWidget(abFrame);

    this->adjustSize();
}

void MainWindow::playMidi(){
    qDebug() << "play";
}

void MainWindow::analyseSound(){
    std::vector< NoteData > * vecNotes = m_audioAnalyser->loadSound();
    m_midiComposer->buildMidiFromData(vecNotes,m_audioAnalyser->getTotalSize());
}

MainWindow::~MainWindow()
{

}


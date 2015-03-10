#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_mainController = new MainController(this);
    m_tracks = std::vector<UITrackFrame*>();

    //Main widget holding tracks & audioRecorder
    QWidget * mainWidget = new QWidget();
    QVBoxLayout * mainLayout = new QVBoxLayout();

    //Buttons
    m_uiActionButtons = new UIActionButtonsFrame(this);
    mainLayout->addWidget(m_uiActionButtons);

    //TRACKS
    QWidget * tracksPanel = new QWidget();
    m_tracksLayout = new QVBoxLayout();

    tracksPanel->setLayout(m_tracksLayout);

    mainLayout->addWidget(tracksPanel);

    //Audio Recorder (frame at bottom)
    m_uiRecorder = new UIRecorder(m_mainController);
    mainLayout->addWidget(m_uiRecorder);

    //Set Central Widget
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
    this->adjustSize();

    m_mainController->onMainWindowReady();
}

//================= UI FUNCTIONS ====================

void MainWindow::addTrack(Track * _track){
    qDebug() << "Adding ui track" << (_track!=NULL);
    //create a track
    UITrackFrame * uiTrackFrame = new UITrackFrame(_track);
    m_tracksLayout->addWidget(uiTrackFrame);
    m_tracks.push_back(uiTrackFrame);
    uiTrackFrame->show();
}

void MainWindow::playMidi(){
    m_mainController->playMidi();
}

void MainWindow::stopMidi(){
    m_mainController->stopMidi();
}

void MainWindow::refreshTrack(unsigned int _trackID){
    m_tracks.at(_trackID)->refresh();
}

//==================CALLBACKS====================

void MainWindow::onRecordedFinished(int _track, sf::SoundBuffer _recorderBuffer){
    qDebug() << "SOUND RECORDED with samplecount = " << _recorderBuffer.getSampleCount();
}

MainWindow::~MainWindow()
{

}


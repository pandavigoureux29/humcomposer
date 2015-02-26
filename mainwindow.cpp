#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_mainController = new MainController();

    //Main widget holding tracks & audioRecorder
    QWidget * mainWidget = new QWidget();
    QVBoxLayout * mainLayout = new QVBoxLayout();

    //TRACKS
    QWidget * tracksPanel = new QWidget();
    QVBoxLayout * m_tracksLayout = new QVBoxLayout();
    //create a track
    UITrackFrame * trackPanel = new UITrackFrame();
    m_tracksLayout->addWidget(trackPanel);

    tracksPanel->setLayout(m_tracksLayout);

    mainLayout->addWidget(tracksPanel);

    //Audio Recorder (frame at bottom)
    m_uiRecorder = new UIRecorder();
    m_uiRecorder->setMainController(m_mainController);
    mainLayout->addWidget(m_uiRecorder);

    //Set Central Widget
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
    this->adjustSize();
}

//==================CALLBACKS====================

void MainWindow::onRecordedFinished(int _track, sf::SoundBuffer _recorderBuffer){
    qDebug() << "SOUND RECORDED with samplecount = " << _recorderBuffer.getSampleCount();
}

MainWindow::~MainWindow()
{

}


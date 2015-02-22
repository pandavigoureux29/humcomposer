#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //MainFrame *mainFrame = new MainFrame(this);
    //this->setCentralWidget(mainFrame);

    MidiComposer * midiComposer = new MidiComposer();

    audioAnalyser = new AudioAnalyser();

    /*QPushButton * playButton = new QPushButton("Play",this);
    QObject::connect(playButton, SIGNAL(clicked()), this, SLOT(playMidi())) ;*/

    QPushButton * analButton = new QPushButton("Analyse",this);
    QObject::connect(analButton, SIGNAL(clicked()), this, SLOT(analyseSound())) ;

    this->adjustSize();
}

void MainWindow::playMidi(){
    qDebug() << "play";
}

void MainWindow::analyseSound(){
    audioAnalyser->loadSound();
}

MainWindow::~MainWindow()
{

}


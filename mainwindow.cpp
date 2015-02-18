#include "mainwindow.h"
#include "midicomposer.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //MainFrame *mainFrame = new MainFrame(this);
    //this->setCentralWidget(mainFrame);
    MidiComposer * midiComposer = new MidiComposer();
    this->adjustSize();
}

MainWindow::~MainWindow()
{

}


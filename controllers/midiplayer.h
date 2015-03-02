#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <stdio.h>
#include <QThread>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QApplication>
#include "QMidi/QMidiOut.h"
#include "QMidi/QMidiFile.h"
#include <iostream>
#include <QDebug>
#include <QMainWindow>
#include <QThread>

class MainController;

class MidiPlayer : public QThread
{
    Q_OBJECT
public:
    MidiPlayer(MainController * mainCtrl);
    ~MidiPlayer();
    void play(std::string path);
    void stop();

private:
    MainController * m_mainController;

    QMidiEvent* m_midiFileEvent;
    QMidiFile* m_midiFile;
    QMidiOut* m_midiOut;

protected:
    void run();

private slots:
    void handleEvent();

};

#endif // MIDIPLAYER_H

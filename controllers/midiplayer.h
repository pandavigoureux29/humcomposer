#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <stdio.h>
#include <QThread>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QApplication>

#include <iostream>
#include <QDebug>
#include <QMainWindow>
#include <QThread>

#if defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)
#include "QMidi/QMidiOut.h"
#include "QMidi/QMidiFile.h"
#endif // defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)

class MainController;
class Track;

class MidiPlayer : public QThread
{
    Q_OBJECT
public:
    MidiPlayer(MainController * mainCtrl);
    ~MidiPlayer();
    void play(QString path);
    void playTrack(Track * _track);
    void stop();

private:
    MainController * m_mainController;

#if defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)
    QMidiEvent* m_midiFileEvent;
    QMidiFile* m_midiFile;
    QMidiOut* m_midiOut;
#endif // defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)

protected:
    void run();

private slots:
    void handleEvent();

};

#endif // MIDIPLAYER_H

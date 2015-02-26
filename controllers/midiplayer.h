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

class MidiPlayer : public QThread
{
    Q_OBJECT
public:
    MidiPlayer();
    ~MidiPlayer();
    void play();

private:
    QMidiEvent* m_midiFileEvent;
    QMidiFile* m_midiFile;
    QMidiOut* m_midiOut;

protected:
    void run();

private slots:
    void handleEvent();

};

#endif // MIDIPLAYER_H

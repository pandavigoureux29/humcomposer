#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVBoxLayout>

//ui
#include "ui/uitrackframe.h"
#include "ui/uirecorder.h"

//data manager
#include "midicomposer.h"
#include "audioanalyser.h"

#include <SFML/Audio.hpp>
#include "notedata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    public slots:
        void playMidi();
        void analyseSound();

    public :
        //callbacks
        void onRecordedFinished(int track, sf::SoundBuffer recorderBuffer);

    private :
        AudioAnalyser * m_audioAnalyser;
        MidiComposer * m_midiComposer;
        //UIRecorder * m_uiRecorder;
        std::vector<UITrackFrame> * m_tracks;

};

#endif // MAINWINDOW_H

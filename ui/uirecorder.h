#ifndef UIRECORDER_H
#define UIRECORDER_H

#include <SFML/Audio.hpp>
#include <QHBoxLayout>
#include <QDebug>
#include <QFrame>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "audioanalyser.h"
//#include "mainwindow.h"

class UIRecorder: public QFrame{

    Q_OBJECT

    public:
        UIRecorder(QWidget *parent = 0);
        ~UIRecorder();

    public slots:
        void play();
        void record();
        void stop();

    private :

        //MainWindow * m_mainWindow;

        sf::SoundBufferRecorder * m_sfRecorder;
        sf::Sound * m_sfSound;

        AudioAnalyser * m_analyser;

};

#endif // UIRECORDER_H

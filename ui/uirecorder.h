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

#include "controllers/maincontroller.h"

class UIRecorder: public QFrame{

    Q_OBJECT

    public:
        UIRecorder(QWidget *parent = 0);
        ~UIRecorder();
        void setMainController(MainController * mc);
        void setOnRecordedCallback();

    public slots:
        void play();
        void record();
        void stop();

    private :
        MainController * m_mainController;
        sf::SoundBufferRecorder * m_sfRecorder;

        sf::Sound * m_sfSound;
        sf::SoundBuffer * m_sndBuffer;
};

#endif // UIRECORDER_H

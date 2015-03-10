#ifndef UIRECORDER_H
#define UIRECORDER_H

#include <SFML/Audio.hpp>
#include <QDebug>
#include <QFrame>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QTimer>

#include "uirecordergraph.h"
#include "other/customrecorder.h"

class MainController;

class UIRecorder: public QFrame{

    Q_OBJECT

    public:
        UIRecorder(MainController * mc);
        ~UIRecorder();
        void setMainController(MainController * mc);
        void onAnalyseFailed();

    public slots:
        void play();
        void record();
        void stop();
        void convertToMidi();
        void onNoiseValueChanged();
        void onTimerRecordTimeOut();

    private :
        UIRecorderGraph * m_graph;
        QSpinBox * m_noiseSpBox;

        MainController * m_mainController;
        CustomRecorder * m_sfRecorder;

        sf::Sound * m_sfSound;
        sf::SoundBuffer * m_sndBuffer;

        std::string m_state;
        QTimer * m_timerRecord;

};

#endif // UIRECORDER_H

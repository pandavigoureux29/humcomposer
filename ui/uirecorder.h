#ifndef UIRECORDER_H
#define UIRECORDER_H


#include <QAudioInput>
#include <QAudioOutput>
#include <QBuffer>
#include <QDebug>
#include <QFrame>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QFile>

#include "uirecordergraph.h"

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
        void killNoise();
        //Input Audio
        void onAudioInputStateChanged(QAudio::State newState);
        void readMore();

    private :
        const int BUFFER_SIZE = 16384;

        UIRecorderGraph * m_graph;
        QSpinBox * m_noiseSpBox;

        MainController * m_mainController;

        QAudioFormat m_format;
        //INPUT DEVICE VARIABLES
        QAudioInput * m_audioInput;
        QAudioDeviceInfo m_inputDeviceInfo;
        QIODevice * m_inputIODevice;

        //OUTPUT DEVICE
        QAudioOutput * m_audioOutput;
        QAudioDeviceInfo m_outputDeviceInfo;
        QIODevice * m_outputIODevice;
        QBuffer * m_outputBuffer;

        QByteArray * m_byteArrayBuffer;
        std::vector<short int> m_samples;

        QFile * m_outputFile;

        std::string m_state;

        void createInputOuptutDevice();

};

#endif // UIRECORDER_H

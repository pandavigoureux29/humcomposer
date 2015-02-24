#ifndef UIRECORDER_H
#define UIRECORDER_H

#include <SFML/Audio.hpp>
#include <QHBoxLayout>
#include <QDebug>

#include <QPushButton>
#include <QHBoxLayout>

class UIRecorder: public QWidget{

    Q_OBJECT

    public:
        UIRecorder(QWidget *parent = 0);
        ~UIRecorder();

    public slots:
        void record();
        void stop();

    private :
        sf::SoundBufferRecorder * m_sfRecorder;
};

#endif // UIRECORDER_H

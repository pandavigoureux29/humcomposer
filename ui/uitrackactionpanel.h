#ifndef UITRACKACTIONPANEL_H
#define UITRACKACTIONPANEL_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QFrame>

#include <QPushButton>
#include <QHBoxLayout>

class UITrackFrame;

class UITrackActionPanel: public QFrame{
    Q_OBJECT

    public:
        UITrackActionPanel(UITrackFrame * frame);
        ~UITrackActionPanel();

    public slots:
        void play();
        void stop();

    private:
        UITrackFrame * m_trackFrame;
        QLabel * m_title;
};

#endif // UITRACKACTIONPANEL_H

#ifndef UITRACKACTIONPANEL_H
#define UITRACKACTIONPANEL_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QFrame>

#include <QPushButton>
#include <QHBoxLayout>

#include "ui/uirecorder.h"

class UITrackActionPanel: public QFrame{
    Q_OBJECT

    public:
        UITrackActionPanel(QWidget *parent = 0);
        ~UITrackActionPanel();

    public slots:
        void record();
        void stop();

    private:
        QLabel * m_title;
};

#endif // UITRACKACTIONPANEL_H

#ifndef UITRACKFRAME_H
#define UITRACKFRAME_H

#include <QHBoxLayout>
#include <QDebug>
#include <QFrame>

#include <QPushButton>
#include <QHBoxLayout>

#include "uitrackactionpanel.h";
#include "uitrackmidipanel.h"

class UITrackFrame : public QFrame {
    Q_OBJECT

    public:
        UITrackFrame(QWidget * parent = 0);
        ~UITrackFrame();

    public slots:
        void playMidi();

    private:
        UITrackActionPanel * m_uiTAP;
        UITrackMidiPanel * m_uiMidiPanel;

};

#endif // UITRACKFRAME_H

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

    public:
        UITrackFrame(QWidget * parent = 0);
        ~UITrackFrame();

    private:
        UITrackActionPanel * m_uiTAP;
        UITrackMidiPanel * m_uiMidiPanel;

};

#endif // UITRACKFRAME_H

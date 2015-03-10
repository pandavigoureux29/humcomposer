#ifndef UITRACKFRAME_H
#define UITRACKFRAME_H

#include <QHBoxLayout>
#include <QDebug>
#include <QFrame>

#include <QPushButton>
#include <QHBoxLayout>

#include "uitrackactionpanel.h";
#include "uitrackmidipanel.h"

#include "../controllers/track.h";

class UITrackFrame : public QFrame {
    Q_OBJECT

    public:
        UITrackFrame(Track * _track);
        ~UITrackFrame();
        void refresh();

        Track * getTrack();

    public slots:
        void playMidi();

    private:
        UITrackActionPanel * m_uiTAP;
        UITrackMidiPanel * m_uiMidiPanel;

        Track * m_track;

};

#endif // UITRACKFRAME_H

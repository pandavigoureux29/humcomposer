#include "uitrackframe.h"

UITrackFrame::UITrackFrame(Track * _track) : QFrame(0)
{
    m_track = _track;
    //layout
    QHBoxLayout * hLayout = new QHBoxLayout();

    m_uiTAP = new UITrackActionPanel();
    hLayout->addWidget(m_uiTAP);

    m_uiMidiPanel = new UITrackMidiPanel();
    hLayout->addWidget(m_uiMidiPanel);


    this->setFrameStyle(QFrame::Box);

    this->setLayout(hLayout);
    this->adjustSize();
}

void UITrackFrame::playMidi(){
    qDebug() << "playTrack";
}

UITrackFrame::~UITrackFrame()
{

}


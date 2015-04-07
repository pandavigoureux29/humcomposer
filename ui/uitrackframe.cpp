#include "uitrackframe.h"

UITrackFrame::UITrackFrame(Track * _track) : QFrame(0)
{
    m_track = _track;
    qDebug() << (_track != NULL);
    //layout
    QHBoxLayout * hLayout = new QHBoxLayout();

    m_uiTAP = new UITrackActionPanel();
    hLayout->addWidget(m_uiTAP);

    m_uiMidiPanel = new UITrackMidiPanel(this);
    hLayout->addWidget(m_uiMidiPanel);


    this->setFrameStyle(QFrame::Box);

    this->setLayout(hLayout);
    this->adjustSize();
}

void UITrackFrame::playMidi(){
    qDebug() << "playTrack";
}

//Called by MainWindow
void UITrackFrame::refresh(){
    m_uiMidiPanel->refresh();
}

Track * UITrackFrame::getTrack(){
    return m_track;
}

UITrackFrame::~UITrackFrame()
{

}


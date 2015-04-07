#include "uitrackframe.h"
#include "controllers/maincontroller.h"

UITrackFrame::UITrackFrame(Track * _track, MainController * _mC) : QFrame(0)
{
    m_track = _track;
    m_mainController = _mC;
    qDebug() << (_track != NULL);
    //layout
    QHBoxLayout * hLayout = new QHBoxLayout();

    m_uiTAP = new UITrackActionPanel(this);
    hLayout->addWidget(m_uiTAP);

    m_uiMidiPanel = new UITrackMidiPanel(this);
    hLayout->addWidget(m_uiMidiPanel);


    this->setFrameStyle(QFrame::Box);

    this->setLayout(hLayout);
    this->adjustSize();
}

void UITrackFrame::playMidi(){
    qDebug() << "playTrack";
    m_mainController->playTrack(m_track);
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


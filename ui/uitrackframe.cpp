#include "uitrackframe.h"

UITrackFrame::UITrackFrame(QWidget * parent) : QFrame(parent)
{
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

UITrackFrame::~UITrackFrame()
{

}


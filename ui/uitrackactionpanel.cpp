#include "uitrackactionpanel.h"

UITrackActionPanel::UITrackActionPanel(QWidget * parent) : QFrame(parent)
{
    QVBoxLayout * vLayout = new QVBoxLayout();

    m_title = new QLabel("Track 1");
    m_title->setMaximumHeight( 20 );
    //m_title->setSizePolicy();
    vLayout->addWidget(m_title);

    m_uiRecorder = new UIRecorder();
    vLayout->addWidget(m_uiRecorder);

    this->setLayout(vLayout);
    this->setFixedSize(200,150);

    this->setFrameStyle(QFrame::Box);
    this->adjustSize();
}

UITrackActionPanel::~UITrackActionPanel()
{

}


#include "uirecordergraph.h"

UIRecorderGraph::UIRecorderGraph() : QFrame(0)
{
    m_infoLabel = new QLabel("Info");
    m_infoLabel->setMaximumHeight(20);

    QVBoxLayout * vLayout = new QVBoxLayout();
    vLayout->addWidget(m_infoLabel);

    this->setMinimumWidth(500);
    this->setFixedHeight(180);

    this->setFrameStyle(QFrame::Box);
    this->setLayout(vLayout);
}

void UIRecorderGraph::setInfoText(std::string _infoText){
    const QString txt = QString::fromStdString(_infoText);
    m_infoLabel->setText(txt);
}

void UIRecorderGraph::buildGraphFromBuffer(sf::SoundBuffer * _sfBuffer){

}

UIRecorderGraph::~UIRecorderGraph()
{

}


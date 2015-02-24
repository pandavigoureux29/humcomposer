#include "uirecorder.h"

UIRecorder::UIRecorder(QWidget *parent) : QWidget(parent)
{
    m_sfRecorder = new sf::SoundBufferRecorder();

    //Buttons
    QHBoxLayout * hLayout = new QHBoxLayout();

    QPushButton * recordButton = new QPushButton(">O");
    QObject::connect(recordButton, SIGNAL(clicked()), this, SLOT(record())) ;

    QPushButton * stopButton = new QPushButton("[]");
    QObject::connect(stopButton, SIGNAL(clicked()), this, SLOT(stop())) ;

    hLayout->addWidget(recordButton);
    hLayout->addWidget(stopButton);

    this->setLayout(hLayout);
    this->adjustSize();
}

void UIRecorder::record(){
    qDebug() << "RECORD";
    //m_sfRecorder->start(44100);
}

void UIRecorder::stop(){
    qDebug() << "STOP";
    //m_sfRecorder->stop();
    //const sf::SoundBuffer& buffer = m_sfRecorder->getBuffer();
}

UIRecorder::~UIRecorder()
{

}


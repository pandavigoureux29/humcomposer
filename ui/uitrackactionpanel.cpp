#include "uitrackactionpanel.h"

UITrackActionPanel::UITrackActionPanel(QWidget * parent) : QFrame(parent)
{

    m_sfRecorder = new sf::SoundBufferRecorder();

    //UI
    //Vertical Layout holding title & audio buttons
    QVBoxLayout * vLayout = new QVBoxLayout();

    //TITLE
    m_title = new QLabel("Track 1");
    m_title->setMaximumHeight( 20 );
    vLayout->addWidget(m_title);


    //AUDIO RECORDING===================
    QWidget * m_audioWidget = new QWidget();
    QHBoxLayout * hLayout = new QHBoxLayout();

    QPushButton * recordButton = new QPushButton(">O");
    QObject::connect(recordButton, SIGNAL(clicked()), this, SLOT(record())) ;

    QPushButton * stopButton = new QPushButton("[]");
    QObject::connect(stopButton, SIGNAL(clicked()), this, SLOT(stop())) ;

    hLayout->addWidget(recordButton);
    hLayout->addWidget(stopButton);

    m_audioWidget->adjustSize();
    m_audioWidget->setLayout(hLayout);
    vLayout->addWidget(m_audioWidget);
    //========================audiorecording

    this->setLayout(vLayout);
    this->setFixedSize(200,150);

    this->setFrameStyle(QFrame::Box);
    this->adjustSize();
}

void UITrackActionPanel::record(){
    qDebug() << "RECORD";
    //m_sfRecorder->start(44100);
}

void UITrackActionPanel::stop(){
    qDebug() << "STOP";
    //m_sfRecorder->stop();
    //const sf::SoundBuffer& buffer = m_sfRecorder->getBuffer();
}

UITrackActionPanel::~UITrackActionPanel()
{

}


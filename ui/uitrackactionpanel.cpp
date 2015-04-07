#include "uitrackactionpanel.h"
#include "ui/uitrackframe.h"

UITrackActionPanel::UITrackActionPanel(UITrackFrame * _frame) : QFrame(0)
{
    m_trackFrame = _frame;
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

    QPushButton * recordButton = new QPushButton(">");
    QObject::connect(recordButton, SIGNAL(clicked()), this, SLOT(play())) ;

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

void UITrackActionPanel::play(){
    m_trackFrame->playMidi();
}

void UITrackActionPanel::stop(){
    qDebug() << "STOP";
}

UITrackActionPanel::~UITrackActionPanel()
{

}


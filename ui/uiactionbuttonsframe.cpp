#include "uiactionbuttonsframe.h"

UIActionButtonsFrame::UIActionButtonsFrame(QWidget *parent) : QFrame(0)
{    
    //Buttons
    QHBoxLayout * hLayout = new QHBoxLayout();

    QPushButton * playButton = new QPushButton(">");
    QObject::connect(playButton, SIGNAL(clicked()), parent, SLOT(playMidi())) ;

    QPushButton * stopButton = new QPushButton("[]");
    QObject::connect(stopButton, SIGNAL(clicked()), parent, SLOT(stopMidi())) ;

    hLayout->addWidget(playButton);
    hLayout->addWidget(stopButton);

    this->setLayout(hLayout);
}

UIActionButtonsFrame::~UIActionButtonsFrame()
{

}


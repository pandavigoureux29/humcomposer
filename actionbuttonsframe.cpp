#include "actionbuttonsframe.h"

ActionButtonsFrame::ActionButtonsFrame(QWidget *parent) : QWidget(parent)
{    
    //Buttons
    QHBoxLayout * hLayout = new QHBoxLayout();

    QPushButton * playButton = new QPushButton("Build MIDI");
    QObject::connect(playButton, SIGNAL(clicked()), parent, SLOT(playMidi())) ;

    QPushButton * analButton = new QPushButton("Analyse");
    QObject::connect(analButton, SIGNAL(clicked()), parent, SLOT(analyseSound())) ;

    hLayout->addWidget(playButton);
    hLayout->addWidget(analButton);

    this->setLayout(hLayout);
}

ActionButtonsFrame::~ActionButtonsFrame()
{

}


#include "uinote.h"

UINote::UINote(QWidget * parent) : QFrame(parent)
{
    QHBoxLayout * mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(QMargins(0,0,0,0));
    mainLayout->setSpacing(0);

    //Label Note
    m_labelNote = new QLabel("00");
    m_labelNote->setMaximumHeight(40);
    mainLayout->addWidget(m_labelNote);

    //BUTTONS
    QWidget * buttonsW = new QWidget();
    QVBoxLayout * btnLayout = new QVBoxLayout();
    btnLayout->setMargin(0);
    btnLayout->setContentsMargins(QMargins(0,0,0,0));
    btnLayout->setSpacing(0);

    m_upButton = new QPushButton();
    m_upButton->setMaximumWidth(20);
    m_upButton->setMaximumHeight(20);
    m_upButton->show();

    m_downButton = new QPushButton();
    m_downButton->setMaximumWidth(20);
    m_downButton->setMaximumHeight(20);
    m_downButton->show();

    btnLayout->addWidget(m_upButton);
    btnLayout->addWidget(m_downButton);
    buttonsW->setLayout(btnLayout);

    mainLayout->addWidget(buttonsW);
    this->setMaximumHeight(40);
    this->setFrameStyle(QFrame::Box);
    this->setLayout(mainLayout);
    //this->setContentsMargins(QMargins(0,0,0,0));
}

void UINote::setUp(NoteData * _noteData){
    m_noteData = _noteData;
    m_labelNote->setText( QString::fromStdString( std::to_string(_noteData->note) ) );
}

void UINote::onUp(){

}

void UINote::onDown(){

}

UINote::~UINote()
{

}


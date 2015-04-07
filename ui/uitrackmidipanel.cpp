#include "uitrackmidipanel.h"
#include "uitrackframe.h"

#include <sstream>

UITrackMidiPanel::UITrackMidiPanel(UITrackFrame * _uitrackframe): QFrame(0)
{
    m_trackFrame = _uitrackframe;
    m_pixelPerSecUnit = 200;
    m_uiNotes = new std::vector<UINote*>();

    m_scrollArea = new QScrollArea();

    m_content = new QWidget();
    m_content->setMinimumHeight(100);

    m_scrollArea->setWidget(m_content);
    m_scrollArea->adjustSize();

    drawRuler();

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(m_scrollArea);

    this->setLayout(layout);
    this->setFrameStyle(QFrame::Box);
    this->setMinimumWidth(500);
    this->setFixedHeight(150);
    this->adjustSize();
}

void UITrackMidiPanel::buildTrack(){

}

void UITrackMidiPanel::refresh(){
    qDebug() << "refresh" << (m_trackFrame->getTrack()->getNotes()->size());

    for( int i =0; i < m_trackFrame->getTrack()->getNotes()->size(); i++){
        NoteData * noteData = & m_trackFrame->getTrack()->getNotes()->at(i);
        UINote * uinote = new UINote(m_content);
        m_uiNotes->push_back(uinote);
        int x = noteData->timeBegin()*m_pixelPerSecUnit * 0.001;
        qDebug() << "note "<< (noteData->note) << "x : " << x;
        //Set up
        uinote->setUp(noteData);
        //move to the right position
        uinote->move(x,30);
        uinote->show();
    }
}

void UITrackMidiPanel::drawRuler(){
    QLabel * timeLabel;
    for(int i=0; i < 30; i++){
        timeLabel = new QLabel(m_content);
        timeLabel->setAlignment(Qt::AlignCenter);

        std::ostringstream convert;
        convert << i;
        std::string s = convert.str();

        timeLabel->setText(QString::fromStdString(s));
        timeLabel->move(i * m_pixelPerSecUnit,0);
    }
    m_content->adjustSize();
    m_scrollArea->adjustSize();
}

UITrackMidiPanel::~UITrackMidiPanel()
{

}


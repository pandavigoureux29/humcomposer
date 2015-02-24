#include "uitrackmidipanel.h"

UITrackMidiPanel::UITrackMidiPanel(QWidget * parent): QFrame(parent)
{
    this->setFrameStyle(QFrame::Box);
    this->setMinimumWidth(500);
    this->setFixedHeight(150);
    this->adjustSize();
}

UITrackMidiPanel::~UITrackMidiPanel()
{

}


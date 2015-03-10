#ifndef UITRACKMIDIPANEL_H
#define UITRACKMIDIPANEL_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QScrollArea>

#include "notedata.h"
#include "ui/uinote.h"

class UITrackFrame;

class UITrackMidiPanel : public QFrame
{
public:
    UITrackMidiPanel(UITrackFrame * uitrackFrame);
    ~UITrackMidiPanel();

    void refresh();
    void drawRuler();

    void buildTrack();
    void addNote(NoteData * noteData);

private :
    QScrollArea * m_scrollArea;
    QWidget * m_content;

    UITrackFrame * m_trackFrame;

    float m_pixelPerSecUnit;
};

#endif // UITRACKMIDIPANEL_H

#ifndef UINOTE_H
#define UINOTE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

#include "notedata.h"

class UINote : public QFrame
{
    Q_OBJECT
public:
    UINote(QWidget * parent = 0);
    ~UINote();

    void setUp(NoteData * noteData);

public slots:
    void onUp();
    void onDown();

private :
    QFrame * m_frame;

    QPushButton * m_upButton ;
    QPushButton * m_downButton ;

    QLabel * m_labelNote;


    NoteData * m_noteData;
};

#endif // UINOTE_H

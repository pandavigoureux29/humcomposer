#ifndef UIACTIONBUTTONSFRAME_H
#define UIACTIONBUTTONSFRAME_H

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>

class UIActionButtonsFrame: public QFrame{

    Q_OBJECT

    public:
        UIActionButtonsFrame(QWidget *parent = 0);
        ~UIActionButtonsFrame();
};

#endif // UIACTIONBUTTONSFRAME_H

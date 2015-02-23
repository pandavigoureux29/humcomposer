#ifndef ACTIONBUTTONSFRAME_H
#define ACTIONBUTTONSFRAME_H


#include <QPushButton>
#include <QHBoxLayout>

class ActionButtonsFrame: public QWidget{

    Q_OBJECT

    public:
        ActionButtonsFrame(QWidget *parent = 0);
        ~ActionButtonsFrame();
};

#endif // ACTIONBUTTONSFRAME_H

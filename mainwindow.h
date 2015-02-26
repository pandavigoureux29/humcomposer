#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVBoxLayout>

#include "controllers/maincontroller.h"

//ui
#include "ui/uitrackframe.h"
#include "ui/uirecorder.h"

#include <SFML/Audio.hpp>
#include "notedata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    public :
        //callbacks
        void onRecordedFinished(int track, sf::SoundBuffer recorderBuffer);

    private :
        MainController * m_mainController;
        UIRecorder * m_uiRecorder;
        std::vector<UITrackFrame> * m_tracks;

};

#endif // MAINWINDOW_H

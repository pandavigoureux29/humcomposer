#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVBoxLayout>

#include "controllers/maincontroller.h"

//ui
#include "ui/uitrackframe.h"
#include "ui/uirecorder.h"
#include "ui/uiactionbuttonsframe.h"

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
        void addTrack(Track * _track);
        //callbacks
        void onRecordedFinished(int track, sf::SoundBuffer recorderBuffer);

    public slots:
        void playMidi();
        void stopMidi();

    private :
        MainController * m_mainController;
        UIRecorder * m_uiRecorder;
        UIActionButtonsFrame * m_uiActionButtons;
        std::vector<UITrackFrame*> m_tracks;

        QVBoxLayout * m_tracksLayout;

};

#endif // MAINWINDOW_H

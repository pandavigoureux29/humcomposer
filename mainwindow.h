#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "actionbuttonsframe.h"

#include "midicomposer.h"
#include "audioanalyser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    public slots:
        void playMidi();
        void analyseSound();

    private :
        AudioAnalyser * m_audioAnalyser;
        MidiComposer * m_midiComposer;

};

#endif // MAINWINDOW_H

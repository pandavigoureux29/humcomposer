#include "midiplayer.h"
#include "maincontroller.h"
#include "controllers/track.h"
#include <QDebug>

MidiPlayer::MidiPlayer(MainController * _mainCtrl)
{
    m_mainController = _mainCtrl;
}

void MidiPlayer::play(QString _path){
#if defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)
    QString filename = QDir::currentPath()+"/"+ _path;
    qDebug() << filename;
    QString midiOutName = "";
    m_midiFile = new QMidiFile();

    m_midiFile->load(filename);

    m_midiOut = new QMidiOut();
    bool connectRes = m_midiOut->connect(midiOutName);

    //MidiPlayer* p = new MidiPlayer(midi_file,midi_out);
    //QObject::connect(this,SIGNAL(finished()),&a,SLOT(quit()));
    this->start();
#endif // defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)
}

void MidiPlayer::playTrack( Track * _track) {
    QString fullPath = m_mainController->getProjectFolder();
    fullPath += "/tracks/"+_track->getTrackName()+".mid";
    play(fullPath);
}

void MidiPlayer::stop(){
    this->quit();
}

void MidiPlayer::run(){
#if defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)
    QElapsedTimer t;
    t.start();
    QList<QMidiEvent*>* events = m_midiFile->events();
    for(int i = 0; i < events->count(); i++)
    {
        m_midiFileEvent = events->at(i);
        if (m_midiFileEvent->type() != QMidiEvent::Meta)
        {
            qint64 event_time = m_midiFile->timeFromTick(m_midiFileEvent->tick()) * 1000;

            qint32 waitTime = event_time - t.elapsed();
            if(waitTime > 0) {
                msleep(waitTime);
            }
            handleEvent();
        }
    }

    m_midiOut->disconnect();
#endif // defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)
}

void MidiPlayer::handleEvent(){
#if defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)
    if (m_midiFileEvent->type() == QMidiEvent::SysEx)
    { // TODO: sysex
    }
    else
    {
        qint32 message = m_midiFileEvent->message();
        m_midiOut->sendMsg(message);
    }
#endif // defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_HAIKU)
}

MidiPlayer::~MidiPlayer()
{

}


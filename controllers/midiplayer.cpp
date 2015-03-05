#include "midiplayer.h"
#include "maincontroller.h"
#include <QDebug>

MidiPlayer::MidiPlayer(MainController * _mainCtrl)
{
    m_mainController = _mainCtrl;
}

void MidiPlayer::play(std::string _path){
    QString filename = QDir::currentPath()+"/"+ QString::fromStdString(_path);
    QString midiOutName = "";
    m_midiFile = new QMidiFile();

    m_midiFile->load(filename);

    m_midiOut = new QMidiOut();
    bool connectRes = m_midiOut->connect(midiOutName);
    qDebug() << connectRes;
    //MidiPlayer* p = new MidiPlayer(midi_file,midi_out);
    //QObject::connect(this,SIGNAL(finished()),&a,SLOT(quit()));
    this->start();
}

void MidiPlayer::stop(){
    this->quit();
}

void MidiPlayer::run(){
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
}

void MidiPlayer::handleEvent(){
    if (m_midiFileEvent->type() == QMidiEvent::SysEx)
    { // TODO: sysex
    }
    else
    {
        qint32 message = m_midiFileEvent->message();
        m_midiOut->sendMsg(message);
    }
}

MidiPlayer::~MidiPlayer()
{

}


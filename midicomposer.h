#ifndef MIDICOMPOSER_H
#define MIDICOMPOSER_H

#ifdef WIN32
#include <windows.h>
#endif

//JDKS
#include "jdksmidi/world.h"
#include "jdksmidi/track.h"
#include "jdksmidi/multitrack.h"
#include "jdksmidi/filereadmultitrack.h"
#include "jdksmidi/fileread.h"
#include "jdksmidi/fileshow.h"
#include "jdksmidi/filewritemultitrack.h"

#include "notedata.h"


class MainController;
class Track;

using namespace jdksmidi;

#include <iostream>
using namespace std;

#include <QDebug>

class MidiComposer
{
public:
    MidiComposer(MainController * mainController);
    ~MidiComposer();

public:
    void setTrackInstrument(int,int);
    void buildMidiTrackFromData(Track * _track, int _totalAudioSize);

private :
    MainController * m_mainController;
    MIDITimedBigMessage *m_message;
    MIDIMultiTrack *m_tracks;
    int m_tracksCount = 2;
    MIDIClockTime m_time;
    MIDIClockTime m_dt;    

    void initTracks();
    void pushNote(int note, int track, int durationMs);
    void pushSilence(int track,int duration);
    int writeFile(QString filePath);
};

#endif // MIDICOMPOSER_H

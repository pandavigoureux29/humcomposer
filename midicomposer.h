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

using namespace jdksmidi;

#include <iostream>
using namespace std;

#include <QDebug>

class MidiComposer
{
public:
    MidiComposer();
    ~MidiComposer();

public:
    void initTracks();
    int writeFile(std::string filePath);
    void setTrackInstrument(int,int);
    void pushNote(int note, int track, int durationMs);
    void pushSilence(int track,int duration);
    void buildMidiFromData(std::vector<NoteData> * _notesData, int _totalAudioSize);

private :
    MIDITimedBigMessage *m_message;
    MIDIMultiTrack *m_tracks;
    int m_tracksCount = 2;
    MIDIClockTime m_time;
    MIDIClockTime m_dt;
};

#endif // MIDICOMPOSER_H

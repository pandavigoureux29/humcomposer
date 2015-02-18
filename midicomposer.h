#ifndef MIDICOMPOSER_H
#define MIDICOMPOSER_H

#ifdef WIN32
#include <windows.h>
#endif

#include "jdksmidi/world.h"
#include "jdksmidi/track.h"
#include "jdksmidi/multitrack.h"
#include "jdksmidi/filereadmultitrack.h"
#include "jdksmidi/fileread.h"
#include "jdksmidi/fileshow.h"
#include "jdksmidi/filewritemultitrack.h"
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
    int writeFile();

private :
    MIDIMultiTrack m_tracks;
    int m_tracksCount = 2;
};

#endif // MIDICOMPOSER_H

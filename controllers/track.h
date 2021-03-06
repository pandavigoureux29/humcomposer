#ifndef TRACK_H
#define TRACK_H

#include "notedata.h"

class TracksManager;

class Track
{
public:
    Track(unsigned int id, TracksManager * trackManager);
    ~Track();
    void getMute();
    void setMute();

    void setNotes(std::vector<NoteData> * notes);
    std::vector<NoteData> * getNotes();

private:
    unsigned int m_id;
    TracksManager * m_manager;
    bool m_mute;

    std::vector<NoteData> * m_notes;

};

#endif // TRACK_H

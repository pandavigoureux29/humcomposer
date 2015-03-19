#include "track.h"
#include "tracksmanager.h"

Track::Track(unsigned int _id, TracksManager * _trackManager)
{
    m_id = _id;
    m_manager = _trackManager;
    m_notes = new std::vector<NoteData>();
}

void Track::setNotes(std::vector<NoteData> * _notes){
    for( int i=0; i < _notes->size(); i++){
        //NoteData * note = _notes->at(i).clone();
        //m_notes->push_back(*note);
    }
}

std::vector<NoteData> * Track::getNotes(){
    return m_notes;
}

Track::~Track()
{
    m_notes->clear();
}


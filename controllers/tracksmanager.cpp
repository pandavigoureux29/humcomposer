#include "tracksmanager.h"
#include "maincontroller.h"

TracksManager::TracksManager(MainController * _mainCtrl)
{
    m_mainController = _mainCtrl;
    m_tracks = std::vector<Track>();
}

void TracksManager::addTrack(){
    Track * track = new Track(m_tracks.size(),this);
    m_tracks.push_back( *track );
    m_mainController->onTrackAdded(m_tracks.size()-1);
}

Track * TracksManager::getTrack(unsigned int _id){
    if( _id >= m_tracks.size()){
        return NULL;
    }
    return &(m_tracks.at(_id));
}

void TracksManager::buildMidiToTrack(unsigned int _trackID, std::vector<NoteData> * _notes){
    Track * track = getTrack(_trackID);
    if( track != NULL ){
        track->setNotes(_notes);
    }
}

TracksManager::~TracksManager()
{

}


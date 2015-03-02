#include "tracksmanager.h"
#include "maincontroller.h"

TracksManager::TracksManager(MainController * _mainCtrl)
{
    m_mainController = _mainCtrl;
    m_tracks = std::vector<Track>();
}

void TracksManager::addTrack(){
    m_tracks.push_back( Track(m_tracks.size(),this));
    m_mainController->onTrackAdded(m_tracks.size()-1);
}

Track * TracksManager::getTrack(unsigned int _id){
    if( _id < m_tracks.size()){
        return NULL;
    }
    return &(m_tracks.at(_id));
}

TracksManager::~TracksManager()
{

}


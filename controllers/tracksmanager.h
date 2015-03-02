#ifndef TRACKSMANAGER_H
#define TRACKSMANAGER_H

#include "track.h"
#include <vector>

class MainController;

class TracksManager
{
public:
    TracksManager(MainController * mainController);
    ~TracksManager();
    Track * getTrack(unsigned int _id);
    void addTrack();

private:
    //vars
    MainController * m_mainController;
    std::vector<Track> m_tracks;

    //functions

};

#endif // TRACKSMANAGER_H

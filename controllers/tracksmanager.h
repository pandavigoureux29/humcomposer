#ifndef TRACKSMANAGER_H
#define TRACKSMANAGER_H

#include "track.h"
#include <vector>

class TracksManager
{
public:
    TracksManager();
    ~TracksManager();

private:
    std::vector<Track> m_tracks;

};

#endif // TRACKSMANAGER_H

#include "track.h"
#include "tracksmanager.h"

Track::Track(unsigned int _id, TracksManager * _trackManager)
{
    m_id = _id;
    m_manager = _trackManager;
}

Track::~Track()
{

}


#ifndef TRACK_H
#define TRACK_H

class TracksManager;

class Track
{
public:
    Track(unsigned int id, TracksManager * trackManager);
    ~Track();
    void getMute();
    void setMute();

private:
    unsigned int m_id;
    TracksManager * m_manager;
    bool m_mute;

};

#endif // TRACK_H

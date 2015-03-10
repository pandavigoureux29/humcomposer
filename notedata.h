#ifndef NOTEDATA
#define NOTEDATA
#include <QDebug>

class NoteData{
public:
    NoteData();
    ~NoteData();
    NoteData * clone();

    int begin;
    int end;
    int note;

    /**
     * Return length of the note in sample count
     */
    int length();
    /**
     * Return duration of the note in ms
    */
    float duration();

    float timeBegin();

    void setSampleRate(int _sampleRate);
    int getSampleRate();

private:
    int m_sampleRate;
};

#endif // NOTEDATA


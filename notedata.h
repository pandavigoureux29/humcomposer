#ifndef NOTEDATA
#define NOTEDATA
#include <QDebug>

class NoteData{
public:
    NoteData();
    ~NoteData();

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

    void setSampleRate(int _sampleRate);
    int getSampleRate();

private:
    int m_sampleRate;
};

#endif // NOTEDATA


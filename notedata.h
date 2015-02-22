#ifndef NOTEDATA
#define NOTEDATA

class NoteData{
public:
    NoteData();
    ~NoteData();

    int begin;
    int end;
    int note;

    int length();
    float duration(int sampleRate);
};

#endif // NOTEDATA


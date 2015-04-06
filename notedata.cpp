#include "notedata.h"

NoteData::NoteData(){
    begin = -1;
    end = -1;
    note = -1;
    m_sampleRate = 44100;
}

int NoteData::length(){
    return end-begin;
}

float NoteData::duration(){
    return ((float)length() /(float) m_sampleRate) * 1000;
}

float NoteData::timeBegin(){
    if( m_sampleRate == 0)
        return -1;
    return ((float)begin/ (float)m_sampleRate) * 1000; // duration in ms
}

void NoteData::setSampleRate(int _sampleRate){
    m_sampleRate = _sampleRate;
}

int NoteData::getSampleRate(){
    return m_sampleRate;
}

NoteData::~NoteData(){

}

NoteData * NoteData::clone(){
    NoteData * newNote = new NoteData();
    newNote->begin = this->begin;
    newNote->end = this->end;
    newNote->note = this->note;
    newNote->setSampleRate(this->m_sampleRate);
    return newNote;
}

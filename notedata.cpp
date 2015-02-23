#include "notedata.h"

NoteData::NoteData(){
    begin = -1;
    end = -1;
    note = -1;
    m_sampleRate = 44100;
}

NoteData::length(){
    return end-begin;
}

float NoteData::duration(){
    return ((float)length() /(float) m_sampleRate) * 1000;
}

void NoteData::setSampleRate(int _sampleRate){
    m_sampleRate = _sampleRate;
}

int NoteData::getSampleRate(){
    return m_sampleRate;
}

NoteData::~NoteData(){

}

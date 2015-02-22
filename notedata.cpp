#include "notedata.h"

NoteData::NoteData(){
    begin = -1;
    end = -1;
    note = -1;
}

NoteData::length(){
    return end-begin;
}

float NoteData::duration(int sampleRate){
    return (length()/sampleRate);
}

NoteData::~NoteData(){

}

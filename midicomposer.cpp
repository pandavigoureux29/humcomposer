#include "midicomposer.h"

MidiComposer::MidiComposer()
{
    MIDITimedBigMessage  m_message; // the object for individual midi events

    m_time = MIDIClockTime(); // time in midi ticks
    initTracks();
    //setTrackInstrument(1,29);
    pushNote(40,1,100);
    pushNote(46,1,300);

    writeFile();

}

void MidiComposer::initTracks(){

    m_time = 0;
    MIDIClockTime dt = 100; // time interval (1 second)
    int clks_per_beat = 100; // number of ticks in crotchet (1...32767)
    m_tracksCount = 2; // tracks 0 and 1

    m_tracks = new MIDIMultiTrack( m_tracksCount );  // the object which will hold all the tracks
    m_tracks->SetClksPerBeat( clks_per_beat );

    m_message.SetTime( m_time );

    // track 0 is used for tempo and time signature info, and some other stuff

    m_message.SetTimeSig( 4, 2 ); // measure 4/4 (default values for time signature)
    m_tracks->GetTrack( 0 )->PutEvent( m_message );

    // set tempo to 1 000 000 usec = 1 sec in crotchet
    // with value of clks_per_beat (100) result 10 msec in 1 midi tick
    // If no tempo is define, 120 beats per minute is assumed.
    m_message.SetTempo( (unsigned long) 1000000 );
    m_tracks->GetTrack( 0 )->PutEvent( m_message );

    // META_TRACK_NAME text in track 0 music notation software like Sibelius uses as headline of the music
    m_tracks->GetTrack( 0 )->PutTextEvent(m_time,
                                         META_TRACK_NAME,
                                         "LibJDKSmidi create_midifile.cpp example by VRM");
}

void MidiComposer::setTrackInstrument(int _track, int _inst){
    unsigned char trk = (unsigned char) _track;
    unsigned char instru = (unsigned char) _inst;
    m_message.SetProgramChange( 0, instru ); // channel 0 instrument 19 - Church Organ
    m_tracks->GetTrack( trk )->PutEvent( m_message );

    m_message.SetProgramChange( 1, instru );
    m_tracks->GetTrack( trk )->PutEvent( m_message );

    m_message.SetProgramChange( 2 , instru );
    m_tracks->GetTrack( trk )->PutEvent( m_message );
}

void MidiComposer::pushNote(int _note,int _track, int _duration){
    //plays the note
    m_message.SetTime( m_time );
    m_message.SetNoteOn( 0, _note, 100 );
    m_tracks->GetTrack( _track )->PutEvent( m_message );

    // after note(s) on before note(s) off: add words to music in the present situation
    m_tracks->GetTrack( _track )->PutTextEvent(m_time, META_LYRIC_TEXT, "note"+_note);

    m_dt = _duration;
    m_time += m_dt;
    //Stops the note
    m_message.SetTime( m_time );
    m_message.SetNoteOff( 0, _note, 100 );
    m_tracks->GetTrack( _track )->PutEvent( m_message );
}

void MidiComposer::pushSilence(int _track,int _duration){
    //plays the note
    m_message.SetTime( m_time );
    m_message.SetNoteOn( 0, 0, 0 );
    m_tracks->GetTrack( _track )->PutEvent( m_message );

    // after note(s) on before note(s) off: add words to music in the present situation
    m_tracks->GetTrack( _track )->PutTextEvent(m_time, META_LYRIC_TEXT, "silence"+_duration);

    m_dt = _duration;
    m_time += m_dt;
    //Stops the note
    m_message.SetTime( m_time );
    m_message.SetNoteOff( 0, 0, 0 );
    m_tracks->GetTrack( _track )->PutEvent( m_message );
}

int MidiComposer::writeFile(){

    int return_code = 0;
    // to write the multi track object out, we need to create an output stream for the output filename
    const char *outfile_name = "debug_midifile.mid";
    MIDIFileWriteStreamFileName out_stream( outfile_name );

    // then output the stream like my example does, except setting m_tracksCount to match your data

    if( out_stream.IsValid() )
    {
        // the object which takes the midi tracks and writes the midifile to the output stream
        MIDIFileWriteMultiTrack writer( m_tracks, &out_stream );

        // write the output file
        if ( writer.Write( m_tracksCount ) )
        {
            cout << "\nOK writing file " << outfile_name << endl;
            return_code = 0;
        }
        else
        {
            cerr << "\nError writing file " << outfile_name << endl;
        }
    }
    else
    {
        cerr << "\nError opening file " << outfile_name << endl;
    }

    //return return_code;
}

MidiComposer::~MidiComposer()
{
    delete &m_tracks;
    delete &m_dt;
    delete &m_message;
    delete &m_time;
}


#include "midicomposer.h"

MidiComposer::MidiComposer()
{
    MIDITimedBigMessage m; // the object for individual midi events
    unsigned char chan, // internal midi channel number 0...15 (named 1...16)
        note, velocity, ctrl, val;

    MIDIClockTime t; // time in midi ticks
    MIDIClockTime dt = 100; // time interval (1 second)
    int clks_per_beat = 100; // number of ticks in crotchet (1...32767)
    m_tracksCount = 2; // tracks 0 and 1

    m_tracks = MIDIMultiTrack( m_tracksCount );  // the object which will hold all the tracks
    m_tracks.SetClksPerBeat( clks_per_beat );
    int trk; // track number, 0 or 1

    t = 0;
    m.SetTime( t );

    // track 0 is used for tempo and time signature info, and some other stuff

    trk = 0;

}

int MidiComposer::writeFile(){
    int return_code = 0;
    // to write the multi track object out, we need to create an output stream for the output filename
    const char *outfile_name = "create_midifile.mid";
    MIDIFileWriteStreamFileName out_stream( outfile_name );

    // then output the stream like my example does, except setting m_tracksCount to match your data

    if( out_stream.IsValid() )
    {
        // the object which takes the midi tracks and writes the midifile to the output stream
        MIDIFileWriteMultiTrack writer( &m_tracks, &out_stream );

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

}


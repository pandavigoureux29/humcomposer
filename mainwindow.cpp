#include "mainwindow.h"
#include "midicomposer.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //MainFrame *mainFrame = new MainFrame(this);
    //this->setCentralWidget(mainFrame);

    MidiComposer * midiComposer = new MidiComposer();
    return;
    int return_code = -1;

        MIDITimedBigMessage m; // the object for individual midi events
        int chan, // internal midi channel number 0...15 (named 1...16)
            note, velocity, ctrl, val;

        MIDIClockTime t; // time in midi ticks
        MIDIClockTime dt = 100; // time interval (1 second)
        int clks_per_beat = 100; // number of ticks in crotchet (1...32767)
        int num_tracks = 2; // tracks 0 and 1

        MIDIMultiTrack tracks( num_tracks );  // the object which will hold all the tracks
        tracks.SetClksPerBeat( clks_per_beat );
        int trk; // track number, 0 or 1

        t = 0;
        m.SetTime( t );

        // track 0 is used for tempo and time signature info, and some other stuff

        trk = 0;

        /*
          SetTimeSig( numerator, denominator_power )
          The numerator is specified as a literal value, the denominator_power is specified as (get ready!)
          the value to which the power of 2 must be raised to equal the number of subdivisions per whole note.
          For example, a value of 0 means a whole note because 2 to the power of 0 is 1 (whole note),
          a value of 1 means a half-note because 2 to the power of 1 is 2 (half-note), and so on.
          (numerator, denominator_power) => musical measure conversion
          (1, 1) => 1/2
          (2, 1) => 2/2
          (1, 2) => 1/4
          (2, 2) => 2/4
          (3, 2) => 3/4
          (4, 2) => 4/4
          (1, 3) => 1/8
        */

        m.SetTimeSig( 4, 2 ); // measure 4/4 (default values for time signature)
        tracks.GetTrack( trk )->PutEvent( m );

        t = 0;

        trk = 1;

        // we add note 1: press and release in (dt) ticks

        m.SetTime( t );
        m.SetNoteOn( chan = 0, note = 60, velocity = 100 );
        tracks.GetTrack( trk )->PutEvent( m );

        // after note(s) on before note(s) off: add words to music in the present situation
        tracks.GetTrack( trk )->PutTextEvent(t, META_LYRIC_TEXT, "Left");

        m.SetTime( t += dt );
        m.SetNoteOff( chan, note, velocity );
        // alternative form of note off event: useful to reduce midifile size if running status is used (on default so)
        // m.SetNoteOn( chan, note, 0 );
        tracks.GetTrack( trk )->PutEvent( m );

        // add pause: press note with velocity = 0 equivalent to simultaneous release it

        t += dt;

        m.SetTime( t );
        m.SetNoteOn( chan = 0, note = 0, velocity = 0 );
        tracks.GetTrack( trk )->PutEvent( m );

        // to write the multi track object out, you need to create an output stream for the output filename

        const char *outfile_name = "create_midifile.mid";
        MIDIFileWriteStreamFileName out_stream( outfile_name );

        // then output the stream like my example does, except setting num_tracks to match your data

        if( out_stream.IsValid() )
        {
            // the object which takes the midi tracks and writes the midifile to the output stream
            MIDIFileWriteMultiTrack writer( &tracks, &out_stream );

            // write the output file
            if ( writer.Write( num_tracks ) )
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

    this->adjustSize();
}

MainWindow::~MainWindow()
{

}


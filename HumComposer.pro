QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-variable

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    midicomposer.cpp \
    jdksmidi/jdksmidi_advancedsequencer.cpp \
    jdksmidi/jdksmidi_driver.cpp \
    jdksmidi/jdksmidi_driverdump.cpp \
    jdksmidi/jdksmidi_edittrack.cpp \
    jdksmidi/jdksmidi_file.cpp \
    jdksmidi/jdksmidi_fileread.cpp \
    jdksmidi/jdksmidi_filereadmultitrack.cpp \
    jdksmidi/jdksmidi_fileshow.cpp \
    jdksmidi/jdksmidi_filewrite.cpp \
    jdksmidi/jdksmidi_filewritemultitrack.cpp \
    jdksmidi/jdksmidi_keysig.cpp \
    jdksmidi/jdksmidi_manager.cpp \
    jdksmidi/jdksmidi_matrix.cpp \
    jdksmidi/jdksmidi_midi.cpp \
    jdksmidi/jdksmidi_msg.cpp \
    jdksmidi/jdksmidi_multitrack.cpp \
    jdksmidi/jdksmidi_parser.cpp \
    jdksmidi/jdksmidi_process.cpp \
    jdksmidi/jdksmidi_queue.cpp \
    jdksmidi/jdksmidi_sequencer.cpp \
    jdksmidi/jdksmidi_showcontrol.cpp \
    jdksmidi/jdksmidi_showcontrolhandler.cpp \
    jdksmidi/jdksmidi_smpte.cpp \
    jdksmidi/jdksmidi_sysex.cpp \
    jdksmidi/jdksmidi_tempo.cpp \
    jdksmidi/jdksmidi_tick.cpp \
    jdksmidi/jdksmidi_track.cpp \
    jdksmidi/jdksmidi_utils.cpp

HEADERS += \
    mainwindow.h \
    midicomposer.h \
    cfugue/Common/_TChar.h \
    cfugue/Common/bitcache.h \
    cfugue/Common/BitVector.h \
    cfugue/Common/COMInitializer.h \
    cfugue/Common/dimacs.h \
    cfugue/Common/ErrorReporter.h \
    cfugue/Common/EventedProperty.h \
    cfugue/Common/EventHandler.h \
    cfugue/Common/FileEnumerator.h \
    cfugue/Common/InitCommonControls.h \
    cfugue/Common/MayaStrUtils.h \
    cfugue/Common/MString.h \
    cfugue/Common/PathHelper.h \
    cfugue/Common/StrUtils.h \
    cfugue/Common/UPDialog.h \
    cfugue/Common/WinStrUtils.h \
    cfugue/jdkmidi/advancedsequencer.h \
    cfugue/jdkmidi/driver.h \
    cfugue/jdkmidi/driverdump.h \
    cfugue/jdkmidi/driverwin32.h \
    cfugue/jdkmidi/edittrack.h \
    cfugue/jdkmidi/file.h \
    cfugue/jdkmidi/fileread.h \
    cfugue/jdkmidi/filereadmultitrack.h \
    cfugue/jdkmidi/fileshow.h \
    cfugue/jdkmidi/filewrite.h \
    cfugue/jdkmidi/filewritemultitrack.h \
    cfugue/jdkmidi/keysig.h \
    cfugue/jdkmidi/manager.h \
    cfugue/jdkmidi/matrix.h \
    cfugue/jdkmidi/midi.h \
    cfugue/jdkmidi/msg.h \
    cfugue/jdkmidi/multitrack.h \
    cfugue/jdkmidi/parser.h \
    cfugue/jdkmidi/process.h \
    cfugue/jdkmidi/queue.h \
    cfugue/jdkmidi/sequencer.h \
    cfugue/jdkmidi/showcontrol.h \
    cfugue/jdkmidi/showcontrolhandler.h \
    cfugue/jdkmidi/smpte.h \
    cfugue/jdkmidi/song.h \
    cfugue/jdkmidi/sysex.h \
    cfugue/jdkmidi/tempo.h \
    cfugue/jdkmidi/tick.h \
    cfugue/jdkmidi/track.h \
    cfugue/jdkmidi/world.h \
    cfugue/rtmidi/RtError.h \
    cfugue/rtmidi/RtMidi.h \
    cfugue/AlsaDriver.h \
    cfugue/CFugueDll.h \
    cfugue/CFugueLib.h \
    cfugue/ChannelPressure.h \
    cfugue/Chords.h \
    cfugue/ControllerEvent.h \
    cfugue/Dictionary.h \
    cfugue/Instrument.h \
    cfugue/KeySignature.h \
    cfugue/Layer.h \
    cfugue/MidiDevice.h \
    cfugue/MidiEventManager.h \
    cfugue/MidiRenderer.h \
    cfugue/MidiTimer.h \
    cfugue/MusicStringParser.h \
    cfugue/Note.h \
    cfugue/Parser.h \
    cfugue/ParserListener.h \
    cfugue/PitchBend.h \
    cfugue/Player.h \
    cfugue/PolyphonicPressure.h \
    cfugue/Talam.h \
    cfugue/Tempo.h \
    cfugue/TimeToken.h \
    cfugue/Voice.h \
    jdksmidi/advancedsequencer.h \
    jdksmidi/driver.h \
    jdksmidi/driverdump.h \
    jdksmidi/driverwin32.h \
    jdksmidi/edittrack.h \
    jdksmidi/file.h \
    jdksmidi/fileread.h \
    jdksmidi/filereadmultitrack.h \
    jdksmidi/fileshow.h \
    jdksmidi/filewrite.h \
    jdksmidi/filewritemultitrack.h \
    jdksmidi/keysig.h \
    jdksmidi/manager.h \
    jdksmidi/matrix.h \
    jdksmidi/midi.h \
    jdksmidi/msg.h \
    jdksmidi/multitrack.h \
    jdksmidi/parser.h \
    jdksmidi/process.h \
    jdksmidi/queue.h \
    jdksmidi/sequencer.h \
    jdksmidi/showcontrol.h \
    jdksmidi/showcontrolhandler.h \
    jdksmidi/smpte.h \
    jdksmidi/song.h \
    jdksmidi/sysex.h \
    jdksmidi/tempo.h \
    jdksmidi/tick.h \
    jdksmidi/track.h \
    jdksmidi/utils.h \
    jdksmidi/world.h
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-variable

win32 { LIBS += -lwinmm }
linux* { LIBS += -lasound }
haiku* { LIBS += -lmidi2 }

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
    jdksmidi/jdksmidi_utils.cpp \
    aubio/io/audio_unit.c \
    aubio/io/sink.c \
    aubio/io/sink_apple_audio.c \
    aubio/io/sink_sndfile.c \
    aubio/io/sink_wavwrite.c \
    aubio/io/source.c \
    aubio/io/source_apple_audio.c \
    aubio/io/source_avcodec.c \
    aubio/io/source_sndfile.c \
    aubio/io/source_wavread.c \
    aubio/io/utils_apple_audio.c \
    aubio/onset/onset.c \
    aubio/onset/peakpicker.c \
    aubio/pitch/pitch.c \
    aubio/pitch/pitchfcomb.c \
    aubio/pitch/pitchmcomb.c \
    aubio/pitch/pitchschmitt.c \
    aubio/pitch/pitchspecacf.c \
    aubio/pitch/pitchyin.c \
    aubio/pitch/pitchyinfft.c \
    aubio/spectral/fft.c \
    aubio/spectral/filterbank.c \
    aubio/spectral/filterbank_mel.c \
    aubio/spectral/mfcc.c \
    aubio/spectral/ooura_fft8g.c \
    aubio/spectral/phasevoc.c \
    aubio/spectral/specdesc.c \
    aubio/spectral/statistics.c \
    aubio/spectral/tss.c \
    aubio/synth/sampler.c \
    aubio/synth/wavetable.c \
    aubio/tempo/beattracking.c \
    aubio/tempo/tempo.c \
    aubio/temporal/a_weighting.c \
    aubio/temporal/biquad.c \
    aubio/temporal/c_weighting.c \
    aubio/temporal/filter.c \
    aubio/temporal/resampler.c \
    aubio/utils/hist.c \
    aubio/utils/parameter.c \
    aubio/utils/scale.c \
    aubio/cvec.c \
    aubio/fmat.c \
    aubio/fvec.c \
    aubio/lvec.c \
    aubio/mathutils.c \
    aubio/vecutils.c \
    audioanalyser.cpp \
    notedata.cpp \
    ui/uirecorder.cpp \
    ui/uitrackactionpanel.cpp \
    ui/uitrackframe.cpp \
    ui/uitrackmidipanel.cpp \
    controllers/tracksmanager.cpp \
    controllers/track.cpp \
    controllers/maincontroller.cpp \
    QMidi/QMidiFile.cpp \
    QMidi/QMidiOut.cpp \
    controllers/midiplayer.cpp \
    ui/uiactionbuttonsframe.cpp \
    ui/uirecordergraph.cpp

HEADERS += \
    mainwindow.h \
    midicomposer.h \
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
    jdksmidi/world.h \
    aubio/io/audio_unit.h \
    aubio/io/sink.h \
    aubio/io/sink_apple_audio.h \
    aubio/io/sink_sndfile.h \
    aubio/io/sink_wavwrite.h \
    aubio/io/source.h \
    aubio/io/source_apple_audio.h \
    aubio/io/source_avcodec.h \
    aubio/io/source_sndfile.h \
    aubio/io/source_wavread.h \
    aubio/onset/onset.h \
    aubio/onset/peakpicker.h \
    aubio/pitch/pitch.h \
    aubio/pitch/pitchfcomb.h \
    aubio/pitch/pitchmcomb.h \
    aubio/pitch/pitchschmitt.h \
    aubio/pitch/pitchspecacf.h \
    aubio/pitch/pitchyin.h \
    aubio/pitch/pitchyinfft.h \
    aubio/spectral/fft.h \
    aubio/spectral/filterbank.h \
    aubio/spectral/filterbank_mel.h \
    aubio/spectral/mfcc.h \
    aubio/spectral/phasevoc.h \
    aubio/spectral/specdesc.h \
    aubio/spectral/tss.h \
    aubio/synth/sampler.h \
    aubio/synth/wavetable.h \
    aubio/tempo/beattracking.h \
    aubio/tempo/tempo.h \
    aubio/temporal/a_weighting.h \
    aubio/temporal/biquad.h \
    aubio/temporal/c_weighting.h \
    aubio/temporal/filter.h \
    aubio/temporal/resampler.h \
    aubio/utils/hist.h \
    aubio/utils/parameter.h \
    aubio/utils/scale.h \
    aubio/aubio.h \
    aubio/aubio_priv.h \
    aubio/config.h \
    aubio/cvec.h \
    aubio/fmat.h \
    aubio/fvec.h \
    aubio/lvec.h \
    aubio/mathutils.h \
    aubio/musicutils.h \
    aubio/types.h \
    aubio/vecutils.h \
    audioanalyser.h \
    notedata.h \
    ui/uirecorder.h \
    ui/uitrackactionpanel.h \
    ui/uitrackframe.h \
    ui/uitrackmidipanel.h \
    controllers/tracksmanager.h \
    controllers/track.h \
    controllers/maincontroller.h \
    QMidi/QMidiFile.h \
    QMidi/QMidiOut.h \
    controllers/midiplayer.h \
    ui/uiactionbuttonsframe.h \
    ui/uirecordergraph.h
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


LIBS += -LC:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d


INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include

#include "audioanalyser.h"

AudioAnalyser::AudioAnalyser()
{

    m_sndBuffer = new sf::SoundBuffer();
    m_sound = new sf::Sound();

    m_winSize = 2048; // window size
    m_hopSize = m_winSize / 4; // hop size
    m_samplerate = 44100; // samplerate

    //create pitch object
    m_aubioPitchObject = new_aubio_pitch ("fcomb", m_winSize, m_hopSize, m_samplerate);

}

void AudioAnalyser::loadSound(){
    QDir dir;
    std::string path = dir.currentPath().toStdString()+"/la.wav";

    bool res = false;
    try{
        res = m_sndBuffer->loadFromFile(path);
    }catch( std::exception & e){
        qDebug() << e.what();
    }

    if( res ){
        qDebug() << "Succeeded To Load File";
        m_sound = new sf::Sound();
        m_sound->setBuffer(*m_sndBuffer);
        processSound();
        //sound->play();
    }else{
        qDebug() << "Failed To Load File";
    }
}

void AudioAnalyser::processSound(){

    //Go through the entire audio and process sample frames
    const short int* samples = m_sndBuffer->getSamples();
    int totalSize = m_sndBuffer->getSampleCount();

    findVoices(samples,totalSize);
    return;

    //data containing values for a frame
    short int frameSamples [m_hopSize];
    //index of the current signal value
    int index = 0;
    int curSampleCount = 0;

    while(index < totalSize ){
        //qDebug() << *(samples+count);
        curSampleCount++;
        index++;
        frameSamples[curSampleCount] = *(samples + index);
        if( curSampleCount >= m_hopSize ){
            curSampleCount =0;
            processFrame(frameSamples,m_hopSize);
        }
    }

    qDebug() << "total sample count";
    qDebug() << m_sndBuffer->getSampleCount();
}

void AudioAnalyser::fillInputData( short int * _input, fvec_t * _output, int _count){
    int i = 0;
    short int temp;
    while(i < _count){
        temp = *(_input+i);
        _output->data[i] = temp;
        i++;
    }
}

void AudioAnalyser::processFrame(short int * _frameSample, int _count){

    // create some vectors
    fvec_t *input = new_fvec (m_hopSize); // input buffer
    fvec_t *out = new_fvec (1); // output candidates

    //Get frameSample values and put them into the right format for aubio
    //the values will be stored in the input variable
    fillInputData(_frameSample,input,m_winSize);

    //do the pitch detection process
    aubio_pitch_do(m_aubioPitchObject,input,out);

    qDebug() << "pitch";
    qDebug() << out->data[0];
    int note = log( out->data[0]/440.0)/log(2) * 12 + 69;
    qDebug() << "note";
    qDebug() << note;

    del_fvec(out);
    del_fvec(input);
}

void AudioAnalyser::findVoices(const short int * _audio,int _length){

}

AudioAnalyser::~AudioAnalyser()
{
    del_aubio_pitch( m_aubioPitchObject);
}


#include "uirecorder.h"
#include "controllers/maincontroller.h"
#include <QDir>

UIRecorder::UIRecorder(MainController * _mc) : QFrame(0)
{
    m_mainController = _mc;

    m_samples = std::vector<short int>();

    createInputOuptutDevice();

    //Layout holding left panel(actions) and right panel (audio graph)
    QHBoxLayout * mainLayout = new QHBoxLayout();

    //LEFT PANEL========================
    QFrame * leftPanel = new QFrame(); // left Panel widget
    QVBoxLayout * vLayout = new QVBoxLayout(); // Vertical layout for left panel
    //Title
    QLabel * title = new QLabel("AudioRecorder");
    title->setMaximumHeight( 20 );
    vLayout->addWidget(title);

    //Buttons
        QWidget * btnsWidget = new QWidget();
        QHBoxLayout * hLayout = new QHBoxLayout();

        QPushButton * playButton = new QPushButton(">");
        QObject::connect(playButton, SIGNAL(clicked()), this, SLOT(play())) ;

        QPushButton * recordButton = new QPushButton("O");
        QObject::connect(recordButton, SIGNAL(clicked()), this, SLOT(record())) ;

        QPushButton * stopButton = new QPushButton("[]");
        QObject::connect(stopButton, SIGNAL(clicked()), this, SLOT(stop())) ;        

        hLayout->addWidget(playButton);
        hLayout->addWidget(recordButton);
        hLayout->addWidget(stopButton);
        btnsWidget->setLayout(hLayout);

        //buttons for converting
        QWidget * btnsWidget2 = new QWidget();
        QHBoxLayout * hLayout2 = new QHBoxLayout();

        QPushButton * buildButton = new QPushButton("B");
        QObject::connect(buildButton, SIGNAL(clicked()), this, SLOT(convertToMidi())) ;

        m_noiseSpBox = new QSpinBox();
        m_noiseSpBox->setValue(m_mainController->getAudioAnalyser()->getNoiseThreshold());
        m_noiseSpBox->setMinimum(0);
        QObject::connect(m_noiseSpBox,SIGNAL(valueChanged(int)),this,SLOT(onNoiseValueChanged()));

        hLayout2->addWidget(m_noiseSpBox);
        hLayout2->addWidget(buildButton);
        btnsWidget2->setLayout(hLayout2);

    //end Buttons

    leftPanel->setFixedSize(200,180);
    leftPanel->setFrameStyle(QFrame::Box);

    vLayout->addWidget(btnsWidget); //add widget to vertical layout for left panel
    vLayout->addWidget(btnsWidget2);
    leftPanel->setLayout(vLayout); //set left panel main layout ( vertical )

    //===========================leftpanel

    //RIGHT PANEL==================
    m_graph = new UIRecorderGraph();
    //==================rightpanel

    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(m_graph);

    this->setLayout(mainLayout);
    this->adjustSize();

    m_state = "idle";
}

void UIRecorder::record(){
    qDebug() << "RECORD";

    m_inputIODevice = m_audioInput->start();
    connect(m_inputIODevice, SIGNAL(readyRead()), this,SLOT(readMore()));

    m_state = "recording";

    m_graph->onRecordingStart();
}

void UIRecorder::stop(){
    qDebug() << "STOP";

    if( m_state == "recording" ){
        m_audioInput->stop();

        //m_graph->onRecordingStop(m_sndBuffer);

    }else if( m_state == "playing"){
        m_audioOutput->stop();
        m_graph->onPlayStop();
    }
    m_state = "idle";
}

void UIRecorder::play(){
    qDebug() << "PLAY" ;
    m_state = "playing";

    m_audioOutput->start(m_outputBuffer);
    m_graph->onPlayStart();
}

void UIRecorder::convertToMidi(){
    //Load file ( DEBUG)
    //m_sndBuffer->loadFromFile( QDir::currentPath().toStdString()+"/ex_sound.wav" );

    //m_mainController->analyseSound(&m_samples,this);
}

//===================================
//======== SLOTS ====================
//===================================

void UIRecorder::onAudioInputStateChanged(QAudio::State _newState){
    //qDebug() <<"NEW STATE " << _newState;
}

void UIRecorder::readMore(){
    //Return if audio input is null
    if(!m_audioInput)
        return;

    //Check the number of samples in input buffer
    qint64 readyCount = m_audioInput->bytesReady();

    //Limit sample size to avoid out of bounds of the buffer
    if(readyCount > BUFFER_SIZE -1){
        qDebug() << "WARNING : bytes length oversize ("<< readyCount <<"). It may create holes in the sample";
        readyCount = BUFFER_SIZE-1;
    }
    //Read sound samples from input device to buffer
    qint64 l = m_inputIODevice->read(m_byteArrayBuffer->data(), readyCount);

    //how many bytes for a data ( divide by 8 bits )
    const int channelBytes = m_format.sampleSize() / 8;
    const int sampleBytes = m_format.channelCount() * channelBytes;
    //how many samples we have in the buffer
    const int numSamples = l / sampleBytes;

    //pointer on the first value in the buffer
    const unsigned char *ptr = reinterpret_cast<const unsigned char *>(m_byteArrayBuffer->data());

    if(l > 0)
    {
        //append to output buffer for playback
        m_outputBuffer->buffer().append(m_byteArrayBuffer->data(),l);

        for( int i = 0; i < numSamples; i ++){
            //convert data into a value ( here we need 2 bytes for an int )
            qint16 value = qFromLittleEndian<quint16>(ptr);
            //keep the value
            m_samples.push_back(value);
            //go to next value
            ptr += channelBytes;
        }
        m_graph->onRecordingProcess(&m_samples);
        /*
        //Noise reduction algorithm, not used yet
        int iIndex;
        //Remove noise using Low Pass filter algortm[Simple algorithm used to remove noise]
        for ( iIndex=1; iIndex < readyCount; iIndex++ )
        {
            outdata[ iIndex ] = 0.333 * resultingData[iIndex ] + ( 1.0 - 0.333 ) * outdata[ iIndex-1 ];
        }*/

    }
}

//==================================
//========CALLBACKS=================
//==================================

void UIRecorder::onAnalyseFailed(){

}

void UIRecorder::onNoiseValueChanged(){
    m_mainController->getAudioAnalyser()->setNoiseThreshold(m_noiseSpBox->value());
}

//SETTERS
void UIRecorder::setMainController(MainController * mc){
    m_mainController = mc;
}

void UIRecorder::createInputOuptutDevice(){
    //QT AUDIO
    m_format.setCodec("audio/PCM");
    m_format.setSampleRate(44100);
    m_format.setSampleSize(16);
    m_format.setChannelCount(1);
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(m_format)) {
        qWarning()<<"default format not supported try to use nearest";
        m_format = info.nearestFormat(m_format);
    }
    //input
    m_inputDeviceInfo = QAudioDeviceInfo::defaultInputDevice();
    m_audioInput = new QAudioInput(m_inputDeviceInfo, m_format,this);
    connect(m_audioInput,SIGNAL(stateChanged(QAudio::State)),this,SLOT(onAudioInputStateChanged(QAudio::State)));
    m_inputIODevice =0;
    //output
    m_outputDeviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    m_audioOutput = new QAudioOutput(m_outputDeviceInfo,m_format,this);
    m_outputIODevice = 0;

    m_byteArrayBuffer = new QByteArray(BUFFER_SIZE,0);
    m_outputBuffer = new QBuffer();
    m_outputBuffer->open(QIODevice::ReadWrite);
}

UIRecorder::~UIRecorder()
{
}


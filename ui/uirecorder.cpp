#include "uirecorder.h"
#include "controllers/maincontroller.h"

UIRecorder::UIRecorder(MainController * _mc) : QFrame(0)
{
    m_mainController = _mc;

    m_sfRecorder = new CustomRecorder();
    m_sndBuffer = new sf::SoundBuffer();
    m_sfSound = new sf::Sound();

    m_timerRecord = new QTimer();
    QObject::connect( m_timerRecord,SIGNAL(timeout()),this,SLOT(onTimerRecordTimeOut()) );

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
    m_sfRecorder->start(44100);
    m_state = "recording";
    m_timerRecord->start(100);
    m_graph->onRecordingStart();
}

void UIRecorder::stop(){
    qDebug() << "STOP";

    if( m_state == "recording" ){
        m_sfRecorder->stop();
        const sf::SoundBuffer& buffer = m_sfRecorder->getBuffer();
        //keep a copy
        m_sndBuffer->loadFromSamples(buffer.getSamples(),buffer.getSampleCount(),
                                     buffer.getChannelCount(), buffer.getSampleRate());
        //qDebug() << m_sndBuffer->getSampleCount();

        m_graph->onRecordingStop(m_sndBuffer);
        m_timerRecord->stop();

    }else if( m_state == "playing"){
        m_sfSound->stop();
    }
    m_state = "idle";
}

void UIRecorder::play(){
    qDebug() << "PLAY" << this;
    m_state = "playing";
    m_sfSound->setBuffer(*m_sndBuffer);
    m_sfSound->play();
}

void UIRecorder::convertToMidi(){
    //Load file ( DEBUG)
    m_sndBuffer->loadFromFile( QDir::currentPath().toStdString()+"/ex_sound.wav" );

    qDebug() << m_sndBuffer->getSampleCount();
    m_mainController->analyseSound(m_sndBuffer->getSamples(),m_sndBuffer->getSampleCount(),this);
}

//===================================
//======== SLOTS ====================
//===================================

void UIRecorder::onTimerRecordTimeOut(){
    if( m_state == "recording" ){
        m_graph->onRecordingProcess(m_sfRecorder->getSamples());
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

UIRecorder::~UIRecorder()
{
    delete m_sndBuffer;
    delete m_sfRecorder;
    delete m_sfSound;
}


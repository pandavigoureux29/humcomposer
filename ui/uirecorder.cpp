#include "uirecorder.h"

UIRecorder::UIRecorder(QWidget *parent) : QFrame(parent)
{

    m_sfRecorder = new sf::SoundBufferRecorder();
    m_sndBuffer = new sf::SoundBuffer();
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
    //end Buttons

    leftPanel->setFixedSize(200,150);
    leftPanel->setFrameStyle(QFrame::Box);

    vLayout->addWidget(btnsWidget); //add widget to vertical layout for left panel
    leftPanel->setLayout(vLayout); //set left panel main layout ( vertical )

    //===========================leftpanel

    //RIGHT PANEL==================
    QFrame * rightPanel = new QFrame();

    rightPanel->setMinimumWidth(500);
    rightPanel->setFixedHeight(150);

    rightPanel->setFrameStyle(QFrame::Box);
    //==================rightpanel

    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightPanel);

    this->setLayout(mainLayout);
    this->adjustSize();
}

void UIRecorder::record(){
    qDebug() << "RECORD";
    //m_sfRecorder->start(44100);

}

void UIRecorder::stop(){
    qDebug() << "STOP";
    //m_sfRecorder->stop();
    const sf::SoundBuffer& buffer = m_sfRecorder->getBuffer();

    //Load file ( DEBUG)
    sf::SoundBuffer * tempBuff = new sf::SoundBuffer();
    bool res = tempBuff->loadFromFile( QDir::currentPath().toStdString()+"/la.wav" );
    if(!res) return;
    qDebug() << tempBuff->getSampleCount();
    m_mainController->analyseSound(tempBuff->getSamples(),tempBuff->getSampleCount());
    return;

    //keep a copy
    m_sndBuffer->loadFromSamples(buffer.getSamples(),buffer.getSampleCount(),
                                 buffer.getChannelCount(), buffer.getSampleRate());
    //analyse the recorded sound
    m_mainController->analyseSound(buffer.getSamples(),buffer.getSampleCount());
}

void UIRecorder::play(){
    qDebug() << "PLAY";
    /*m_sfSound = new sf::Sound();
    m_sfSound->setBuffer(*m_sndBuffer);
    m_sfSound->play();
    */
}

//SETTERS
void UIRecorder::setMainController(MainController * mc){
    m_mainController = mc;
}

void UIRecorder::setOnRecordedCallback(){
}

UIRecorder::~UIRecorder()
{

}


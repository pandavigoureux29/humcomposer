#include "uirecordergraph.h"

UIRecorderGraph::UIRecorderGraph() : QFrame(0)
{
    m_xBarRange = 1000;
    m_xPlotRange = 100; m_yPlotRange = 500;
    m_currentSampleIndex = 0;
    m_xScale = 0.001;
    m_yScale = 0.03;
    //vertical layout
    QVBoxLayout * vLayout = new QVBoxLayout();

    //widget containing horizontal layout (Graph + ScrollBar Vert)
    QWidget * frameWidget = new QWidget();
    QHBoxLayout * horizontalLayout = new QHBoxLayout();

    setupPlot();
    horizontalLayout->addWidget(m_plot);

    frameWidget->setLayout(horizontalLayout);
    vLayout->addWidget(frameWidget);


    m_horizBar = new QScrollBar(Qt::Orientation::Horizontal);
    m_horizBar->setRange(0,m_xPlotRange * 100);
    vLayout->addWidget(m_horizBar);
    QObject::connect(m_horizBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));

    this->setMinimumWidth(800);
    this->setFixedHeight(230);

    this->setFrameStyle(QFrame::Box);
    this->setLayout(vLayout);
}

void UIRecorderGraph::buildGraphFromBuffer(std::vector<short int> * _samples){

}


//===================================
//          RECORDING
//===================================

void UIRecorderGraph::onRecordingStart(){
    m_currentSampleIndex = 0;
}

void UIRecorderGraph::onRecordingProcess(std::vector<short int> * _samples){

    //compute how many samples we have to process from last time
    int newSampleSize = _samples->size() - m_currentSampleIndex;

    //keep size in case it changes during process ( recording is asynchronous )
    int totalSampleBuffer = _samples->size();

    QVector<double> x(newSampleSize+1), y(newSampleSize+1); // initialize with entries 0..100
    for (int i= m_currentSampleIndex; i < _samples->size(); i ++)
    {
      int index = i - m_currentSampleIndex;
      if( index < x.size() ){
          x[index] = i * m_xScale ;
          y[index] = (double) abs( _samples->at(i) * m_yScale );
      }
    }

    //change plot range
    float maxCurrentX = _samples->size() * m_xScale;
    //qDebug() << maxCurrentX << " " << m_plot->xAxis->range().size();
    if( maxCurrentX > m_xPlotRange){
        m_xPlotRange = (int) maxCurrentX;
        m_plot->xAxis->setRange(0, m_xPlotRange, Qt::AlignLeft);
    }

    //m_plot->graph(0)->setData(x, y);
    m_plot->graph()->addData(x,y);
    m_plot->replot();

    m_currentSampleIndex= totalSampleBuffer;

}

void UIRecorderGraph::onRecordingStop(){

}

//===================================
//              PLAY
//===================================

void UIRecorderGraph::onPlayStart(){

}

void UIRecorderGraph::onPlayProgress(int _sampleCount){
    float currentX = _sampleCount * m_xScale;
}

void UIRecorderGraph::onPlayStop(){

}

void UIRecorderGraph::setupPlot(){
    m_plot = new QCustomPlot();
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i * 1000; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    m_plot->addGraph();
    m_plot->graph(0)->setData(x, y);

    // set axes ranges, so we see all data:
    m_plot->setInteractions(QCP::iRangeDrag);

    // initialize axis range
    m_plot->xAxis->setRange(0, m_xPlotRange, Qt::AlignLeft);
    m_plot->yAxis->setRange(0, 100);

    // create connection between axes and scroll bars:
    QObject::connect(m_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));

    m_plot->replot();
}

void UIRecorderGraph::horzScrollBarChanged(int value)
{
  //qDebug() << "horScrBarChgd " << value << " "<< m_plot->xAxis->range().size();
  if (qAbs(m_plot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
  {
    //m_plot->xAxis->setRange(value/100.0, m_plot->xAxis->range().size(), Qt::AlignCenter);
    m_plot->xAxis->setRange(value /100.0, m_plot->xAxis->range().size(), Qt::AlignLeft);
    m_plot->replot();
  }
}

void UIRecorderGraph::xAxisChanged(QCPRange range)
{
  //qDebug() << "range changed " << range.size();
  m_horizBar->setValue(qRound(range.lower*100.0)); // adjust position of scroll bar slider
  m_horizBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}


UIRecorderGraph::~UIRecorderGraph()
{

}


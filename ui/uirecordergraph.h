#ifndef UIRECORDERGRAPH_H
#define UIRECORDERGRAPH_H

#include <QFrame>
#include <QWidget>
#include <SFML/Audio.hpp>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollBar>

#include <math.h>

#include "QCustomPlot/qcustomplot.h"

class UIRecorderGraph : public QFrame
{
    Q_OBJECT

public:
    UIRecorderGraph();
    ~UIRecorderGraph();

    void buildGraphFromBuffer(sf::SoundBuffer * m_sfBuffer);
    void setInfoText(std::string _infoText);

public slots:
  void horzScrollBarChanged(int value);
  void xAxisChanged(QCPRange range);


  //Recording
  void onRecordingStart();
  void onRecordingProcess(std::vector<short int> * samples);
  void onRecordingStop(sf::SoundBuffer * _sndBuffer);
  //Play
  void onPlayStart();
  void onPlayProgress(int sampleCount);
  void onPlayStop();

private :
    QCustomPlot * m_plot;
    int m_currentSampleIndex;

    QScrollBar * m_horizBar;

    int m_xBarRange;
    int m_xPlotRange;
    int m_yPlotRange;

    float m_xScale;

    void setupPlot();

};

#endif // UIRECORDERGRAPH_H

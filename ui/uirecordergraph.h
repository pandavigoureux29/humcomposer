#ifndef UIRECORDERGRAPH_H
#define UIRECORDERGRAPH_H

#include <QFrame>
#include <QWidget>
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

    void buildGraphFromBuffer(std::vector<short int> * buffer);
    void setInfoText(std::string _infoText);

public slots:
  void horzScrollBarChanged(int value);
  void xAxisChanged(QCPRange range);


  //Recording
  void onRecordingStart();
  void onRecordingProcess(std::vector<short int> * samples);
  void onRecordingStop();
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
    float m_yScale;

    int m_lastBarCountTime;

    void setupPlot();
    void addTimeBar(int sampleCountBegin);

};

#endif // UIRECORDERGRAPH_H

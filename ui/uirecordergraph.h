#ifndef UIRECORDERGRAPH_H
#define UIRECORDERGRAPH_H

#include <QFrame>
#include <QWidget>
#include <SFML/Audio.hpp>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

class UIRecorderGraph : public QFrame
{
public:
    UIRecorderGraph();
    ~UIRecorderGraph();

    void buildGraphFromBuffer(sf::SoundBuffer * m_sfBuffer);
    void setInfoText(std::string _infoText);

private :
    QLabel * m_infoLabel;

};

#endif // UIRECORDERGRAPH_H

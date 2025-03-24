#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QDragEnterEvent>
#include <QDrag>
#include <QMimeData>
#include <vector>
#include <QMediaPlayer>
#include <QVideoSink>

#include "videoclip.h"

class Timeline : public QWidget
{
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent = nullptr);

    void addClip(VideoClip* clip);

private:
    QVBoxLayout* mainLayout;
    QSlider* progressSlider;
    QHBoxLayout* sliderLayout;
    QHBoxLayout* clipTimeline;
    QWidget* emptyWidget;
    QPalette pallette;

    std::vector<VideoClip*> clips;
    QMediaPlayer* player;
    QVideoSink* sink;


    QString testString;



protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


signals:
    void droppedClip(QString path, int width);
};

#endif // TIMELINE_H

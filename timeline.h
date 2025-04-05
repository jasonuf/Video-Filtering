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
#include <QLabel>

#include "videoclip.h"

class Timeline : public QWidget
{
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent = nullptr);

    void addClip(VideoClip* clip);
    bool hasClip(VideoClip* clip);

private:
    QVBoxLayout* mainLayout;
    QSlider* progressSlider;
    QHBoxLayout* sliderLayout;
    QHBoxLayout* clipTimeline;
    QWidget* spacerWidget;

    std::vector<QLabel*> timelineLabels;
    bool hasLoadedOnce;
    int displayHeight;
    int displayWidth;
    int numDisplays;

    //void updateTimelineLabels();

    QWidget* emptyWidget;
    QPalette pallette;

    std::vector<VideoClip*> clips;
    QMediaPlayer* player;
    QVideoSink* sink;


    qint64 timelinePos;

    QString testString;



protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void resizeEvent(QResizeEvent *event);


signals:
    void droppedClip(QString path, int width);
};

#endif // TIMELINE_H

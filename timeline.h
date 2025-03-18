#ifndef TIMELINE_H
#define TIMELINE_H

#include <QObject>
#include <vector>
#include "videoclip.h"
#include <QVideoWidget>

class Timeline : public QObject
{
    Q_OBJECT
public:
    explicit Timeline(QObject *parent = nullptr);
    ~Timeline();


public slots:

    void currentClipActivated(VideoClip* clip);


    void addClip(VideoClip *clip);
    void play();
    void isFinished(qint64 pos);

    void setVideoWidget(QVideoWidget* w) {videoWidget= w;};

private:
    std::vector<VideoClip*> clips;

    QVideoWidget* videoWidget;

    qint64 clipDuration;

    qint64 currentPosition;
    unsigned int currentClipIndex;

signals:
};

#endif // TIMELINE_H

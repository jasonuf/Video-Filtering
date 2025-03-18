#ifndef TIMELINE_H
#define TIMELINE_H

#include <QObject>
#include <vector>
#include "videoclip.h"
#include <QVideoWidget>
#include  <QStackedWidget>

class Timeline : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent = nullptr);
    ~Timeline();


    void switchStackIndex();

public slots:


    //void setVideoWidget(QVideoWidget* w) {videoWidget= w;};

    void addClip(VideoClip *clip);
    void playFromBeginning();

    void loadClip(uint index);
    void playClip(uint index);
    void isFinished(qint64 pos);



private:
    bool isPreLoaded;
    bool isPrePlayed;

    QVideoWidget* internalWidget0;
    QVideoWidget* internalWidget1;

    //QVideoWidget* videoWidget;

    std::vector<VideoClip*> clips;
    qint64 currentClipDuration;
    qint64 currentLoadThreshHold;

    qint64 currentPosition;
    unsigned int currentClipIndex;

signals:
};

#endif // TIMELINE_H

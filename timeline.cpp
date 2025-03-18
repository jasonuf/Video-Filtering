#include "timeline.h"

Timeline::Timeline(QObject *parent)
    : QObject{parent}
{
    clipDuration = 0;
    currentPosition = 0;
    currentClipIndex = 0;
    videoWidget = nullptr;
}

Timeline::~Timeline()
{

}


void Timeline::addClip(VideoClip *clip)
{
    clips.push_back(clip);
}

void Timeline::play()
{
    if (clips.empty()){
        return;
    }

    this->currentClipActivated(clips[currentClipIndex]);

    // for (VideoClip* clip : clips){
    //     clip->setClipWidget(videoWidget);
    //     clip->playPlayer();
    //     clipDuration = clip->getClipPlayer()->duration();
    //     connect(clip->getClipPlayer(), &QMediaPlayer::positionChanged, this, &Timeline::currentClipActivated );
    // }
}


void Timeline::currentClipActivated(VideoClip* clip)
{
    clip->setClipWidget(videoWidget);
    clip->setClipSink(videoWidget);
    connect(clip->getClipPlayer(), &QMediaPlayer::positionChanged, this, &Timeline::isFinished);
    clip->playPlayer();
    clipDuration = clip->getClipDuration();
    qInfo() << clipDuration;

}

void Timeline::isFinished(qint64 pos)
{

    clipDuration = clips[currentClipIndex]->getClipDuration();
    qInfo() << "changed position: " << pos;
    qInfo() << "clipDuration: " << clips[currentClipIndex]->getClipDuration();

    if (pos < clipDuration || clipDuration == 0){
        qInfo() << "returned";
        return;
    }


    disconnect(clips[currentClipIndex]->getClipPlayer(), &QMediaPlayer::positionChanged, this, &Timeline::isFinished);
    clips[currentClipIndex]->setClipSink(static_cast<QVideoSink*>(nullptr));
    clips[currentClipIndex]->setClipWidget(nullptr);

    currentClipIndex += 1;

    if (currentClipIndex >= clips.size()){
        currentClipIndex = 0;
        qInfo() << "Timeline done";
        return;
    }

    this->currentClipActivated(clips[currentClipIndex]);
}

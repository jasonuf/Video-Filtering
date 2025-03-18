#include "timeline.h"

Timeline::Timeline(QWidget *parent)
    : QStackedWidget(parent)
{


    currentClipDuration = 0;
    currentPosition = 0;
    currentClipIndex = 0;
    currentLoadThreshHold = 0;
    isPreLoaded = false;
    isPrePlayed = false;
    //videoWidget = nullptr;

    internalWidget0 = new QVideoWidget();
    internalWidget1 = new QVideoWidget();

    this->addWidget(internalWidget0);
    this->addWidget(internalWidget1);
    this->setCurrentIndex(0);

}

Timeline::~Timeline()
{
// delete only if there is no parent for widget objects!!!!
}

void Timeline::switchStackIndex()
{
    if (this->currentIndex() == 0){
        this->setCurrentIndex(1);
    }
    else{
        this->setCurrentIndex(0);
    }
}


void Timeline::addClip(VideoClip *clip)
{
    clips.push_back(clip);
}

void Timeline::playFromBeginning()
{
    if (clips.empty()){
        return;
    }

    loadClip(0);
    playClip(0);


    // for (VideoClip* clip : clips){
    //     clip->setClipWidget(videoWidget);
    //     clip->playPlayer();
    //     clipDuration = clip->getClipPlayer()->duration();
    //     connect(clip->getClipPlayer(), &QMediaPlayer::positionChanged, this, &Timeline::currentClipActivated );
    // }
}


void Timeline::loadClip(uint index)
{

    if (index % 2 == 0)
    {
        clips[index]->setClipWidget(internalWidget0);
        clips[index]->setClipSink(internalWidget0);
        connect(clips[index]->getClipPlayer(), &QMediaPlayer::positionChanged, this, &Timeline::isFinished);
        currentClipDuration = clips[index]->getClipDuration();
        qInfo() << currentClipDuration;
    }
    else
    {
        clips[index]->setClipWidget(internalWidget1);
        clips[index]->setClipSink(internalWidget1);
        connect(clips[index]->getClipPlayer(), &QMediaPlayer::positionChanged, this, &Timeline::isFinished);
        currentClipDuration = clips[index]->getClipDuration();
        qInfo() << currentClipDuration;
    }

}

void Timeline::playClip(uint index)
{
    clips[index]->playPlayer();
}

void Timeline::isFinished(qint64 pos)
{

    currentClipDuration = clips[currentClipIndex]->getClipDuration();
    currentLoadThreshHold = (currentClipDuration * 9) / 10;

    qInfo() << "changed position: " << pos;
    qInfo() << "clipDuration: " << clips[currentClipIndex]->getClipDuration();

    if (pos < currentLoadThreshHold || currentClipDuration == 0)
    {
        qInfo() << "Under Load Threshold";
        return;
    }
    else if (pos < currentClipDuration-500)
    {
        if (!isPreLoaded)
        {
            isPreLoaded = true;
            loadClip(currentClipIndex + 1);
            qInfo() << "Next Clip Loaded";
        }
        qInfo() << "Past Load Threshold";
        return;
    }
    else if (pos < currentClipDuration)
    {
        if (!isPrePlayed){
            isPrePlayed = true;
            playClip(currentClipIndex+1);
        }
        return;
    }

    switchStackIndex();


    if (currentClipIndex + 2 == clips.size())
    {
        isPreLoaded = true;
        isPrePlayed = true;
    }
    else
    {
        isPreLoaded = false;
        isPrePlayed = false;
    }


    disconnect(clips[currentClipIndex]->getClipPlayer(), &QMediaPlayer::positionChanged, this, &Timeline::isFinished);
    clips[currentClipIndex]->setClipSink(static_cast<QVideoSink*>(nullptr));
    clips[currentClipIndex]->setClipWidget(nullptr);

    currentClipIndex += 1;

    if (currentClipIndex >= clips.size()){
        currentClipIndex = 0;
        qInfo() << "Timeline done";
    }

}

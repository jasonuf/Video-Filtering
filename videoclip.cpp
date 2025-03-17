#include "videoclip.h"



VideoClip::VideoClip(QObject *parent)
: QObject{parent}
{
    this->setParent(parent);

    positionStart = 0;
    positionEnd = 0;

    clipSource = new QUrl(QUrl::fromLocalFile("C:/Users/Jason/Downloads/macdemarco.mp4"));

    clipPlayer = new QMediaPlayer(this->parent());
    clipSink = new QVideoSink(this->parent());

    clipPlayer->setSource(*clipSource);
    //clipPlayer->setVideoSink(clipSink);
    //clipPlayer->setVideoOutput(clipSink);


    connect(clipSink, &QVideoSink::videoFrameChanged, this, &VideoClip::frameDoSomething);
    connect(clipSink, &QVideoSink::videoSizeChanged, this, &VideoClip::frameDoSomething2);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VideoClip::frameDoSomething2);
    timer->start(1000);
}

VideoClip::~VideoClip()
{
    delete clipSource;
}

void VideoClip::setClipWidget(QVideoWidget* v)
{
    clipPlayer->setVideoOutput(v);

    QVideoSink* widgetSink = v->videoSink();
    if (widgetSink) {
        connect(widgetSink, &QVideoSink::videoFrameChanged, this, &VideoClip::frameDoSomething);
    }

}

void VideoClip::playPlayer()
{
    clipPlayer->play();

}

void VideoClip::frameDoSomething(const QVideoFrame &frame)
{
    qInfo() << "Anything";
    qInfo() <<  "height: " << frame.height();
    qInfo() <<  "isMapped: " << frame.isMapped();
}

void VideoClip::frameDoSomething2()
{
    qInfo() << "HI";
}



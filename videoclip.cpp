#include "videoclip.h"



VideoClip::VideoClip(QObject *parent)
: QObject{parent}
{
    this->setParent(parent);

    positionStart = 0;
    positionEnd = 0;

    clipSource = new QUrl(QUrl::fromLocalFile("C:/Users/Jason/Downloads/countdown.mp4"));


    // REVERSE THIS IF PLAYER.H DOES NOT WORK---------------------
    // clipPlayer = new QMediaPlayer(this->parent());
    // clipAudio = new QAudioOutput(this->parent());

    // clipPlayer->setAudioOutput(clipAudio);
    // clipPlayer->setSource(*clipSource);
    // REVERSE THIS IF PLAYER.H DOES NOT WORK---------------------

    //clipPlayer->setVideoSink(clipSink);
    //clipPlayer->setVideoOutput(clipSink);


    //connect(clipSink, &QVideoSink::videoFrameChanged, this, &VideoClip::frameDoSomething);
    //connect(clipSink, &QVideoSink::videoSizeChanged, this, &VideoClip::frameDoSomething2);


}

VideoClip::~VideoClip()
{
    delete clipSource;
}

void VideoClip::setClipWidget(QVideoWidget *v)
{


    clipPlayer->setVideoOutput(v);
}

void VideoClip::setClipSink(QVideoWidget *v)
{
    clipSink = v->videoSink();

    if (clipSink){
        connect(clipSink, &QVideoSink::videoFrameChanged, this, &VideoClip::frameDoSomething);
    }
}



void VideoClip::setClipSink(QVideoSink *sink)
{
    if (sink == nullptr){
        disconnect(clipSink, &QVideoSink::videoFrameChanged, this, &VideoClip::frameDoSomething);
    }
    clipSink = sink;


}


void VideoClip::playPlayer()
{
    clipPlayer->play();

}

void VideoClip::pausePlayer()
{
    clipPlayer->pause();
}

void VideoClip::frameDoSomething(const QVideoFrame &frame)
{

    static bool inFilter = false;
    if (inFilter)
        return;

    // Make a copy we can map (the QVideoFrame coming from the signal may be const)
    QVideoFrame copyFrame = frame;
    if (!copyFrame.isValid())
        return;

    // Map the frame for reading/writing pixel data
    if (!copyFrame.map(QVideoFrame::ReadWrite))
        return;

    // --- Perform your pixel manipulations here ---
    // For example, demonstrate inverting the color of each pixel
    // (Assuming an RGB-compatible format for simplicity)
    const int bytesPerLine = copyFrame.bytesPerLine(0);
    uchar *data = copyFrame.bits(0);
    const int height = copyFrame.height();
    const int width = copyFrame.width();

    // Very simple example: invert each pixel’s R, G, B
    for (int y = 0; y < height; ++y) {
        uchar *scanline = data + y * bytesPerLine;
        for (int x = 0; x < width * 3; x += 3) {
            // If the frame is RGB24-like: [R, G, B]
            scanline[x + 0] = 255 - scanline[x + 0]; // R
            scanline[x + 1] = 255 - scanline[x + 1]; // G
            scanline[x + 2] = 255 - scanline[x + 2]; // B
        }
    }


    // --- end of manipulation ---

    copyFrame.unmap();

    // Now push our modified frame back to the sink for display
    // Block recursion so we don’t re-enter this slot.
    inFilter = true;
    clipSink->setVideoFrame(copyFrame);
    inFilter = false;

}

void VideoClip::frameDoSomething2()
{
    qInfo() << "HI";
}



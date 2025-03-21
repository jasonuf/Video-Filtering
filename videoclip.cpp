#include "videoclip.h"


VideoClip::VideoClip(QObject *parent)
: QObject{parent}
{
    //initialize values
    positionStart = 0;
    positionEnd = 0;
    thumbnail = nullptr;
    clipSource = nullptr;

   // clipSource = QUrl::fromLocalFile("C:/Users/Jason/Downloads/countdown.mp4");


    // REVERSE THIS IF PLAYER.H DOES NOT WORK---------------------
    //Create Players for each clip with the sole purpose of capturing the thumbnail
    clipPlayer = new QMediaPlayer(this);
    clipSink = new QVideoSink(this);
    clipPlayer->setVideoSink(clipSink);

    //For every frame change, check the video position. When the position reaches 200ms, grab thumbnail
    connect(clipSink, &QVideoSink::videoFrameChanged, this, &VideoClip::waitForThumbnail);
    connect(clipPlayer, &QMediaPlayer::playbackStateChanged, this, &VideoClip::onMediaStop);
    clipPlayer->play();
}

VideoClip::~VideoClip()
{

    delete thumbnail;
    qInfo() << "Video Clip deleted: " << this;
    // if (clipPlayer) delete clipPlayer;
    // if (clipSink) delete clipSink;
}

void VideoClip::setSource(QUrl source)
{
    //Set the source and begin playing to capture thumbnail. !!!Possible issue if clipPlayer is already deleted!!!
    clipSource = source;

    if (clipPlayer)
    {
        qInfo() << "Set source";
        clipPlayer->setSource(clipSource);
        clipPlayer->play();
    }
}


void VideoClip::setFileName(QString str)
{
    fileName = str;
}

void VideoClip::onMediaStop(QMediaPlayer::PlaybackState newState)
{
    if (newState == QMediaPlayer::StoppedState)
    {
        disconnect(clipPlayer, &QMediaPlayer::playbackStateChanged, this, &VideoClip::onMediaStop);
        clipPlayer->deleteLater();
        clipSink->deleteLater();
    }
}

void VideoClip::waitForThumbnail(const QVideoFrame &frame)
{
    if (clipPlayer->position() >= 200) //when the position of the video for the source reaches 200ms
    {
        thumbnail = new QImage(frame.toImage()); //convert frame to QImage
        //Clean up player and sink to free memory and disconnect signal/slot, also send signal to let the Pool know that the clip's thumbnail is done uploading
        clipPlayer->stop();
        emit thumbNailLoaded();
        disconnect(clipSink, &QVideoSink::videoFrameChanged, this, &VideoClip::waitForThumbnail);
    }
}

/*

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

*/



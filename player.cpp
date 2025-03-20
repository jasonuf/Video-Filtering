#include "player.h"

Player::Player(QWidget *parent)
    : QVideoWidget(parent)
{

    //Initialize the player main components (QMediaPlayer, QAudioOutput). Then connect the signals and slots.
    mainPlayer = new QMediaPlayer(parent);
    mainAudio = new QAudioOutput(parent);
    mainPlayer->setVideoOutput(this);
    mainPlayer->setAudioOutput(mainAudio);


    connect(mainPlayer, &QMediaPlayer::positionChanged, this, &Player::whenPositionChanged);
    connect(mainPlayer, &QMediaPlayer::mediaStatusChanged, this, &Player::handleStatusChange);
    connect(this->videoSink(), &QVideoSink::videoFrameChanged, this, &Player::filterFrame); //-----MOVE THIS IF SOMETHING BREAKS TO->?????

    switchSourceTime = 0;
    currentClipIndex = 0;
    currentClipDuration = 0;

}

void Player::addClip(VideoClip *clip)
{
    clips.push_back(clip);
}

void Player::playFromBeginning()
{
    //Set the current playing clip to be the first Index.
    currentClipIndex = 0;
    //Get the clip's source based off the index and then connect the player's source to that. Then connect the
    mainPlayer->setSource(clips[currentClipIndex]->getClipSource());
    //?????????????????MOVE BACK HERE
    mainPlayer->play();
}

void Player::handleStatusChange(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia)
    {
        currentClipDuration = mainPlayer->duration();
        qInfo() << "Current Clip Duration set to: " << currentClipDuration;
    }
}

void Player::whenPositionChanged(qint64 pos)
{


    if (pos < currentClipDuration)
    {
        return;
    }

    currentClipIndex += 1;

    if (currentClipIndex == clips.size())
    {
        currentClipIndex = 0;
        return;
    }
    mainPlayer->setSource(clips[currentClipIndex]->getClipSource());
    mainPlayer->play();
}


void Player::filterFrame(const QVideoFrame &frame)
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
    this->videoSink()->setVideoFrame(copyFrame);
    inFilter = false;
}



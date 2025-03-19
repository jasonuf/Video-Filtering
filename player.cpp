#include "player.h"

Player::Player(QWidget *parent)
    : QVideoWidget(parent)
{
    mainPlayer = new QMediaPlayer(parent);
    mainAudio = new QAudioOutput(parent);
    mainPlayer->setVideoOutput(this);
    mainPlayer->setAudioOutput(mainAudio);


    connect(mainPlayer, &QMediaPlayer::positionChanged, this, &Player::whenPositionChanged);

    switchSourceTime = 0;
    currentClipIndex = 0;

}

void Player::addClip(VideoClip *clip)
{
    clips.push_back(clip);
}

void Player::playFromBeginning()
{
    currentClipIndex = 0;
    mainPlayer->setSource(*clips[currentClipIndex]->getClipSource());
    connect(this->videoSink(), &QVideoSink::videoFrameChanged, this, &Player::filterFrame);
    mainPlayer->play();
}

void Player::whenPositionChanged(qint64 pos)
{
    switchSourceTime = mainPlayer->duration();
    qInfo() << "Main Player duration set to: " << switchSourceTime;

    if (pos < switchSourceTime)
    {
        return;
    }

    currentClipIndex += 1;

    if (currentClipIndex == clips.size())
    {
        currentClipIndex = 0;
        return;
    }
    mainPlayer->setSource(*clips[currentClipIndex]->getClipSource());
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

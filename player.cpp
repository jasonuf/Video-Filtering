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
    globalPosition = 0;
    currentClipEnd = 0;
    globalPositionReference = 0;

}

void Player::addClip(VideoClip *clip)
{
    clips.push_back(clip);
    startTimes.push_back(clip->getPositionStart());
    endTimes.push_back(clip->getPositionEnd());
    totalDuration+= clip->getPositionEnd() - clip->getPositionStart();
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

void Player::regularPlay()
{
    mainPlayer->play();
}

void Player::regularPause()
{
    mainPlayer->pause();
}

void Player::playFromPosition(qint64 pos)
{
    if(clips.empty())
    {
        return;
    }

    return;
}

void Player::handleStatusChange(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) //Only when the clip has loaded into the player can you take the duration
    {
        currentClipDuration = clips[currentClipIndex]->getPositionEnd() - clips[currentClipIndex]->getPositionStart();
        currentClipEnd = clips[currentClipIndex]->getPositionEnd();
        mainPlayer->setPosition(startTimes[currentClipIndex]);
        qInfo() << "Current Clip Duration set to: " << currentClipDuration;
    }
}

void Player::whenPositionChanged(qint64 pos)
{
    // globalPosition = 0;
    // for (int i = 0; i < currentClipIndex; ++i)
    // {
    //     globalPosition += endTimes[i] - startTimes[i];
    // }

    globalPosition = globalPositionReference + pos - startTimes[currentClipIndex];
    emit globalPosChanged(globalPosition);

    // Handle when player reaches the duration. Will change the clip's end later
    if (pos < currentClipEnd)
    {
        return;
    }
    //Since first clip is done playing, move onto next clip
    currentClipIndex += 1;

    //Check if clip is at the end of the player's list of clips and resets if true
    if (currentClipIndex == clips.size())
    {
        currentClipIndex = 0;
        mainPlayer->stop();
        return;
    }

    calculateGlobalPositionReference();
    mainPlayer->pause();
    mainPlayer->setSource(clips[currentClipIndex]->getClipSource()); //Sets the new source and plays, continueing the loop
    mainPlayer->play();
}


void Player::filterFrame(const QVideoFrame &frame)
{
    //temporary filter credit a la chat geepeeteee will handle later based on the clip's filters, last thing to do.
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

void Player::calculateGlobalPositionReference()
{
    globalPositionReference = 0;

    for (int i = 0; i < currentClipIndex; ++i)
    {
        globalPositionReference += endTimes[i] - startTimes[i];
    }
}



#ifndef PLAYER_H
#define PLAYER_H

#include <QVideoWidget>
#include <vector>
#include <QMediaPlayer>
#include <QVideoSink>
#include <QAudioOutput>

#include "videoclip.h"

class Player : public QVideoWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent = nullptr);

    int getCurrentClipIndex() const {return currentClipIndex;}
    QMediaPlayer::PlaybackState getPlaybackState() const {return mainPlayer->playbackState();}
    qint64 getTotalDuration() const {return totalDuration;}

public slots:
    void addClip(VideoClip *clip);

    void playFromBeginning();
    void regularPlay();
    void regularPause();
    void playFromPosition(qint64 pos);

private slots:

    void handleStatusChange(QMediaPlayer::MediaStatus status);
    void whenPositionChanged(qint64 pos);
    void filterFrame(const QVideoFrame &frame);


private:
    std::vector<VideoClip*> clips;
    std::vector<qint64> startTimes;
    std::vector<qint64> endTimes;
    qint64 totalDuration;


    QMediaPlayer* mainPlayer;
    QAudioOutput* mainAudio;

    qint64 switchSourceTime;
    uint currentClipIndex;
    qint64 currentClipDuration;
    qint64 currentClipEnd;
    qint64 globalPosition;
    qint64 globalPositionReference;


    void calculateGlobalPositionReference();

signals:

    void globalPosChanged(qint64 pos);

};

#endif // PLAYER_H

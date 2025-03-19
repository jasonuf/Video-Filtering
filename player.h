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

public slots:
    void addClip(VideoClip *clip);

    void playFromBeginning();

private slots:

    void whenPositionChanged(qint64 pos);
    void filterFrame(const QVideoFrame &frame);

private:
    std::vector<VideoClip*> clips;
    QMediaPlayer* mainPlayer;
    QAudioOutput* mainAudio;

    qint64 switchSourceTime;
    uint currentClipIndex;


};

#endif // PLAYER_H

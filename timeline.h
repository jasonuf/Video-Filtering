#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QDragEnterEvent>
#include <QDrag>
#include <QMimeData>
#include <vector>
#include <QMediaPlayer>
#include <QVideoSink>
#include <QLabel>
#include <QVideoFrame>
#include <QTimer>
#include "videoclip.h"

class Timeline : public QWidget
{
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent = nullptr);


    bool hasClip(VideoClip* clip);

public slots:
    void addClip(VideoClip* clip);
    void setSliderMaximum(qint64 max);
    void setSliderValue(qint64 value);

private:
    QVBoxLayout* mainLayout;
    QSlider* progressSlider;
    QHBoxLayout* sliderLayout;
    QHBoxLayout* clipTimeline;
    QWidget* spacerWidget;

    std::vector<QLabel*> timelineLabels;
    std::vector<QPixmap*> labelPics;

    std::vector<qint64> labelPos;
    bool isGenerating;
    bool hasFrameGenerated;
    int indexToGenerate;
    bool hasLoadedOnce;
    int displayHeight;
    int displayWidth;
    int numDisplays;

    qint64 totalDuration;

    //void updateTimelineLabels();

    QWidget* emptyWidget;
    QPalette pallette;

    std::vector<VideoClip*> clips;
    QMediaPlayer* player;
    QVideoSink* sink;


    qint64 timelinePos;

    QString testString;



protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void resizeEvent(QResizeEvent *event);
    void manageFrameChange(const QVideoFrame &frame);
    void managePlaybackState(QMediaPlayer::PlaybackState newState);
    void managePositionChanged(qint64 position);
    void manageSliderPressed();
    void manageSliderReleased();


signals:
    void droppedClip(QString path, int width);
    void clipAdded(VideoClip* clip);
    void tSliderPressed(bool val);
    void tSliderReleased(int pos);
};

#endif // TIMELINE_H

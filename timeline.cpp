#include "timeline.h"

Timeline::Timeline(QWidget *parent)
    : QWidget{parent}
{
    setAcceptDrops(true);
    timelinePos = 0;
    hasLoadedOnce = false;
    displayHeight = 0;
    displayWidth = 0;
    numDisplays = 0;

    player = new QMediaPlayer(this);
    sink = new QVideoSink(this);
    player->setVideoSink(sink);


    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    progressSlider = new QSlider(Qt::Horizontal,  this);
    sliderLayout = new QHBoxLayout();
    clipTimeline = new QHBoxLayout();

    sliderLayout->addWidget(progressSlider);

    emptyWidget = new QWidget(this);
    pallette = QPalette();
    pallette.setColor(QPalette::Window, QColor(26, 29, 33));
    emptyWidget->setAutoFillBackground(true);
    emptyWidget->setPalette(pallette);
    emptyWidget->setStyleSheet("border: 0.5px solid black;");

    clipTimeline->addWidget(emptyWidget);


    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(sliderLayout, 1);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(clipTimeline, 5);

    spacerWidget = new QWidget(this);
    mainLayout->addWidget(spacerWidget, 3);

    qInfo() << "TIMELINE GEOMETRY: " << clipTimeline->geometry();
    //this->setStyleSheet("border-width: 10px;border: 2px solid black;");
}

void Timeline::addClip(VideoClip *clip)
{
    clips.push_back(clip);
}

bool Timeline::hasClip(VideoClip *clip)
{
    for (int i = 0; i < clips.size(); ++i)
    {
        if (clip == clips[i])
        {
            return true;
        }
    }
    return false;
}


// void Timeline::updateTimelineLabels()
// {
//     for (int i = 0; i < clips.size(); ++i)
//     {
//         timelineLabels.push_back(new QLabel());
//     }
// }

void Timeline::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
    {
        event->acceptProposedAction();
    }
}

void Timeline::dropEvent(QDropEvent *event)
{

    testString = event->mimeData()->text();
    emit droppedClip(testString, event->position().toPoint().x());

}

void Timeline::resizeEvent(QResizeEvent *event)
{
    //qInfo() << "TimeLine size x: " <<  event->size().width() << " y: " << event->size().height();
    //qInfo() << "TIMELINE GEOMETRY: " << clipTimeline->geometry()->
    if (!hasLoadedOnce)
    {
        hasLoadedOnce = true;
        displayHeight = clipTimeline->geometry().height();
        displayWidth = (displayHeight / 9) * 16;
        numDisplays = clipTimeline->geometry().width() / displayWidth;

        qInfo() << "DISPLAY HEIGHT: " << displayHeight << " DISPLAY WIDTH: " << displayWidth << " NUMDISPLAYS: " << numDisplays;

        // for (int i = 0; i < numDisplays; ++i)
        // {

        // }
    }

}

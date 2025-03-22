#include "timeline.h"

Timeline::Timeline(QWidget *parent)
    : QWidget{parent}
{
    setAcceptDrops(true);

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
    emptyWidget->setStyleSheet("border: 1px solid black; background-color: rgb(26, 29, 33)");

    clipTimeline->addWidget(emptyWidget);


    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(sliderLayout, 1);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(clipTimeline, 5);
    //this->setStyleSheet("border-width: 10px;border: 2px solid black;");
}

void Timeline::addClip(VideoClip *clip)
{
    clips.push_back(clip);
    qInfo() << "Clip added to timeline";
}

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

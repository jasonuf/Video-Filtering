#include "clipdisplay.h"

ClipDisplay::ClipDisplay(QWidget *parent)
    : QWidget{parent}
{
    layout = new QVBoxLayout(this);
    layout->setSpacing(2);
    layout->setContentsMargins(2,2,2,2);
    layout->setAlignment(Qt::AlignTop);

    imageLabel = new QLabel();
    imageLabel->setFixedSize(125,70);

    fileLabel = new QLabel(clip->getFileName());
    fileLabel->setFixedSize(125,15);

    layout->addWidget(imageLabel);
    layout->addWidget(fileLabel);

    setLayout(layout);
}

ClipDisplay::ClipDisplay(QWidget *parent, VideoClip *clip) : QWidget{parent}
{
    this->clip = clip;

    layout = new QVBoxLayout(this);
    layout->setSpacing(2);
    layout->setContentsMargins(2,2,2,2);
    layout->setAlignment(Qt::AlignTop);

    imageLabel = new QLabel();
    imageLabel->setFixedSize(125,70);

    fileLabel = new QLabel(clip->getFileName());
    fileLabel->setFixedSize(125,15);

    layout->addWidget(imageLabel);
    layout->addWidget(fileLabel);

    setLayout(layout);

}

void ClipDisplay::mousePressEvent(QMouseEvent *event)
{
    emit clipClicked(clip);
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

void ClipDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength() < 15)
        return;

    qInfo() << this  << " item clicked";
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(clip->getClipSource().path());
    drag->setMimeData(mimeData);
    drag->setPixmap(imagePix.scaled(QSize(100,56), Qt::IgnoreAspectRatio));

    Qt::DropAction dropAction = drag->exec();
}




#include "videoplayer.h"
#include <QWidget>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}



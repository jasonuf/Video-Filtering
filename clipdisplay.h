#ifndef CLIPDISPLAY_H
#define CLIPDISPLAY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include "videoclip.h"

class ClipDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ClipDisplay(QWidget *parent = nullptr);
    ClipDisplay(QWidget* parent, VideoClip* clip);

    QVBoxLayout* layout;
    QLabel* imageLabel;
    QPixmap imagePix;
    QLabel* fileLabel;
    VideoClip* clip;
    QPoint dragStartPosition;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
signals:
};

#endif // CLIPDISPLAY_H

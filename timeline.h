#ifndef TIMELINE_H
#define TIMELINE_H

#include <QObject>
#include "videoclip.h"

class Timeline : public QObject
{
    Q_OBJECT
public:
    explicit Timeline(QObject *parent = nullptr);

signals:
};

#endif // TIMELINE_H

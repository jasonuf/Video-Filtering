#ifndef POOL_H
#define POOL_H
#include "videoclip.h"

#include <QWidget>
#include <vector>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>


class Pool : public QWidget
{
    Q_OBJECT
public:
    explicit Pool(QWidget *parent = nullptr);

    struct ClipDisplay : public QVBoxLayout
    {


        QLabel* imageLabel;
        QPixmap imagePix;
        QLabel* fileLabel;

        ClipDisplay(QWidget* parent, VideoClip* clip) : QVBoxLayout{parent}
        {

            imageLabel = new QLabel();
            imageLabel->setFixedSize(125,70);

            // imagePix = QPixmap::fromImage(*clip->getThumbnail());
            // imageLabel->setPixmap(imagePix);

            fileLabel = new QLabel(clip->getFileName());
            fileLabel->setFixedSize(125,15);

            addWidget(imageLabel);
            addWidget(fileLabel);
        }

    };

public slots:
    void addClips(QStringList* list);

    void addToPool(uint num);

    void displayThumbnail();


private:
    qint16 rows;
    qint16 cols;

    std::vector<VideoClip*> clips;
    std::vector<ClipDisplay*> clipDisplays;

    QVBoxLayout* masterLayout;

    QUrl tempUrl;
    QString tempFileName;

    QHBoxLayout* tempLayout;

    QLabel* testLabel;
    QWidget* testWidget;



signals:
};

#endif // POOL_H

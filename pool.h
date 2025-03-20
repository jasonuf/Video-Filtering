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
        QWidget* testWidget;

        ClipDisplay(QWidget* parent, VideoClip* clip) : QVBoxLayout{parent}
        {
            QPalette bluePal = QPalette();
            bluePal.setColor(QPalette::Window, Qt::blue);

            testWidget = new QWidget();
            testWidget->setAutoFillBackground(true);
            testWidget->setPalette(bluePal);
            testWidget->setFixedSize(150,75);

            imageLabel = new QLabel();
            imageLabel->setFixedSize(150,75);

            // imagePix = QPixmap::fromImage(*clip->getThumbnail());
            // imageLabel->setPixmap(imagePix);

            fileLabel = new QLabel(clip->getFileName());
            fileLabel->setFixedSize(150,25);

            addWidget(imageLabel);
            addWidget(fileLabel);
            addWidget(testWidget);
        }

    };

public slots:
    void addClips(QStringList* list);

    void addToPool(std::vector<VideoClip*> clipList);



private:
    std::vector<VideoClip*> clips;
    std::vector<VideoClip*> needToAddClips;
    QVBoxLayout* masterLayout;

    QUrl tempUrl;
    QString tempFileName;

    QHBoxLayout* tempLayout;

    QLabel* testLabel;
    QWidget* testWidget;



signals:
};

#endif // POOL_H

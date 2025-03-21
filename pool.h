#ifndef POOL_H
#define POOL_H
#include "videoclip.h"

#include <QWidget>
#include <vector>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class Pool : public QWidget
{
    Q_OBJECT
public:
    explicit Pool(QWidget *parent = nullptr);

    class ClipDisplay : public QWidget
    {
    public:
        QVBoxLayout* layout;
        QLabel* imageLabel;
        QPixmap imagePix;
        QLabel* fileLabel;

        ClipDisplay(QWidget* parent, VideoClip* clip) : QWidget{parent}
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

    };

public slots:
    void addClips(QStringList* list);

    void addToPool(uint num);

    void displayThumbnail();


private:
    qint16 lastRowIndex;
    qint16 availableCols;
    qint16 lastRowCols;


    std::vector<VideoClip*> clips;
    std::vector<ClipDisplay*> clipDisplays;
    std::vector<QHBoxLayout*> rowLayouts;

    QVBoxLayout* masterLayout;

    QUrl tempUrl;
    QString tempFileName;

    QHBoxLayout* tempLayout;

    QLabel* testLabel;
    QWidget* testWidget;

    void addRow();
    void removeRow();

protected:
    void resizeEvent(QResizeEvent *event) override;


signals:
};

#endif // POOL_H

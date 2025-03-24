#ifndef POOL_H
#define POOL_H
#include "videoclip.h"
#include "clipdisplay.h"

#include <QWidget>
#include <vector>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>
#include <QDrag>
#include <QMimeData>



class Pool : public QWidget
{
    Q_OBJECT
public:
    explicit Pool(QWidget *parent = nullptr);

    // class ClipDisplay : public QWidget
    // {
    // public:


    //     QVBoxLayout* layout;
    //     QLabel* imageLabel;
    //     QPixmap imagePix;
    //     QLabel* fileLabel;
    //     VideoClip* clip;
    //     QPoint dragStartPosition;



    //     ClipDisplay(QWidget* parent, VideoClip* clip) : QWidget{parent}
    //     {
    //         this->clip = clip;

    //         layout = new QVBoxLayout(this);
    //         layout->setSpacing(2);
    //         layout->setContentsMargins(2,2,2,2);
    //         layout->setAlignment(Qt::AlignTop);

    //         imageLabel = new QLabel();
    //         imageLabel->setFixedSize(125,70);

    //         fileLabel = new QLabel(clip->getFileName());
    //         fileLabel->setFixedSize(125,15);

    //         layout->addWidget(imageLabel);
    //         layout->addWidget(fileLabel);

    //         setLayout(layout);

    //     }


    // protected:
    //     void mousePressEvent(QMouseEvent *event)
    //     {

    //         if (event->button() == Qt::LeftButton)
    //             dragStartPosition = event->pos();
    //     }

    //     void mouseMoveEvent(QMouseEvent *event)
    //     {
    //         if (!(event->buttons() & Qt::LeftButton))
    //             return;
    //         if ((event->pos() - dragStartPosition).manhattanLength() < 15)
    //             return;

    //         qInfo() << this  << " item clicked";
    //         QDrag *drag = new QDrag(this);
    //         QMimeData *mimeData = new QMimeData;

    //         mimeData->setText(clip->getClipSource().path());
    //         drag->setMimeData(mimeData);
    //         drag->setPixmap(imagePix.scaled(QSize(100,56), Qt::IgnoreAspectRatio));

    //         Qt::DropAction dropAction = drag->exec();
    //     }


    // };



    std::vector<VideoClip*>& getClips();
    void sendClipToPool(VideoClip* clip);

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

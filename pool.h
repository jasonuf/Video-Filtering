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

    std::vector<VideoClip*>& getClips();
    void sendClipToPool(VideoClip* clip);

public slots:
    void addClips(QStringList* list);

    void addToPool(uint num);

    void displayThumbnail();

    void clipClickRecieved(VideoClip* clip);


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
    void sendClickedClip(VideoClip* clip);
};

#endif // POOL_H

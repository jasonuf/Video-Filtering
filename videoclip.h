#ifndef VIDEOCLIP_H
#define VIDEOCLIP_H
#include <QObject>
#include <QMediaPlayer>
#include <QVideoSink>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QVideoFrame>
#include <QAudioOutput>

#include <QTimer>

class VideoClip : public QObject{
    Q_OBJECT

public:
    explicit VideoClip(QObject *parent = nullptr);
    ~VideoClip();



    QUrl getClipSource() const {return clipSource;}
    QString getFileName() const {return fileName;};

    QVideoSink* getClipSink() const {return clipSink;}
    QMediaPlayer* getClipPlayer() const {return clipPlayer;}
    // qint64 getClipDuration() const {return clipPlayer->duration();};
    QImage* getThumbnail() const {return thumbnail;};
    qint64 getPositionStart() const {return positionStart;};
    qint64 getPositionEnd() const {return positionEnd;};


    // void setClipWidget(QVideoWidget* v);
    // void setClipSink(QVideoWidget* v);
    // void setClipSink(QVideoSink* sink);
    void setSource(QUrl source);
    void setFileName(QString str);
    void setPositionStart(qint64 start);
    void setPositionEnd(qint64 end);

signals:

    void thumbNailLoaded();

    // void playPlayer();
    // void pausePlayer();

private:
    qint64 positionStart;
    qint64 positionEnd;

    QVideoSink* clipSink;
    QMediaPlayer* clipPlayer;
    // QAudioOutput* clipAudio;
    QUrl clipSource;
    QString fileName;

    QImage* thumbnail;


private slots:
    void onMediaStop(QMediaPlayer::PlaybackState newState);

public slots:

    void waitForThumbnail(const QVideoFrame &frame);

    // void frameDoSomething(const QVideoFrame &frame);
    // void frameDoSomething2();
};


#endif // VIDEOCLIP_H

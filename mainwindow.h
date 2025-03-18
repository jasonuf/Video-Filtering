#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QFile>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QAudioOutput>

#include "videoclip.h"
#include "timeline.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:

    void actionTest();


private slots:



    void on_actionOpen_File_triggered();

    void pausePlay();

private:
    bool existsVideo;
    bool isPlaying;


    Ui::MainWindow *ui;



    void createMenus();
    void createActions();

    QStringList* openVideoFilesList;
    QUrl testUrl;
    QMediaPlayer* videoPlayer;
    QVideoWidget* vidWidget;
    QAudioOutput* audioOutput;

    QBoxLayout* masterLayout;
    QBoxLayout* col1Layout;
    QBoxLayout* col2Layout;

    QBoxLayout* controlBarLayout;
    QBoxLayout* vidLayout;
    QPushButton* videoPlaceholder;
    QWidget* myWidget2;
    QWidget* myWidget3;
    QWidget* myWidget4;


    VideoClip* testClip1;
    VideoClip* testClip2;
    VideoClip* testClip3;
    Timeline* timeline;

    QVideoWidget* testVideoWidget;


};
#endif // MAINWINDOW_H

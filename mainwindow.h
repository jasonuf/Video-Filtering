#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "videoplayer.h"

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QFile>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>


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

private:
    Ui::MainWindow *ui;
    VideoPlayer* mainVideo;

    void createMenus();
    void createActions();

    QStringList* openVideoFilesList;
    QUrl testUrl;
    QMediaPlayer* videoPlayer;
    QVideoWidget* vidWidget;






};
#endif // MAINWINDOW_H

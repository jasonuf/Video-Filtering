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
#include <QScrollArea>

#include "videoclip.h"
#include "player.h"
#include "pool.h"


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

signals:

    void sendFileStringList(QStringList* list);

public slots:

    void actionTest();


private slots:



    void on_actionOpen_File_triggered();


private:


    Ui::MainWindow *ui;



    void createMenus();
    void createActions();

    QStringList* openVideoFilesList;



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

    Player* testPlayer;

    Pool* poolw;



    QScrollArea* testScrollArea;
    QGridLayout* testGridLayout;
    QVBoxLayout* testMasterLayout;
    QHBoxLayout* testRow1Layout;
    QHBoxLayout* testRow2Layout;
    QHBoxLayout* testRow3Layout;

    QWidget* scrollWid;

    QWidget* testWid1;
    QWidget* testWid2;
    QWidget* testWid3;
    QWidget* testWid4;
    QWidget* testWid5;
    QWidget* testWid6;
    QWidget* testWid7;
    QWidget* testWid8;
    QWidget* testWid9;


    QVideoWidget* testVideoWidget;


};
#endif // MAINWINDOW_H

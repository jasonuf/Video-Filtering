#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videoplayer.h"


#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QVBoxLayout>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //initialize opened video location to be empty;
    openVideoFilesList = nullptr;



    ui->setupUi(this);
    setFixedSize(960,540);



    qInfo() << "Main Window Created";


}

MainWindow::~MainWindow()
{


    delete ui;
}

void MainWindow::actionTest()
{
    qInfo() << "Action was completed";
}

void MainWindow::createMenus()
{


}



void MainWindow::on_actionOpen_File_triggered()
{
    //on open file action pressed, load the selected file into the openVideoFilesList
    openVideoFilesList = new QStringList(QFileDialog::getOpenFileNames(this,
        tr("Open Video"), "/", tr("Video Files (*.mp4)")));

    qInfo() << "The property openVideoFilesList is set to: " << *openVideoFilesList;


    if (!openVideoFilesList->isEmpty()){
        testUrl = QUrl::fromLocalFile(openVideoFilesList->at(0));
    }

    qInfo() << "The property testURL is set to: " << testUrl;

    videoPlayer = new QMediaPlayer(this);
    videoPlayer->setSource(testUrl);

    vidWidget = new QVideoWidget();
    videoPlayer->setVideoOutput(vidWidget);

    vidWidget->show();
    videoPlayer->play();




}


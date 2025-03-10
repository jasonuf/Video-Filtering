#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videoplayer.h"


#include <QMenuBar>
#include <QMenu>
#include <QDebug>

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //initialize opened video location to be empty;
    openVideoFilesList = nullptr;
    videoPlayer = nullptr;
    vidWidget = nullptr;



    ui->setupUi(this);
    //setFixedSize(960,540);
    //showFullScreen();
    centralWidget()->resize(100,100);


    //Palletes
    QPalette blackPal = QPalette();
    blackPal.setColor(QPalette::Window, Qt::black);
    QPalette bluePal = QPalette();
    bluePal.setColor(QPalette::Window, Qt::blue);
    QPalette yellowPal = QPalette();
    yellowPal.setColor(QPalette::Window, Qt::yellow);
    QPalette greenPal = QPalette();
    greenPal.setColor(QPalette::Window, Qt::green);

    // QWidget* masterWidget = new QWidget();

    // setCentralWidget(masterWidget);


    masterLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight, centralWidget());
    col1Layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    col2Layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);




    myWidget1 = new QWidget();
    myWidget1->setAutoFillBackground(true);
    myWidget1->setPalette(blackPal);

    myWidget2 = new QWidget();
    myWidget2->setAutoFillBackground(true);
    myWidget2->setPalette(bluePal);

    myWidget3 = new QWidget();
    myWidget3->setAutoFillBackground(true);
    myWidget3->setPalette(yellowPal);

    myWidget4 = new QWidget();
    myWidget4->setAutoFillBackground(true);
    myWidget4->setPalette(greenPal);

    col1Layout->addWidget(myWidget1);
    col1Layout->addWidget(myWidget2);

    col2Layout->addWidget(myWidget3);
    col2Layout->addWidget(myWidget4);

    masterLayout->addLayout(col1Layout, 2);
    masterLayout->addLayout(col2Layout, 1);


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

    col1Layout->removeItem(col1Layout->itemAt(0));

    //on open file action pressed, load the selected file into the openVideoFilesList
    openVideoFilesList = new QStringList(QFileDialog::getOpenFileNames(this,
        tr("Open Video"), "/", tr("Video Files (*.mp4)")));

    qInfo() << "The property openVideoFilesList is set to: " << *openVideoFilesList;


    if (!openVideoFilesList->isEmpty()){
        testUrl = QUrl::fromLocalFile(openVideoFilesList->at(0));
    }

    qInfo() << "The property testURL is set to: " << testUrl;

    videoPlayer = new QMediaPlayer();
    videoPlayer->setSource(testUrl);

    vidWidget = new QVideoWidget(centralWidget());
    vidWidget->resize(300,300);
    videoPlayer->setVideoOutput(vidWidget);

    vidWidget->show();
    videoPlayer->play();


    col1Layout->insertWidget(0, vidWidget);

}


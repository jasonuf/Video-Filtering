#include "mainwindow.h"
#include "./ui_mainwindow.h"



#include <QMenuBar>
#include <QMenu>
#include <QDebug>

#include <QFileDialog>
#include <QStackedWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //initialize opened video location to be empty;
    openVideoFilesList = nullptr;
    vidWidget = nullptr;
    existsVideo = false;
    isPlaying = false;

    ui->setupUi(this);

    //setFixedSize(960,540);
    //showFullScreen();
    //centralWidget()->resize(100,100);

    videoPlayer = new QMediaPlayer(this);
    // connect(videoPlayer, &QMediaPlayer::errorOccurred, this, [](QMediaPlayer::Error error, const QString &errorString) -> void {
    //     qInfo() << "Your error was: " << errorString;
    // });

    //Palletes
    QPalette blackPal = QPalette();
    blackPal.setColor(QPalette::Window, Qt::black);
    QPalette bluePal = QPalette();
    bluePal.setColor(QPalette::Window, Qt::blue);
    QPalette yellowPal = QPalette();
    yellowPal.setColor(QPalette::Window, Qt::yellow);
    QPalette greenPal = QPalette();
    greenPal.setColor(QPalette::Window, Qt::green);
    QPalette customPal = QPalette();
    customPal.setColor(QPalette::Window, QColor(45, 51, 50));
    // QPalette wid1Pal = QPalette();
    // wid1Pal.setColor(QPalette::Button, QColor(138, 143, 150));

    this->setPalette(customPal);
    this->menuBar()->setPalette(customPal);
    // QWidget* masterWidget = new QWidget();

    // setCentralWidget(masterWidget);


    masterLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight, centralWidget());
    col1Layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    col2Layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);

    vidLayout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    controlBarLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);


    videoPlaceholder = new QPushButton("Upload a Video");
    QFont f = videoPlaceholder->font();
    f.setUnderline(true);
    f.setItalic(true);
    f.setFamily("Sans Regular");
    videoPlaceholder->setFont(f);
    //videoPlaceHolder->setAutoFillBackground(true);
    videoPlaceholder->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    //videoPlaceholder->setPalette(customPal);
    //videoPlaceholder->setPalette(greenPal);
    //videoPlaceholder->setAlignment(Qt::AlignCenter);
    //videoPlaceholder->setPalette(wid1Pal);


    testClip1 = new VideoClip(this);
    testClip2 = new VideoClip(this);
    testClip3 = new VideoClip(this);
    timeline = new Timeline(this);
    //testVideoWidget = new QVideoWidget(this);

    timeline->addClip(testClip1);
    timeline->addClip(testClip2);
    timeline->addClip(testClip3);

    //timeline->setVideoWidget(testVideoWidget);

    vidLayout->addWidget(timeline);

    timeline->playFromBeginning();

    connect(videoPlaceholder,&QAbstractButton::clicked,this, &MainWindow::on_actionOpen_File_triggered);

    /////////---------------------------
    // QStackedWidget* stack = new QStackedWidget(this);
    // QWidget* myWidget6 = new QWidget();
    // myWidget6->setAutoFillBackground(true);
    // myWidget6->setPalette(yellowPal);

    // QWidget* myWidget7 = new QWidget();
    // myWidget7->setAutoFillBackground(true);
    // myWidget7->setPalette(greenPal);

    // stack->addWidget(myWidget6);
    // stack->addWidget(myWidget7);

    // stack->setCurrentIndex(1);

    // vidLayout->addWidget(stack);
    //////////////////------------------------

    myWidget2 = new QWidget();
    myWidget2->setAutoFillBackground(true);
    myWidget2->setPalette(bluePal);


    myWidget3 = new QWidget();
    myWidget3->setAutoFillBackground(true);
    myWidget3->setPalette(yellowPal);

    myWidget4 = new QWidget();
    myWidget4->setAutoFillBackground(true);
    myWidget4->setPalette(greenPal);

    ui->pushButton->setStyleSheet("QPushButton:enabled { background-color: rgb(97, 107, 107); }\n");
    controlBarLayout->addWidget(ui->pushButton, 0, Qt::AlignLeft);
    connect(ui->pushButton, &QAbstractButton::clicked,this, &MainWindow::pausePlay);


    col1Layout->addLayout(vidLayout, 75);
    col1Layout->addLayout(controlBarLayout, 5);
    col1Layout->addWidget(myWidget2, 20);

    col2Layout->addWidget(myWidget3);
    col2Layout->addWidget(myWidget4);

    masterLayout->addLayout(col1Layout, 2);
    masterLayout->addLayout(col2Layout, 1);


    qInfo() << "Main Window Created";


}

MainWindow::~MainWindow()
{
    delete ui;
    delete openVideoFilesList;
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
    delete openVideoFilesList;
    openVideoFilesList = new QStringList(QFileDialog::getOpenFileNames(this,
        tr("Open Video"), "", tr("Video Files (*.mp4 *.mov)")));

    if (!openVideoFilesList->isEmpty()){
        testUrl = QUrl::fromLocalFile(openVideoFilesList->at(0));
        if (!existsVideo){
            existsVideo = true;
            vidWidget = new QVideoWidget(this);
            audioOutput = new QAudioOutput;
            videoPlayer->setAudioOutput(audioOutput);
            videoPlayer->setVideoOutput(vidWidget);
            vidLayout->removeWidget(videoPlaceholder);
            vidLayout->addWidget(vidWidget);
            videoPlaceholder->hide();

        }

        videoPlayer->setSource(testUrl);

    }


    qInfo() << "The property testURL is set to: " << testUrl;


}


void MainWindow::pausePlay(){
    if (!existsVideo){
        return;
    }

    if (!isPlaying){
        isPlaying = true;
        videoPlayer->play();
    }
    else{
        isPlaying = false;
        videoPlayer->pause();
    }

}

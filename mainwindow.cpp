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

    ui->setupUi(this); //setup ui (WOW)

    setMinimumSize(960,540);


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

    //Palette of window, still wondering how to change the menu palette
    //this->setPalette(customPal);
    this->menuBar()->setPalette(customPal);


    //masterLayout is the central layout with 2 columns.
    masterLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight, centralWidget());
    col1Layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    col2Layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);

    //vidLayout currently holds the player 3/20/2025
    vidLayout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    controlBarLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

    //This widget will trigger the file upload, currently not in use
    videoPlaceholder = new QPushButton("Upload a Video");
    QFont f = videoPlaceholder->font();
    f.setUnderline(true);
    f.setItalic(true);
    f.setFamily("Sans Regular");
    videoPlaceholder->setFont(f);
    videoPlaceholder->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    connect(videoPlaceholder,&QAbstractButton::clicked,this, &MainWindow::on_actionOpen_File_triggered);


    testPlayer = new Player();
    // testClip1 = new VideoClip(this);
    // testClip2 = new VideoClip(this);
    // testClip3 = new VideoClip(this);

    // testPlayer->addClip(testClip1);
    // testPlayer->addClip(testClip2);
    // testPlayer->addClip(testClip3);

    vidLayout->addWidget(testPlayer);

    // testPlayer->playFromBeginning();




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
    //connect(ui->pushButton, &QAbstractButton::clicked,this, &MainWindow::pausePlay);


    // Create and set up QScrollArea
    testScrollArea = new QScrollArea(this);
    testScrollArea->setWidgetResizable(true); // Change to false to preserve widget sizes
    testScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    testScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    testScrollArea->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    poolw = new Pool();
    poolw->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(this, &MainWindow::sendFileStringList, poolw, &Pool::addClips);

    testScrollArea->setWidget(poolw);


    timeline = new Timeline(this);
    connect(timeline, &Timeline::droppedClip, this, &MainWindow::manageDroppedClips);



    col1Layout->addLayout(vidLayout, 75);
    col1Layout->addLayout(controlBarLayout, 5);
    col1Layout->addWidget(timeline, 20);

    // Add widgets to col2Layout with stretch factors
    col2Layout->addWidget(testScrollArea, 50);
    col2Layout->addWidget(ui->widget, 50);

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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qInfo() << "New size " << width() << " Old size: " << event->oldSize();
    QWidget::resizeEvent(event);
}



void MainWindow::on_actionOpen_File_triggered()
{

    //on open file action pressed, load the selected file into the openVideoFilesList
    delete openVideoFilesList;
    openVideoFilesList = new QStringList(QFileDialog::getOpenFileNames(this,
        tr("Open Video"), "", tr("Video Files (*.mp4 *.mov)")));

    //emit this signal which is sent to the pool instance
    emit sendFileStringList(openVideoFilesList);

    //testUrl = QUrl::fromLocalFile(openVideoFilesList->at(0));


}

void MainWindow::manageDroppedClips(QString path, int width)
{
    qInfo() <<"Dropped path: " << path << " x: " << width;

    for (VideoClip* clip : poolw->getClips())
    {
        if (clip->getClipSource().path() == path)
        {
            timeline->addClip(clip);
            qInfo() << "timeline clip added is " << clip;
            break;
        }
    }
}


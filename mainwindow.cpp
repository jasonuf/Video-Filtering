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

    ui->setupUi(this);

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

    this->setPalette(customPal);
    this->menuBar()->setPalette(customPal);



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
    videoPlaceholder->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));


    testPlayer = new Player();
    testClip1 = new VideoClip(this);
    testClip2 = new VideoClip(this);
    testClip3 = new VideoClip(this);

    testPlayer->addClip(testClip1);
    testPlayer->addClip(testClip2);
    testPlayer->addClip(testClip3);

    vidLayout->addWidget(testPlayer);

    testPlayer->playFromBeginning();


    connect(videoPlaceholder,&QAbstractButton::clicked,this, &MainWindow::on_actionOpen_File_triggered);


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

    // testScrollArea = new QScrollArea();
    //testScrollArea->setPalette(bluePal);
    // testScrollArea->setWidget(myWidget3);
    // testScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    // testCol1Layout = new QVBoxLayout();
    // testCol2Layout = new QVBoxLayout();

    // testCol1Layout->addWidget(testWid1);
    // testCol1Layout->addWidget(testWid2);
    // testCol1Layout->addWidget(testWid3);

    // testCol2Layout->addWidget(testWid4);
    // testCol2Layout->addWidget(testWid5);
    // testCol2Layout->addWidget(testWid6);

    // testGridLayout->addLayout(testCol1Layout, 0, 0);
    // testGridLayout->addLayout(testCol2Layout, 0, 1);

    // testGridLayout->setSizeConstraint(QLayout::SetFixedSize);



    // Create and set up QScrollArea
    testScrollArea = new QScrollArea(this);
    testScrollArea->setWidgetResizable(true); // Change to false to preserve widget sizes
    testScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    testScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    testScrollArea->setAlignment(Qt::AlignHCenter);

    // Create scroll content widget
    // scrollWid = new QWidget();

    // // Create and set up child widgets
    // testWid1 = new QWidget();
    // testWid1->setAutoFillBackground(true);
    // testWid1->setPalette(blackPal);
    // testWid1->setFixedSize(100,100);
    // testWid2 = new QWidget();
    // testWid2->setAutoFillBackground(true);
    // testWid2->setPalette(bluePal);
    // testWid2->setFixedSize(100,100);
    // testWid3 = new QWidget();
    // testWid3->setAutoFillBackground(true);
    // testWid3->setPalette(yellowPal);
    // testWid3->setFixedSize(100,100);
    // testWid4 = new QWidget();
    // testWid4->setAutoFillBackground(true);
    // testWid4->setPalette(greenPal);
    // testWid4->setFixedSize(100,100);
    // testWid5 = new QWidget();
    // testWid5->setAutoFillBackground(true);
    // testWid5->setPalette(blackPal);
    // testWid5->setFixedSize(100,100);
    // testWid6 = new QWidget();
    // testWid6->setAutoFillBackground(true);
    // testWid6->setPalette(bluePal);
    // testWid6->setFixedSize(100,100);
    // testWid7 = new QWidget();
    // testWid7->setAutoFillBackground(true);
    // testWid7->setPalette(blackPal);
    // testWid7->setFixedSize(100,100);
    // testWid8 = new QWidget();
    // testWid8->setAutoFillBackground(true);
    // testWid8->setPalette(bluePal);
    // testWid8->setFixedSize(100,100);
    // testWid9 = new QWidget();
    // testWid9->setAutoFillBackground(true);
    // testWid9->setPalette(yellowPal);
    // testWid9->setFixedSize(100,100);

    // testMasterLayout = new QVBoxLayout();
    // testRow1Layout = new QHBoxLayout();
    // testRow2Layout = new QHBoxLayout();
    // testRow3Layout = new QHBoxLayout();

    // testRow1Layout->addWidget(testWid1);
    // testRow1Layout->addWidget(testWid2);
    // testRow1Layout->addWidget(testWid3);
    // testRow1Layout->setSpacing(25);

    // testRow2Layout->addWidget(testWid4);
    // testRow2Layout->addWidget(testWid5);
    // testRow2Layout->addWidget(testWid6);

    // testRow3Layout->addWidget(testWid7);
    // testRow3Layout->addWidget(testWid8);
    // testRow3Layout->addWidget(testWid9);

    // testMasterLayout->addLayout(testRow1Layout);
    // testMasterLayout->addLayout(testRow2Layout);
    // testMasterLayout->addLayout(testRow3Layout);

    //--------------------------------------------------
    // Create grid layout and add widgets
    //testGridLayout = new QGridLayout(scrollWid);
    //testGridLayout->setSpacing(25);
    // testGridLayout->setContentsMargins(5,5,5,5);
    // testGridLayout->addWidget(testWid1, 0,0);
    // testGridLayout->addWidget(testWid2, 1,0);
    // testGridLayout->addWidget(testWid3, 2,0);
    // testGridLayout->addWidget(testWid4, 0,1);
    // testGridLayout->addWidget(testWid5, 1,1);
    // testGridLayout->addWidget(testWid6, 2,1);


    // Set the layout for the scroll widget


    // Calculate the size needed for the grid
    //scrollWid->adjustSize();

    // Set the scroll widget as the widget for the scroll area




    ////------------------------------------------------ Pool testing
    ///
    ///
    poolw = new Pool();

    connect(this, &MainWindow::sendFileStringList, poolw, &Pool::addClips);


    testScrollArea->setWidget(poolw);


    col1Layout->addLayout(vidLayout, 75);
    col1Layout->addLayout(controlBarLayout, 5);
    col1Layout->addWidget(myWidget2, 20);

    // Add widgets to col2Layout with stretch factors
    col2Layout->addWidget(testScrollArea, 50);
    col2Layout->addWidget(myWidget4, 50);

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

    emit sendFileStringList(openVideoFilesList);

    //testUrl = QUrl::fromLocalFile(openVideoFilesList->at(0));


}


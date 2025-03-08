#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videoplayer.h"


#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,videoArea(new VideoPlayer(this))
    , ui(new Ui::MainWindow)
{

    //setCentralWidget(videoArea);

    //createMenus();

    // QWidget *widget = new QWidget;
    // setCentralWidget(widget);

    // QWidget *topFiller = new QWidget;
    // topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
    //                           "invoke a context menu</i>"));
    // infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    // infoLabel->setAlignment(Qt::AlignCenter);
    // infoLabel->setStyleSheet("QLabel { background-color : red; color : blue; }");


    // QWidget *bottomFiller = new QWidget;
    // bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // QVBoxLayout *layout = new QVBoxLayout;
    // layout->setContentsMargins(5, 5, 5, 5);
    // layout->addWidget(topFiller);
    // layout->addWidget(infoLabel);
    // layout->addWidget(bottomFiller);
    // widget->setLayout(layout);


    // createActions();
    // createMenus();

    // QString message = tr("A context menu is available by right-clicking");
    // statusBar()->showMessage(message);

    // setWindowTitle(tr("Menus"));
    // setMinimumSize(160, 160);
    // resize(480, 320);

    fileMenu = new QMenu("View");
    fileMenu->addAction("Sky");
    fileMenu->addAction("Cloud");
    fileMenu->addAction("Tree");



    qInfo() << "Main Window Created";

    ui->setupUi(this);
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

    QMenu* saveAsMenu = new QMenu(tr("&Save As"), this);
    // for (QAction *action : std::as_const(saveAsActs))
    //     saveAsMenu->addAction(action);

    QMenu* fileMenu = new QMenu(tr("&File"), this);
    // fileMenu->addAction(openAct);
    // fileMenu->addMenu(saveAsMenu);
    // fileMenu->addAction(printAct);
    // fileMenu->addSeparator();
    // fileMenu->addAction(exitAct);

    QMenu* optionMenu = new QMenu(tr("&Options"), this);
    // optionMenu->addAction(penColorAct);
    // optionMenu->addAction(penWidthAct);
    // optionMenu->addSeparator();
    // optionMenu->addAction(clearScreenAct);

    QMenu* helpMenu = new QMenu(tr("&Help"), this);
    // helpMenu->addAction(aboutAct);
    // helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}


void MainWindow::createActions()
{
    newAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                         tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::actionTest);
}


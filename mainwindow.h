#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "videoplayer.h"

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QFile>

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



private:
    Ui::MainWindow *ui;
    VideoPlayer* mainVideo;

    void createMenus();
    void createActions();

    QString* videoOpen;








};
#endif // MAINWINDOW_H

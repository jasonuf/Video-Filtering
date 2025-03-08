#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoplayer.h"
#include <QLabel>

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
    // void newFile();
    // void open();
    // void save();
    // void print();
    // void undo();
    // void redo();
    // void cut();
    // void copy();
    // void paste();
    // void bold();
    // void italic();
    // void leftAlign();
    // void rightAlign();
    // void justify();
    // void center();
    // void setLineSpacing();
    // void setParagraphSpacing();
    // void about();
    // void aboutQt();

private:
    Ui::MainWindow *ui;
    VideoPlayer* videoArea;

    void createMenus();
    void createActions();




    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;

};
#endif // MAINWINDOW_H

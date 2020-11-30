#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QSplitter>
#include "mygraphicview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    void setDimensions();
    void deleteItem();
    void newItem();
    void showReport();
    void saveReport();
    void exit();

private:
    void closeEvent(QCloseEvent *event);
    void createActions();
    void createMenus();
    void fillTree();
    bool askForSave();
    bool saved;
    CarShowroom sr;
    QMenu *fileMenu;
    QMenu *itemMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *setDimensionsAct;
    QAction *deleteAct;
    QAction *newItemAct;
    QAction *showReportAct;
    QAction *saveReportAct;
    QAction *exitAct;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    QTreeWidgetItem *carTree;
    QTreeWidgetItem *podiumTree;
    MyGraphicView *myPicture;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

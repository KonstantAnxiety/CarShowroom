#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QSplitter>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include "cardialog.h"
#include "dimensionsdialog.h"
#include "carshowroom.h"
#include "auxiliary.h"
#include "cmath"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    splitter = new QSplitter;

    saved = true;
    sr.setLength(100);
    sr.setWidth(100);
    myPicture = new MyGraphicView(parent, sr.getLength(), sr.getWidth());
    treeWidget = new QTreeWidget(parent);
    ui->horizontalLayout->addWidget(splitter);

    splitter->addWidget(myPicture);
    splitter->addWidget(treeWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);

    carTree = new QTreeWidgetItem;
    podiumTree = new QTreeWidgetItem;
    carTree->setExpanded(true);
    podiumTree->setExpanded(true);
    treeWidget->addTopLevelItem(carTree);
    treeWidget->addTopLevelItem(podiumTree);
    carTree->setText(0, "Cars");
    podiumTree->setText(0, "Podiums");

    QStringList headerLables;
    headerLables.push_back(QString("Objects"));
    headerLables.push_back(QString("ID"));
    headerLables.push_back(QString("Brand"));
    headerLables.push_back(QString("X"));
    headerLables.push_back(QString("Y"));
    headerLables.push_back(QString("Rotation"));
    headerLables.push_back(QString("Length"));
    headerLables.push_back(QString("Width"));
    headerLables.push_back(QString("Radius"));
    treeWidget->setColumnCount(9);
    treeWidget->setHeaderLabels(headerLables);

    myPicture->addItems(sr);
    fillTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    if (!askForSave())
        return;
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open file"),
                                                    "/",
                                                    tr("Text Files (*.txt)"));

    sr.readFromFile(filename.toStdString());
    carTree->setExpanded(true);
    podiumTree->setExpanded(true);
    fillTree();
}

void MainWindow::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save as..."),
                                                    "/",
                                                    tr("Text Files (*.txt)"));
    if (!filename.isEmpty()) {
        sr.writeToFile(filename.toStdString());
        saved = true;
    }
}

void MainWindow::setDimensions()
{
    DimensionsDialog *d = new DimensionsDialog;
    bool succ = d->exec();
    if (succ) {
        sr.setLength(d->getLength());
        sr.setWidth(d->getWidth());
        fillTree();
        saved = false;
    }
    delete d;
}

void MainWindow::deleteItem()
{
    if (sr.objects.empty()) {
        QMessageBox::information(this, "Empty", "The showroom is empty.");
        return;
    }
    if (treeWidget->selectedItems().size() &&
            treeWidget->selectedItems()[0] != treeWidget->topLevelItem(0) &&
            treeWidget->selectedItems()[0] != treeWidget->topLevelItem(1)) {
        size_t i = treeWidget->selectedItems()[0]->text(1).toInt();
        sr.objects.del(i);
        fillTree();
        saved = false;
    }
}

void MainWindow::newItem()
{
    CarDialog *d = new CarDialog(this, sr.objects.getSize());
    bool succ = d->exec();
    if (succ) {
        int pos = d->getPos();
        if (pos == 0)
            sr.objects.push_back(std::shared_ptr<Point>(d->getItem()));
        else
            sr.objects.insert(pos-1, std::shared_ptr<Point>(d->getItem()));
        fillTree();
        saved = false;
    }
    delete d;
}

void MainWindow::showReport()
{
    QString report;
    report.append(sr.getCarIntersections(1));
    report.append(sr.getPodiumIntersections(1));
    report.append(sr.getWallCarIntersections(1));
    report.append(sr.getWallPodiumIntersections(1));
    report.append(sr.getCarPodiumAdequacy(1));
    QMessageBox::information(this, "Report", report);
}

void MainWindow::saveReport()
{
    std::ofstream fout;
    fout.open("report.txt");
    QString report;
    report.append(sr.getCarIntersections(1));
    report.append(sr.getPodiumIntersections(1));
    report.append(sr.getWallCarIntersections(1));
    report.append(sr.getWallPodiumIntersections(1));
    report.append(sr.getCarPodiumAdequacy(1));
    fout << report.toStdString();
    fout.close();
    QMessageBox::information(this, "Saved", "Report saved to \"report.txt\".");
}

void MainWindow::exit()
{
    if (!askForSave())
        return;
    QApplication::exit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!askForSave())
        event->ignore();
    else
        QMainWindow::closeEvent(event);
}

bool MainWindow::askForSave() // returns false if need to abort the operation it was called before
{
    if (!saved) {
        QMessageBox msgBox;
        msgBox.setText("The document has unsaved changes");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                                  QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              saveFile();
              return true;
              break;
          case QMessageBox::Cancel:
              return false;
              break;
          default:
              return true;
              break;
        }
    }
    return true;
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Create a new file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save as..."), this);
    saveAct->setShortcuts(QKeySequence::SaveAs);
    saveAct->setStatusTip(tr("Save to file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Exit app"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::exit);

    setDimensionsAct = new QAction(tr("&Dimensions"), this);
    setDimensionsAct->setStatusTip(tr("Set new dimensions for the car showroom"));
    connect(setDimensionsAct, &QAction::triggered, this, &MainWindow::setDimensions);

    deleteAct = new QAction(tr("&Delete"), this);
    deleteAct->setShortcuts(QKeySequence::Delete);
    deleteAct->setStatusTip(tr("Remove selected item"));
    connect(deleteAct, &QAction::triggered, this, &MainWindow::deleteItem);

    newItemAct = new QAction(tr("&Add item"), this);
    newItemAct->setShortcuts(QKeySequence::New);
    newItemAct->setStatusTip(tr("Add new item"));
    connect(newItemAct, &QAction::triggered, this, &MainWindow::newItem);

    showReportAct = new QAction(tr("&Show report"), this);
    showReportAct->setStatusTip(tr("Show report ina message"));
    connect(showReportAct, &QAction::triggered, this, &MainWindow::showReport);

    saveReportAct = new QAction(tr("&Save report"), this);
    saveReportAct->setStatusTip(tr("Save report to text a file"));
    connect(saveReportAct, &QAction::triggered, this, &MainWindow::saveReport);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(setDimensionsAct);
    itemMenu->addAction(deleteAct);
    itemMenu->addAction(newItemAct);
    itemMenu->addAction(showReportAct);
    itemMenu->addAction(saveReportAct);
}

void MainWindow::fillTree()
{
    foreach(auto i, carTree->takeChildren()) delete i;
    foreach(auto i, podiumTree->takeChildren()) delete i;
    for (size_t i = 0; i < sr.objects.getSize(); ++i) {
        QTreeWidgetItem *car = new QTreeWidgetItem();
        Car *curCar = dynamic_cast<Car*>(sr.objects[i].get());
        if (curCar) {
            car->setText(1, QString::number(i));
            car->setText(2, QString::fromUtf8(curCar->getBrand().c_str()));
            car->setText(3, QString::number(curCar->getX()));
            car->setText(4, QString::number(curCar->getY()));
            car->setText(5, QString::number(curCar->getRotation()));
            car->setText(6, QString::number(curCar->getLength()));
            car->setText(7, QString::number(curCar->getWidth()));
            car->setText(8, "-");
            carTree->addChild(car);
            continue;
        }
        Podium *curPodium = dynamic_cast<Podium*>(sr.objects[i].get());
        if (curPodium) {
            car->setText(1, QString::number(i));
            car->setText(2, QString::fromUtf8(curPodium->getBrand().c_str()));
            car->setText(3, QString::number(curPodium->getX()));
            car->setText(4, QString::number(curPodium->getY()));
            car->setText(5, "-");
            car->setText(6, "-");
            car->setText(7, "-");
            car->setText(8, QString::number(curPodium->getRadius()));
            podiumTree->addChild(car);
        }
    }
    treeWidget->header()->setStretchLastSection(false);
    treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    myPicture->addItems(sr);
}

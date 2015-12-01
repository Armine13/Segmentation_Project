#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab.h"
#include "segmentationmarkerwidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QTabWidget>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIcon::setThemeName("TangoMFK");//custom theme for icons

    //Create widget for displaying markers
    SegmentationMarkers = new SegmentationMarkerWidget(ui->SegmentationToolBar);
    connect(SegmentationMarkers, SIGNAL(colorSelected(QColor)), this, SLOT(on_penColorChanged(QColor)));

    //Adding markers to a toolbar
    ui->SegmentationToolBar->addWidget(SegmentationMarkers);

    //Create initial open tab
    openTabsN = 1;
    tabsVector.append(new Tab(ui->tabWidget));
    ui->tabWidget->addTab(tabsVector[0], QString("New segmentation"));
    //    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(on_tabCloseRequested(int index)));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    //setting up actions
    ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
    ui->actionSaveAs->setIcon(QIcon::fromTheme("document-save-as"));
    ui->actionClose->setIcon(QIcon::fromTheme("document-close"));
    ui->actionExit->setIcon(QIcon::fromTheme("exit"));
    ui->actionLoadImage->setIcon(QIcon::fromTheme("image-x-generic"));
    ui->actionUndo->setIcon(QIcon::fromTheme("edit-undo"));
    ui->actionRedo->setIcon(QIcon::fromTheme("edit-redo"));
    ui->actionStart_Segmentation->setIcon(QIcon::fromTheme("start"));
    ui->actionShowMainToolbar->setChecked(true);
    ui->actionShowSegmentationToolbar->setChecked(true);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionNew_triggered()
{
    openTabsN++;
    tabsVector.append(new Tab(ui->tabWidget));
    ui->tabWidget->addTab(tabsVector[openTabsN - 1], QString("New segmentation"));

    //enable action loadImage
    ui->actionLoadImage->setEnabled(true);
}

void MainWindow::on_actionLoadImage_triggered()
{//This function opens a dialog to choose an image

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "../seededSegmentation", tr("Image Files (*.png *.jpg *.bmp)"));

    //If name is not empty open the chosen image in a new tab
    if (!fileName.isEmpty())
    {
        //open image in tab widget
        tabsVector[ui->tabWidget->currentIndex()]->openImage(fileName);

        //enable action start_Segmentation
        ui->actionStart_Segmentation->setEnabled(true);
    }
}

void MainWindow::on_actionShowMainToolbar_triggered()
{// Show/hide the main toolbar when actionShowMainToolbar toggled
    if (ui->actionShowMainToolbar->isChecked())
        ui->mainToolBar->show();
    else ui->mainToolBar->hide();

}

void MainWindow::on_actionShowSegmentationToolbar_triggered()
{// Show/hide the segmentation toolbar when actionShowSegmentationToolbar toggled
    if (ui->actionShowSegmentationToolbar->isChecked())
        ui->SegmentationToolBar->show();
    else ui->SegmentationToolBar->hide();
}

void MainWindow::on_actionSet_Number_of_Classes_triggered()
{
    bool ok;
    int n = QInputDialog::getInt(this, tr("Set Number of Classes"),
                                 tr("Set Number of Classes for Segmentation"), 2, 2, 5, 1, &ok);
    if (ok)
        SegmentationMarkers->setMarkerNumber(n);
}
void MainWindow::on_penColorChanged(QColor clr)
{
    // pass the selected pen color to the currently open tab widget
    tabsVector[ui->tabWidget->currentIndex()]->setPenColor(clr);
}

void MainWindow::tabChanged(int n)
{
    //if no tab is open or image not loaded in tab..
    if (!tabsVector.isEmpty() || !tabsVector[n]->isImageLoaded())
        //disable "start segmentation"
        ui->actionStart_Segmentation->setEnabled(false);
    else
        ui->actionStart_Segmentation->setEnabled(true);
}

void MainWindow::on_actionStart_Segmentation_triggered()
{
    // call startSegmentation function of the currently open tab widget
    tabsVector[ui->tabWidget->currentIndex()]->startSegmentation();
}

void MainWindow::on_actionClose_triggered()
{
    //triggered from File menu
    // call on_tabCloseRequested to close the widget
    on_tabWidget_tabCloseRequested(ui->tabWidget->currentIndex());
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    // remove the tab widget
    ui->tabWidget->removeTab(index);

    //delete object
    delete tabsVector[index];
    //remove tab from tabsVector
    tabsVector.remove(index);

    openTabsN--;

    //if no open tabs left, disable action "open image"
    if (openTabsN == 0)
    {
        qDebug()<<"no open tabs";
//        ui->actionLoadImage->setDisabled(true);
    }
}

void MainWindow::on_actionExit_triggered()
{//close application

    QCoreApplication::quit();
}

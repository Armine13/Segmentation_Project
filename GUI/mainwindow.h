#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "segmentationmarkerwidget.h"
#include "tab.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void tabChanged(int);
    void on_actionLoadImage_triggered();
    void on_actionShowMainToolbar_triggered();
    void on_actionShowSegmentationToolbar_triggered();
    void on_actionClose_triggered();
    void on_penColorChanged(QColor);
    void on_actionStart_Segmentation_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionExit_triggered();

    void on_actionSaveAs_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    Ui::MainWindow *tabWidget;
    int openTabsN;
    SegmentationMarkerWidget* SegmentationMarkers;
    QVector<Tab*> tabsVector;
};

#endif // MAINWINDOW_H

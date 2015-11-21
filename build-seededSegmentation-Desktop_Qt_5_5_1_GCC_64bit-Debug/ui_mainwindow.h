/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionNew;
    QAction *actionClose;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionShowMainToolbar;
    QAction *actionLoadImage;
    QAction *actionShowSegmentationToolbar;
    QAction *actionSet_Number_of_Classes;
    QAction *actionSelect_Marker;
    QAction *actionStart_Segmentation;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuSegmentation;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;
    QToolBar *SegmentationToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(562, 362);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionShowMainToolbar = new QAction(MainWindow);
        actionShowMainToolbar->setObjectName(QStringLiteral("actionShowMainToolbar"));
        actionShowMainToolbar->setCheckable(true);
        actionLoadImage = new QAction(MainWindow);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        actionLoadImage->setEnabled(true);
        actionLoadImage->setMenuRole(QAction::AboutRole);
        actionShowSegmentationToolbar = new QAction(MainWindow);
        actionShowSegmentationToolbar->setObjectName(QStringLiteral("actionShowSegmentationToolbar"));
        actionShowSegmentationToolbar->setCheckable(true);
        actionSet_Number_of_Classes = new QAction(MainWindow);
        actionSet_Number_of_Classes->setObjectName(QStringLiteral("actionSet_Number_of_Classes"));
        actionSelect_Marker = new QAction(MainWindow);
        actionSelect_Marker->setObjectName(QStringLiteral("actionSelect_Marker"));
        actionSelect_Marker->setEnabled(true);
        actionSelect_Marker->setMenuRole(QAction::AboutRole);
        actionStart_Segmentation = new QAction(MainWindow);
        actionStart_Segmentation->setObjectName(QStringLiteral("actionStart_Segmentation"));
        actionStart_Segmentation->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMouseTracking(false);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);

        horizontalLayout->addWidget(tabWidget);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 562, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuSegmentation = new QMenu(menuBar);
        menuSegmentation->setObjectName(QStringLiteral("menuSegmentation"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        SegmentationToolBar = new QToolBar(MainWindow);
        SegmentationToolBar->setObjectName(QStringLiteral("SegmentationToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, SegmentationToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuSegmentation->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSaveAs);
        menuFile->addAction(actionClose);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuView->addAction(actionShowMainToolbar);
        menuView->addAction(actionShowSegmentationToolbar);
        menuSegmentation->addAction(actionLoadImage);
        menuSegmentation->addAction(actionSet_Number_of_Classes);
        menuSegmentation->addSeparator();
        menuSegmentation->addAction(actionStart_Segmentation);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionSaveAs);
        mainToolBar->addAction(actionClose);
        mainToolBar->addAction(actionUndo);
        mainToolBar->addAction(actionRedo);
        SegmentationToolBar->addAction(actionLoadImage);
        SegmentationToolBar->addAction(actionStart_Segmentation);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSaveAs->setText(QApplication::translate("MainWindow", "Save As", 0));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("MainWindow", "Save File", 0));
#endif // QT_NO_TOOLTIP
        actionSaveAs->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "New Segmentation Project", 0));
#endif // QT_NO_TOOLTIP
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", 0));
        actionShowMainToolbar->setText(QApplication::translate("MainWindow", "Show Main Toolbar", 0));
        actionLoadImage->setText(QApplication::translate("MainWindow", "Load Image", 0));
        actionShowSegmentationToolbar->setText(QApplication::translate("MainWindow", "Show Segmentation Toolbar", 0));
        actionSet_Number_of_Classes->setText(QApplication::translate("MainWindow", "Set Number of Classes", 0));
#ifndef QT_NO_TOOLTIP
        actionSet_Number_of_Classes->setToolTip(QApplication::translate("MainWindow", "Set Number of Classes for Segmentation", 0));
#endif // QT_NO_TOOLTIP
        actionSelect_Marker->setText(QApplication::translate("MainWindow", "Select Marker", 0));
        actionStart_Segmentation->setText(QApplication::translate("MainWindow", "Start Segmentation", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
        menuSegmentation->setTitle(QApplication::translate("MainWindow", "Segmentation", 0));
        mainToolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        SegmentationToolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

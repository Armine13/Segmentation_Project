/********************************************************************************
** Form generated from reading UI file 'tab.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_H
#define UI_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QFrame *line;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_seg;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_image;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Tab)
    {
        if (Tab->objectName().isEmpty())
            Tab->setObjectName(QStringLiteral("Tab"));
        Tab->resize(499, 452);
        gridLayout = new QGridLayout(Tab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 2, 1, 1);

        line = new QFrame(Tab);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 5, 2, 1, 1);

        label_seg = new QLabel(Tab);
        label_seg->setObjectName(QStringLiteral("label_seg"));
        label_seg->setMinimumSize(QSize(200, 100));
        QFont font;
        font.setPointSize(15);
        label_seg->setFont(font);
        label_seg->setAutoFillBackground(false);
        label_seg->setStyleSheet(QLatin1String("border-style: dotted; \n"
"border-color: grey;\n"
"border-width: 1.5px;\n"
"border-radius: 15px;\n"
"color: grey;"));
        label_seg->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_seg, 6, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(131, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 7, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_image = new QLabel(Tab);
        label_image->setObjectName(QStringLiteral("label_image"));
        label_image->setMinimumSize(QSize(200, 100));
        label_image->setFont(font);
        label_image->setAutoFillBackground(false);
        label_image->setStyleSheet(QLatin1String("border-style: dotted; \n"
"border-color: grey;\n"
"border-width: 1.5px;\n"
"border-radius: 15px;\n"
"color: grey;"));
        label_image->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_image);


        gridLayout->addLayout(horizontalLayout, 1, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(131, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 6, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(132, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 6, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 2, 1, 1);


        retranslateUi(Tab);

        QMetaObject::connectSlotsByName(Tab);
    } // setupUi

    void retranslateUi(QWidget *Tab)
    {
        Tab->setWindowTitle(QApplication::translate("Tab", "Form", 0));
        label_seg->setText(QApplication::translate("Tab", "Segmented image", 0));
        label_image->setText(QApplication::translate("Tab", "Load image", 0));
    } // retranslateUi

};

namespace Ui {
    class Tab: public Ui_Tab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_H

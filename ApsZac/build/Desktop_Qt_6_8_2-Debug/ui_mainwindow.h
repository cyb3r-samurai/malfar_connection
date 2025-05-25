/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *lnIPAddress;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QSpinBox *spinPort;
    QPushButton *btnConnect;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QPushButton *pushButton;
    QLineEdit *ln_number;
    QGroupBox *grpSendData;
    QGridLayout *gridLayout_3;
    QPushButton *btnSend;
    QComboBox *cB_msg_type;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QListView *list_ka;
    QHBoxLayout *horizontalLayout;
    QCustomPlot *pl_time;
    QCustomPlot *dft_plot;
    QHBoxLayout *horizontalLayout_3;
    QListView *listView;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QTableView *tableView_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(924, 768);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(160000, 150));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_5->addWidget(label_2);

        lnIPAddress = new QLineEdit(groupBox);
        lnIPAddress->setObjectName("lnIPAddress");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lnIPAddress->sizePolicy().hasHeightForWidth());
        lnIPAddress->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(lnIPAddress);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout_6->addWidget(label);

        spinPort = new QSpinBox(groupBox);
        spinPort->setObjectName("spinPort");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinPort->sizePolicy().hasHeightForWidth());
        spinPort->setSizePolicy(sizePolicy2);
        spinPort->setMinimum(5555);
        spinPort->setMaximum(65535);
        spinPort->setValue(5555);

        horizontalLayout_6->addWidget(spinPort);


        gridLayout->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        btnConnect = new QPushButton(groupBox);
        btnConnect->setObjectName("btnConnect");

        gridLayout->addWidget(btnConnect, 2, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMaximumSize(QSize(160000, 150));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 1, 0, 1, 2);

        ln_number = new QLineEdit(groupBox_2);
        ln_number->setObjectName("ln_number");

        gridLayout_2->addWidget(ln_number, 0, 1, 1, 1);


        horizontalLayout_4->addWidget(groupBox_2);

        grpSendData = new QGroupBox(centralwidget);
        grpSendData->setObjectName("grpSendData");
        grpSendData->setEnabled(true);
        sizePolicy.setHeightForWidth(grpSendData->sizePolicy().hasHeightForWidth());
        grpSendData->setSizePolicy(sizePolicy);
        grpSendData->setMinimumSize(QSize(200, 0));
        grpSendData->setMaximumSize(QSize(16777215, 150));
        gridLayout_3 = new QGridLayout(grpSendData);
        gridLayout_3->setObjectName("gridLayout_3");
        btnSend = new QPushButton(grpSendData);
        btnSend->setObjectName("btnSend");

        gridLayout_3->addWidget(btnSend, 1, 0, 1, 1);

        cB_msg_type = new QComboBox(grpSendData);
        cB_msg_type->setObjectName("cB_msg_type");
        sizePolicy1.setHeightForWidth(cB_msg_type->sizePolicy().hasHeightForWidth());
        cB_msg_type->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(cB_msg_type, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(grpSendData);


        verticalLayout_3->addLayout(horizontalLayout_4);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        list_ka = new QListView(groupBox_3);
        list_ka->setObjectName("list_ka");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(list_ka->sizePolicy().hasHeightForWidth());
        list_ka->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(list_ka);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pl_time = new QCustomPlot(groupBox_3);
        pl_time->setObjectName("pl_time");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pl_time->sizePolicy().hasHeightForWidth());
        pl_time->setSizePolicy(sizePolicy4);
        pl_time->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pl_time);

        dft_plot = new QCustomPlot(groupBox_3);
        dft_plot->setObjectName("dft_plot");
        sizePolicy4.setHeightForWidth(dft_plot->sizePolicy().hasHeightForWidth());
        dft_plot->setSizePolicy(sizePolicy4);
        dft_plot->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(dft_plot);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        listView = new QListView(groupBox_3);
        listView->setObjectName("listView");
        sizePolicy3.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(listView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        tableView = new QTableView(groupBox_3);
        tableView->setObjectName("tableView");
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);

        verticalLayout_2->addWidget(tableView);

        tableView_2 = new QTableView(groupBox_3);
        tableView_2->setObjectName("tableView_2");

        verticalLayout_2->addWidget(tableView_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);

        verticalLayout_3->addWidget(groupBox_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 924, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\220\320\237\320\241 \320\267\320\260\320\272\320\260\320\267\321\207\320\270\320\272\320\260", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201\321\201:", nullptr));
        lnIPAddress->setInputMask(QCoreApplication::translate("MainWindow", "000.000.000.000;_", nullptr));
        lnIPAddress->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202:", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\276\320\265\320\264\320\265\320\275\320\265\320\275\320\270\320\265", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\206\320\265\320\273\320\265\321\203\320\272\320\276\320\267\320\260\320\275\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 \320\232\320\220 :", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        grpSendData->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\321\200\320\276\321\201 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\321\200\320\276\321\201\320\270\321\202\321\214", nullptr));
        groupBox_3->setTitle(QString());
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

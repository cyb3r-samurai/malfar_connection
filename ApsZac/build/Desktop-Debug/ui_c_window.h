/********************************************************************************
** Form generated from reading UI file 'c_window.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_WINDOW_H
#define UI_C_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_C_window
{
public:
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ln_session;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cb_pol;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *ln_freq;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDateTimeEdit *dateTimeEdit_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QLineEdit *ln_az;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QLineEdit *ln_angl;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;

    void setupUi(QDialog *C_window)
    {
        if (C_window->objectName().isEmpty())
            C_window->setObjectName("C_window");
        C_window->resize(663, 389);
        gridLayout_2 = new QGridLayout(C_window);
        gridLayout_2->setObjectName("gridLayout_2");
        tableWidget = new QTableWidget(C_window);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMaximumSize(QSize(200, 16777215));
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);

        gridLayout_2->addWidget(tableWidget, 0, 0, 8, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(C_window);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        ln_session = new QLineEdit(C_window);
        ln_session->setObjectName("ln_session");

        horizontalLayout->addWidget(ln_session);


        gridLayout_2->addLayout(horizontalLayout, 1, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(C_window);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        cb_pol = new QComboBox(C_window);
        cb_pol->setObjectName("cb_pol");

        horizontalLayout_2->addWidget(cb_pol);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(C_window);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_3);

        ln_freq = new QLineEdit(C_window);
        ln_freq->setObjectName("ln_freq");

        horizontalLayout_3->addWidget(ln_freq);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(C_window);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_4);

        dateTimeEdit = new QDateTimeEdit(C_window);
        dateTimeEdit->setObjectName("dateTimeEdit");

        horizontalLayout_4->addWidget(dateTimeEdit);


        gridLayout_2->addLayout(horizontalLayout_4, 4, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(C_window);
        label_5->setObjectName("label_5");
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_5);

        dateTimeEdit_2 = new QDateTimeEdit(C_window);
        dateTimeEdit_2->setObjectName("dateTimeEdit_2");

        horizontalLayout_5->addWidget(dateTimeEdit_2);


        gridLayout_2->addLayout(horizontalLayout_5, 5, 2, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_9 = new QLabel(C_window);
        label_9->setObjectName("label_9");

        horizontalLayout_9->addWidget(label_9);

        lineEdit = new QLineEdit(C_window);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_9->addWidget(lineEdit);


        gridLayout_2->addLayout(horizontalLayout_9, 6, 2, 1, 1);

        label_6 = new QLabel(C_window);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(label_6, 7, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pushButton_2 = new QPushButton(C_window);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_7 = new QLabel(C_window);
        label_7->setObjectName("label_7");

        verticalLayout_2->addWidget(label_7);

        ln_az = new QLineEdit(C_window);
        ln_az->setObjectName("ln_az");
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ln_az->sizePolicy().hasHeightForWidth());
        ln_az->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(ln_az);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        pushButton = new QPushButton(C_window);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_8 = new QLabel(C_window);
        label_8->setObjectName("label_8");

        verticalLayout_3->addWidget(label_8);

        ln_angl = new QLineEdit(C_window);
        ln_angl->setObjectName("ln_angl");
        sizePolicy3.setHeightForWidth(ln_angl->sizePolicy().hasHeightForWidth());
        ln_angl->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(ln_angl);


        gridLayout->addLayout(verticalLayout_3, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 8, 0, 1, 3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_7->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(C_window);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy3.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy3);
        pushButton_3->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(pushButton_3);


        gridLayout_2->addLayout(horizontalLayout_7, 9, 0, 1, 1);


        retranslateUi(C_window);

        QMetaObject::connectSlotsByName(C_window);
    } // setupUi

    void retranslateUi(QDialog *C_window)
    {
        C_window->setWindowTitle(QCoreApplication::translate("C_window", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("C_window", "\320\220\320\267\320\270\320\274\321\203\321\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("C_window", "\320\243\320\263\320\276\320\273 \320\274\320\265\321\201\321\202\320\260", nullptr));
        label->setText(QCoreApplication::translate("C_window", "\320\235\320\276\320\274\320\265\321\200 \320\272\320\260\320\275\320\260\320\273\320\260 \320\264\320\260\320\275\320\275\321\213\321\205:", nullptr));
        ln_session->setText(QCoreApplication::translate("C_window", "1", nullptr));
        label_2->setText(QCoreApplication::translate("C_window", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\265 \320\277\320\276\320\273\321\217\321\200\320\270\320\267\320\260\321\206\320\270\320\270 :", nullptr));
        label_3->setText(QCoreApplication::translate("C_window", "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\260\321\217 \321\207\320\260\321\201\321\202\320\276\321\202\320\260:", nullptr));
        ln_freq->setText(QCoreApplication::translate("C_window", "12123", nullptr));
        label_4->setText(QCoreApplication::translate("C_window", "\320\222\321\200\320\265\320\274\321\217 \320\275\320\260\321\207\320\260\320\275\320\273\320\260 \321\201\320\265\320\260\320\275\321\201\320\260:", nullptr));
        dateTimeEdit->setDisplayFormat(QCoreApplication::translate("C_window", "d/M/yy h:mm:ss", nullptr));
        label_5->setText(QCoreApplication::translate("C_window", "\320\222\321\200\320\265\320\274\321\217 \320\276\320\272\320\276\320\275\321\207\320\260\320\275\320\270\321\217 \321\201\320\265\320\260\320\275\321\201\320\260:", nullptr));
        dateTimeEdit_2->setDisplayFormat(QCoreApplication::translate("C_window", "d/M/yy h:mm:ss", nullptr));
        label_9->setText(QCoreApplication::translate("C_window", "\320\235\320\276\320\274\320\265\321\200 \320\232\320\220", nullptr));
        lineEdit->setText(QCoreApplication::translate("C_window", "2", nullptr));
        label_6->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("C_window", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_7->setText(QCoreApplication::translate("C_window", "\320\220\320\267\320\270\320\274\321\203\321\202", nullptr));
        pushButton->setText(QCoreApplication::translate("C_window", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_8->setText(QCoreApplication::translate("C_window", "\320\243\320\263\320\276\320\273 \320\274\320\265\321\201\321\202\320\260", nullptr));
        pushButton_3->setText(QCoreApplication::translate("C_window", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_window: public Ui_C_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_WINDOW_H

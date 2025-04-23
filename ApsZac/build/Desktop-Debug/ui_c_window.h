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
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
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
    QLineEdit *ln_step;
    QLabel *label_6;
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
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pushButton_2 = new QPushButton(C_window);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_7 = new QLabel(C_window);
        label_7->setObjectName("label_7");

        verticalLayout_2->addWidget(label_7);

        ln_az = new QLineEdit(C_window);
        ln_az->setObjectName("ln_az");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ln_az->sizePolicy().hasHeightForWidth());
        ln_az->setSizePolicy(sizePolicy);

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
        sizePolicy.setHeightForWidth(ln_angl->sizePolicy().hasHeightForWidth());
        ln_angl->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(ln_angl);


        gridLayout->addLayout(verticalLayout_3, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        tableWidget = new QTableWidget(C_window);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMaximumSize(QSize(200, 16777215));
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 20, 20, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(C_window);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(label);

        ln_session = new QLineEdit(C_window);
        ln_session->setObjectName("ln_session");

        horizontalLayout->addWidget(ln_session);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(C_window);
        label_2->setObjectName("label_2");
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(label_2);

        cb_pol = new QComboBox(C_window);
        cb_pol->setObjectName("cb_pol");

        horizontalLayout_2->addWidget(cb_pol);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(C_window);
        label_3->setObjectName("label_3");
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(label_3);

        ln_freq = new QLineEdit(C_window);
        ln_freq->setObjectName("ln_freq");

        horizontalLayout_3->addWidget(ln_freq);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(C_window);
        label_4->setObjectName("label_4");
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_4);

        dateTimeEdit = new QDateTimeEdit(C_window);
        dateTimeEdit->setObjectName("dateTimeEdit");

        horizontalLayout_4->addWidget(dateTimeEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(C_window);
        label_5->setObjectName("label_5");
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(label_5);

        ln_step = new QLineEdit(C_window);
        ln_step->setObjectName("ln_step");

        horizontalLayout_5->addWidget(ln_step);


        verticalLayout->addLayout(horizontalLayout_5);

        label_6 = new QLabel(C_window);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(label_6);


        gridLayout_2->addLayout(verticalLayout, 0, 2, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(C_window);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(pushButton_3);


        gridLayout_2->addLayout(horizontalLayout_7, 4, 0, 1, 3);


        retranslateUi(C_window);

        QMetaObject::connectSlotsByName(C_window);
    } // setupUi

    void retranslateUi(QDialog *C_window)
    {
        C_window->setWindowTitle(QCoreApplication::translate("C_window", "Dialog", nullptr));
        pushButton_2->setText(QCoreApplication::translate("C_window", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_7->setText(QCoreApplication::translate("C_window", "\320\220\320\267\320\270\320\274\321\203\321\202", nullptr));
        pushButton->setText(QCoreApplication::translate("C_window", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_8->setText(QCoreApplication::translate("C_window", "\320\243\320\263\320\276\320\273 \320\274\320\265\321\201\321\202\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("C_window", "\320\220\320\267\320\270\320\274\321\203\321\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("C_window", "\320\243\320\263\320\276\320\273 \320\274\320\265\321\201\321\202\320\260", nullptr));
        label->setText(QCoreApplication::translate("C_window", "\320\234\320\265\321\202\320\272\320\260 \321\201\320\265\320\260\320\275\321\201\320\260:", nullptr));
        label_2->setText(QCoreApplication::translate("C_window", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\265 \320\277\320\276\320\273\321\217\321\200\320\270\320\267\320\260\321\206\320\270\320\270 :", nullptr));
        label_3->setText(QCoreApplication::translate("C_window", "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\260\321\217 \321\207\320\260\321\201\321\202\320\276\321\202\320\260:", nullptr));
        label_4->setText(QCoreApplication::translate("C_window", "\320\222\321\200\320\265\320\274\321\217 \320\275\320\260\321\207\320\260\320\275\320\273\320\260 \321\201\320\265\320\260\320\275\321\201\320\260:", nullptr));
        dateTimeEdit->setDisplayFormat(QCoreApplication::translate("C_window", "M/d/yy h:mm:ss", nullptr));
        label_5->setText(QCoreApplication::translate("C_window", "\320\250\320\260\320\263 \320\274\320\265\320\266\320\264\321\203 \321\206\320\265\320\273\320\265\321\203\320\272\320\276\320\267\320\260\320\275\320\270\321\217\320\274\320\270 :", nullptr));
        label_6->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("C_window", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_window: public Ui_C_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_WINDOW_H

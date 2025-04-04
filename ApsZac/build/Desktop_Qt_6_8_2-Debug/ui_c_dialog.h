/********************************************************************************
** Form generated from reading UI file 'c_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_DIALOG_H
#define UI_C_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_C_Dialog
{
public:

    void setupUi(QDialog *C_Dialog)
    {
        if (C_Dialog->objectName().isEmpty())
            C_Dialog->setObjectName("C_Dialog");
        C_Dialog->resize(400, 300);

        retranslateUi(C_Dialog);

        QMetaObject::connectSlotsByName(C_Dialog);
    } // setupUi

    void retranslateUi(QDialog *C_Dialog)
    {
        C_Dialog->setWindowTitle(QCoreApplication::translate("C_Dialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_Dialog: public Ui_C_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_DIALOG_H

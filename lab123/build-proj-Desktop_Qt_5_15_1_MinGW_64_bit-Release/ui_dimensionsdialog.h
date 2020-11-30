/********************************************************************************
** Form generated from reading UI file 'dimensionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIMENSIONSDIALOG_H
#define UI_DIMENSIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DimensionsDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lengthEdit;
    QLineEdit *widthEdit;

    void setupUi(QDialog *DimensionsDialog)
    {
        if (DimensionsDialog->objectName().isEmpty())
            DimensionsDialog->setObjectName(QString::fromUtf8("DimensionsDialog"));
        DimensionsDialog->resize(300, 200);
        DimensionsDialog->setMinimumSize(QSize(300, 200));
        DimensionsDialog->setMaximumSize(QSize(16777215, 300));
        gridLayout = new QGridLayout(DimensionsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        okButton = new QPushButton(DimensionsDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        gridLayout->addWidget(okButton, 1, 1, 1, 1);

        cancelButton = new QPushButton(DimensionsDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(DimensionsDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(DimensionsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lengthEdit = new QLineEdit(DimensionsDialog);
        lengthEdit->setObjectName(QString::fromUtf8("lengthEdit"));

        gridLayout_2->addWidget(lengthEdit, 0, 1, 1, 1);

        widthEdit = new QLineEdit(DimensionsDialog);
        widthEdit->setObjectName(QString::fromUtf8("widthEdit"));

        gridLayout_2->addWidget(widthEdit, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 3);


        retranslateUi(DimensionsDialog);

        QMetaObject::connectSlotsByName(DimensionsDialog);
    } // setupUi

    void retranslateUi(QDialog *DimensionsDialog)
    {
        DimensionsDialog->setWindowTitle(QCoreApplication::translate("DimensionsDialog", "Dialog", nullptr));
        okButton->setText(QCoreApplication::translate("DimensionsDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("DimensionsDialog", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("DimensionsDialog", "Horizontal", nullptr));
        label_2->setText(QCoreApplication::translate("DimensionsDialog", "Vertical", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DimensionsDialog: public Ui_DimensionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIMENSIONSDIALOG_H

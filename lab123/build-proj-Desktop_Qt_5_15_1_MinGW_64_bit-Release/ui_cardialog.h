/********************************************************************************
** Form generated from reading UI file 'cardialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDIALOG_H
#define UI_CARDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CarDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_7;
    QComboBox *comboBox;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_4;
    QLineEdit *brandEdit;
    QLineEdit *widthEdit;
    QLineEdit *lengthEdit;
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *angleEdit;
    QLineEdit *radiusEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *label_9;
    QComboBox *posCombo;

    void setupUi(QDialog *CarDialog)
    {
        if (CarDialog->objectName().isEmpty())
            CarDialog->setObjectName(QString::fromUtf8("CarDialog"));
        CarDialog->resize(320, 400);
        CarDialog->setMinimumSize(QSize(320, 400));
        gridLayout = new QGridLayout(CarDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CarDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(CarDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(CarDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_5 = new QLabel(CarDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_7 = new QLabel(CarDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        comboBox = new QComboBox(CarDialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label_8 = new QLabel(CarDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 8, 0, 1, 1);

        label_6 = new QLabel(CarDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label_4 = new QLabel(CarDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        brandEdit = new QLineEdit(CarDialog);
        brandEdit->setObjectName(QString::fromUtf8("brandEdit"));

        gridLayout->addWidget(brandEdit, 1, 1, 1, 3);

        widthEdit = new QLineEdit(CarDialog);
        widthEdit->setObjectName(QString::fromUtf8("widthEdit"));

        gridLayout->addWidget(widthEdit, 2, 1, 1, 3);

        lengthEdit = new QLineEdit(CarDialog);
        lengthEdit->setObjectName(QString::fromUtf8("lengthEdit"));

        gridLayout->addWidget(lengthEdit, 3, 1, 1, 3);

        xEdit = new QLineEdit(CarDialog);
        xEdit->setObjectName(QString::fromUtf8("xEdit"));

        gridLayout->addWidget(xEdit, 4, 1, 1, 3);

        yEdit = new QLineEdit(CarDialog);
        yEdit->setObjectName(QString::fromUtf8("yEdit"));

        gridLayout->addWidget(yEdit, 5, 1, 1, 3);

        angleEdit = new QLineEdit(CarDialog);
        angleEdit->setObjectName(QString::fromUtf8("angleEdit"));

        gridLayout->addWidget(angleEdit, 6, 1, 1, 3);

        radiusEdit = new QLineEdit(CarDialog);
        radiusEdit->setObjectName(QString::fromUtf8("radiusEdit"));

        gridLayout->addWidget(radiusEdit, 8, 1, 1, 3);

        okButton = new QPushButton(CarDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setEnabled(true);

        gridLayout->addWidget(okButton, 9, 2, 1, 1);

        cancelButton = new QPushButton(CarDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 9, 3, 1, 1);

        label_9 = new QLabel(CarDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 0, 2, 1, 1);

        posCombo = new QComboBox(CarDialog);
        posCombo->addItem(QString());
        posCombo->setObjectName(QString::fromUtf8("posCombo"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(posCombo->sizePolicy().hasHeightForWidth());
        posCombo->setSizePolicy(sizePolicy);

        gridLayout->addWidget(posCombo, 0, 3, 1, 1);


        retranslateUi(CarDialog);

        QMetaObject::connectSlotsByName(CarDialog);
    } // setupUi

    void retranslateUi(QDialog *CarDialog)
    {
        CarDialog->setWindowTitle(QCoreApplication::translate("CarDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CarDialog", "Item type", nullptr));
        label_3->setText(QCoreApplication::translate("CarDialog", "Width", nullptr));
        label_2->setText(QCoreApplication::translate("CarDialog", "Brand", nullptr));
        label_5->setText(QCoreApplication::translate("CarDialog", "X", nullptr));
        label_7->setText(QCoreApplication::translate("CarDialog", "Angle", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("CarDialog", "Car", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("CarDialog", "Podium", nullptr));

        label_8->setText(QCoreApplication::translate("CarDialog", "Radius", nullptr));
        label_6->setText(QCoreApplication::translate("CarDialog", "Y", nullptr));
        label_4->setText(QCoreApplication::translate("CarDialog", "Length", nullptr));
        okButton->setText(QCoreApplication::translate("CarDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("CarDialog", "Cancel", nullptr));
        label_9->setText(QCoreApplication::translate("CarDialog", "on position", nullptr));
        posCombo->setItemText(0, QCoreApplication::translate("CarDialog", "[end]", nullptr));

    } // retranslateUi

};

namespace Ui {
    class CarDialog: public Ui_CarDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDIALOG_H

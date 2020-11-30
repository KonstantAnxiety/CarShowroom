#include "dimensionsdialog.h"
#include "ui_dimensionsdialog.h"
#include <QDoubleValidator>
#include <QMessageBox>

DimensionsDialog::DimensionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DimensionsDialog)
{
    ui->setupUi(this);

    QDoubleValidator *val = new QDoubleValidator(0, 100, 3);
    ui->lengthEdit->setValidator(val);
    ui->widthEdit->setValidator(val);
}

DimensionsDialog::~DimensionsDialog()
{
    delete ui;
}

int DimensionsDialog::getWidth() const
{
    return ui->widthEdit->text().toInt();
}

int DimensionsDialog::getLength() const
{
    return ui->lengthEdit->text().toInt();
}

void DimensionsDialog::on_okButton_clicked()
{
    if (ui->widthEdit->text().isEmpty() ||
            ui->lengthEdit->text().isEmpty())
        QMessageBox::warning(this, "Rejected!", "Please provide all parameters");
    else
        this->accept();
}

void DimensionsDialog::on_cancelButton_clicked()
{
    this->reject();
}

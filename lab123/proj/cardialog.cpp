#include "cardialog.h"
#include "ui_cardialog.h"
#include <QDoubleValidator>
#include <QMessageBox>
#include "car.h"
#include "podium.h"

CarDialog::CarDialog(QWidget *parent, int size) :
    QDialog(parent),
    ui(new Ui::CarDialog)
{
    ui->setupUi(this);

    ui->radiusEdit->setEnabled(false);
    ui->angleEdit->setEnabled(true);
    ui->widthEdit->setEnabled(true);
    ui->lengthEdit->setEnabled(true);

    QDoubleValidator *val = new QDoubleValidator(0, 100, 3);
    ui->widthEdit->setValidator(val);
    ui->lengthEdit->setValidator(val);
    ui->angleEdit->setValidator(val);
    ui->radiusEdit->setValidator(val);
    ui->xEdit->setValidator(val);
    ui->yEdit->setValidator(val);

    for (int i = 0; i < size; ++i)
        ui->posCombo->addItem(QString::number(i));
}

CarDialog::~CarDialog()
{
    delete ui;
}

Point *CarDialog::getItem() const
{
    Point *item;
    if (ui->comboBox->currentIndex() == 0)
        item = new Car(ui->widthEdit->text().toDouble(),
                       ui->lengthEdit->text().toDouble(),
                       ui->xEdit->text().toDouble(),
                       ui->yEdit->text().toDouble(),
                       ui->angleEdit->text().toDouble(),
                       ui->brandEdit->text().toStdString());
    else if (ui->comboBox->currentIndex() == 1)
        item = new Podium(ui->xEdit->text().toDouble(),
                          ui->yEdit->text().toDouble(),
                          ui->radiusEdit->text().toDouble(),
                          ui->brandEdit->text().toStdString());
    else
        item = new Point;
    std::cout << *item;
    return item;
}

int CarDialog::getPos() const
{
    return ui->posCombo->currentIndex();
}

void CarDialog::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->radiusEdit->setEnabled(false);
        ui->angleEdit->setEnabled(true);
        ui->widthEdit->setEnabled(true);
        ui->lengthEdit->setEnabled(true);
    } else if (index == 1) {
        ui->radiusEdit->setEnabled(true);
        ui->angleEdit->setEnabled(false);
        ui->widthEdit->setEnabled(false);
        ui->lengthEdit->setEnabled(false);
    }
}

void CarDialog::on_cancelButton_clicked()
{
    this->reject();
}

void CarDialog::on_okButton_clicked()
{
    if (ui->brandEdit->text().isEmpty() ||
            ui->xEdit->text().isEmpty() ||
            ui->yEdit->text().isEmpty())
        QMessageBox::warning(this, "Rejected!", "Please provide all parameters");
    else if (ui->comboBox->currentIndex() == 0 &&
             (ui->widthEdit->text().isEmpty() ||
             ui->lengthEdit->text().isEmpty() ||
             ui->angleEdit->text().isEmpty()))
        QMessageBox::warning(this, "Rejected!", "Please provide all parameters");
    else if (ui->comboBox->currentIndex() == 1 &&
             ui->radiusEdit->text().isEmpty())
        QMessageBox::warning(this, "Rejected!", "Please provide all parameters");
    else
        this->accept();
}

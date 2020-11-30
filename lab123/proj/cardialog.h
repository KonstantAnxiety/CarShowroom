#ifndef CARDIALOG_H
#define CARDIALOG_H

#include <QDialog>
#include "point.h"

namespace Ui {
class CarDialog;
}

class CarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CarDialog(QWidget *parent = nullptr, int size = 0);
    ~CarDialog();
    Point *getItem() const;
    int getPos() const;

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::CarDialog *ui;
    QString brand;
};

#endif // CARDIALOG_H

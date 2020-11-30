#ifndef DIMENSIONSDIALOG_H
#define DIMENSIONSDIALOG_H

#include <QDialog>

namespace Ui {
class DimensionsDialog;
}

class DimensionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DimensionsDialog(QWidget *parent = nullptr);
    ~DimensionsDialog();
    int getWidth() const;
    int getLength() const;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::DimensionsDialog *ui;
};

#endif // DIMENSIONSDIALOG_H

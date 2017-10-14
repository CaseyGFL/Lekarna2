#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QItemSelectionModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    int id;
    QString name;
    bool filled;

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QSqlTableModel *model;
    QSqlDatabase db;
    QItemSelectionModel *selection;
};

#endif // DIALOG_H

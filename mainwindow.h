#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogleky.h"
#include "dialogpacient.h"
#include <QSqlTableModel>
#include "dialog.h"
#include "dialogsklad.h"
#include "dialogchangemnozstvi.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString name_skladu;
    int iddialog;
private slots:
    void on_pushButton_clicked();

    void on_delete_leky_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void set_sklad();

    void add_objednavka();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlDatabase db;
    Dialog dialog;
};

#endif // MAINWINDOW_H

#ifndef DIALOGLEKY_H
#define DIALOGLEKY_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class Dialogleky;
}

class Dialogleky : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogleky(QWidget *parent = 0);
    ~Dialogleky();
public slots:
    void getCombobox(QString name);
    void comboBoxItemadd();

private slots:
    void on_buttonBox_accepted();



private:
    Ui::Dialogleky *ui;
    QSqlTableModel *model;
    QSqlDatabase db;

};

#endif // DIALOGLEKY_H

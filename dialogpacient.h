#ifndef DIALOGPACIENT_H
#define DIALOGPACIENT_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class Dialogpacient;
}

class Dialogpacient : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogpacient(QWidget *parent = 0);
    ~Dialogpacient();
    QString id;
    QSqlTableModel *model;
public slots:

    QString get_name();
    QString get_surrname();
    QString get_id();
    QString get_mnozstvi();


private:
    Ui::Dialogpacient *ui;

    QSqlDatabase db;
};

#endif // DIALOGPACIENT_H

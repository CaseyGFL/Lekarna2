#include "dialogleky.h"
#include "ui_dialogleky.h"
#include <QSqlQuery>
#include <QDebug>
Dialogleky::Dialogleky(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogleky)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../lekarna/lekarna.db");
    db.open();
    model = new QSqlTableModel(this);
    model->setTable("sklady");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->hideColumn(0);
    model->select();
}

Dialogleky::~Dialogleky()
{
    delete ui;
}

void Dialogleky::getCombobox(QString name)
{

}

void Dialogleky::comboBoxItemadd()
{


}



void Dialogleky::on_buttonBox_accepted()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QString ids;
    QString sql = "INSERT INTO leky VALUES (NULL,";
    QModelIndex index = selection->selectedRows().at(0);
    QString id = QString::number(model->data(index).toInt());
    QString sql2 = "SELECT * FROM sklady WHERE id=" + id;
    QSqlQuery dotaz2;
    dotaz2.prepare(sql2);
    dotaz2.exec();
    dotaz2.first();
    QString name = dotaz2.value("nazev").toString();
    int price = ui->cena_spin->value();
    double mnozstvi = ui->mnozstvi_spin->value();
    sql+="'" + ui->lineEdit->text() + "','" + id + "', '" + name + "','" + QString::number(mnozstvi) + "','" + QString::number(price) + "')";
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();

}



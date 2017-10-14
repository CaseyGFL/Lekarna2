#include "dialogpacient.h"
#include "ui_dialogpacient.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
Dialogpacient::Dialogpacient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogpacient)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../lekarna/lekarna.db");
    db.open();
    model = new QSqlTableModel(this);
    model->setTable("leky");
    model->select();


    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);


    model->select();
}

Dialogpacient::~Dialogpacient()
{
    delete ui;
}

QString Dialogpacient::get_name()
{
    return ui->lineEdit->text();
}

QString Dialogpacient::get_surrname()
{
    return ui->lineEdit_2->text();
}

QString Dialogpacient::get_id()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if(selection->selectedRows().count()==0){
        this->reject();
        id=-1;
        return id;
    }
    else{
    QModelIndex index = selection->selectedRows().at(0);
    QString id = QString::number(model->data(index).toInt());
    return id;
    }
}

QString Dialogpacient::get_mnozstvi()
{
    return QString::number(ui->spinBox->value());
}



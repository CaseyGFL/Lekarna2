#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlQuery>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../lekarna/lekarna.db");
    db.open();
    model = new QSqlTableModel(this);
    model->setTable("sklady");
    model->select();
    this->setWindowTitle("Přidání léku");
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->hideColumn(0);
    model->select();
}

Dialog::~Dialog()
{

    delete ui;

}

void Dialog::on_buttonBox_accepted()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if(selection->selectedRows().count()>0){
    QModelIndex index = selection->selectedRows().at(0);
    id = model->data(index).toInt();
    filled= true;
}
    else{
        filled = false;
        id=0;
    }



}

void Dialog::on_pushButton_clicked()
{
    name = "";
    filled=false;
    id=0;
    this->close();
}

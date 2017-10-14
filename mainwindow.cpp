#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogleky.h"
#include "dialogpacient.h"
#include <QSqlDatabase>
#include <QItemSelectionModel>
#include <QDebug>
#include <QModelIndex>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Dialog dialog;
    dialog.exec();
    name_skladu =dialog.name;
    MainWindow::showMaximized();
    MainWindow::setMinimumSize(800,800);
    ui->setupUi(this);

    // otevření databáze
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../lekarna/lekarna.db");
    db.open();

    //první model pacienti
    model = new QSqlTableModel(this);
    model->setTable("pacienti");
    model->setHeaderData(1, Qt::Horizontal, "jmeno");
    model->setHeaderData(2, Qt::Horizontal, "prijmeni");
    model->setHeaderData(3, Qt::Horizontal, "id_leku");
    ui->tableView->setModel(model);
    model->select();
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(3);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //druhý model léky
    model2 = new QSqlTableModel(this);
    model2->setTable("leky");
    model2->select();
    model2->setHeaderData(1, Qt::Horizontal, "nazev");
    model2->setHeaderData(2, Qt::Horizontal, "id_skladu");

    ui->tableView_2->setModel(model2);
    ui->tableView_2->setColumnWidth(1, 200);




    ui->tableView_2->hideColumn(0);



    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionMode(QAbstractItemView::MultiSelection);

    QSqlQuery dotaz;
    QString sql = "SELECT * FROM sklady WHERE id=" + QString::number(dialog.id);
    dotaz.prepare(sql);
    dotaz.exec();
    dotaz.first();
    name_skladu = dotaz.value("nazev").toString();
    if(dialog.filled==false){
        ui->using_sklad->setText("Admin");
            ui->tableView_2->hideColumn(2);
            ui->pushButton_5->setVisible(true);
            model2->setFilter("");
    }
    else{
    ui->using_sklad->setText("Aktuální sklad:   " + name_skladu);
    model2->setFilter("id_sklad = '" + QString::number(dialog.id) + "'");
    iddialog = dialog.id;
    ui->tableView_2->hideColumn(2);
    ui->tableView_2->hideColumn(3);
    ui->pushButton_5->setVisible(false);


    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    Dialogleky d;


    if(d.exec() == QDialog::Accepted)
    {
        model2->select();
    }

}

void MainWindow::on_delete_leky_clicked()
{

        QItemSelectionModel *selection = ui->tableView_2->selectionModel();
        for (int i = 0; i < selection->selectedRows().count(); ++i) {

                QModelIndex index = selection->selectedRows().at(i);
                QString id = QString::number(model2->data(index).toInt());


                 QString sql2 = "DELETE FROM leky WHERE id=";
                 sql2+=id;
                 QSqlQuery dotaz;
                 dotaz.prepare(sql2);
                 dotaz.exec();
        }

        model2->select();



}

void MainWindow::on_pushButton_2_clicked()
{
    Dialogpacient d2;
    QString filter = "id_sklad = '" + QString::number(iddialog) + "'";
    if(ui->using_sklad->text()=="Admin"){
        filter= "";
    }
    d2.model->setFilter(filter);
    if(d2.exec() == QDialog::Accepted)
    {
        QString id = d2.get_id();
        QString name = d2.get_name();
        QString surrname = d2.get_surrname();
        QString mnozstvi = d2.get_mnozstvi();
        QString sql2 = "SELECT * FROM leky WHERE id=" + id;
        QSqlQuery dotaz2;
        dotaz2.prepare(sql2);

        dotaz2.exec();
        dotaz2.first();
        QString name_leku = dotaz2.value("nazev").toString();
        QString sql = "INSERT INTO pacienti VALUES (NULL,'";
        sql+= name;
        sql+= "','" + surrname + "','" + id + "','" + name_leku + "'," + mnozstvi + ")";
        if(id!="ÿ"){
        QSqlQuery dotaz;
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Dokončit?", "Doopravdy chcete přidat objednávku na " + name_leku +" v množství " + mnozstvi,
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
              QString sql3 = "SELECT mnozstvi_ks FROM leky WHERE id=" + id;
              QSqlQuery dotaz4;
              dotaz4.prepare(sql3);
              dotaz4.exec();
              dotaz4.first();
              int puvodni_ks = dotaz4.value("mnozstvi_ks").toInt();
              int cilovy_ks = puvodni_ks - mnozstvi.toInt();
              if(cilovy_ks>=0){
              dotaz.prepare(sql);
              dotaz.exec();
              model->select();
              QSqlQuery dotaz5;
              QString sql5 = "UPDATE leky SET mnozstvi_ks = '" + QString::number(cilovy_ks) + "' WHERE id='" + id + "'";
              dotaz5.prepare(sql5);
              dotaz5.exec();
              model2->select();
              }
              else{
                  QMessageBox::critical(this,"Error", "Tolik zboží není na tomto skladě! (Objednávka neprovedena");
              }
          } else {

          }
        }

    }



}

void MainWindow::on_pushButton_4_clicked()
{
    set_sklad();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString dank = "nazev like '%" + ui->lineEdit->text() + "%' and id_sklad = '" + name_skladu + "'";
    model2->setFilter(dank);
    model2->select();
}

void MainWindow::set_sklad()
{
    if(dialog.exec() == QDialog::Accepted || dialog.close())
    {

        model2->select();
        QSqlQuery dotaz;
        QString sql = "SELECT * FROM sklady WHERE id=" + QString::number(dialog.id);
        dotaz.prepare(sql);
        dotaz.exec();
        dotaz.first();
        if( dialog.filled==false){
            ui->using_sklad->setText("Admin");
            ui->tableView_2->showColumn(3);
            model2->setFilter("");
            ui->pushButton_5->setVisible(true);
        }
        else{
        name_skladu = dotaz.value("nazev").toString();
        ui->using_sklad->setText("Aktuální sklad:   " + name_skladu);
        model2->setFilter("id_sklad = '" + QString::number(dialog.id) + "'");
        iddialog = dialog.id;
        ui->pushButton_5->setVisible(false);
        ui->tableView_2->hideColumn(3);
        }
    }

}

void MainWindow::add_objednavka()
{





}



void MainWindow::on_pushButton_5_clicked()
{
    DialogSklad dialogsklad;
    dialogsklad.exec();
}



void MainWindow::on_pushButton_6_clicked()
{
    Dialogchangemnozstvi addmnozstvi;
    QItemSelectionModel *selection = ui->tableView_2->selectionModel();
    QModelIndex index = selection->selectedRows().at(0);
    QString miau = QString::number(model2->data(index).toInt());
    QSqlQuery select_name;
    QString sql3 = "SELECT nazev FROM leky WHERE id=" + miau;
    select_name.prepare(sql3);
    select_name.exec();
    select_name.first();
    addmnozstvi.setWindowTitle("Pridani leku : " + select_name.value("nazev").toString());
    if(selection->selectedRows().count() == 1){
    if(addmnozstvi.exec() == QDialog::Accepted){
        QString sql = "SELECT mnozstvi_ks FROM leky WHERE id=" + miau;
        QSqlQuery dotaz;
        dotaz.prepare(sql);
        dotaz.exec();
        dotaz.first();
        int puvodni_ks = dotaz.value("mnozstvi_ks").toInt();
        int cilovy_ks = puvodni_ks + addmnozstvi.get_value();
        QSqlQuery dotaz2;
        QString sql2 = "UPDATE leky SET mnozstvi_ks = '" + QString::number(cilovy_ks) + "' WHERE id='" + miau + "'";
        dotaz2.prepare(sql2);
        dotaz2.exec();
        model2->select();
    }
    }
    else{
        QMessageBox::warning(this,"Příliš mnoho léků", "Vyberte prosím jen jeden lék.");
    }
}

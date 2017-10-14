#include "dialogsklad.h"
#include "ui_dialogsklad.h"

DialogSklad::DialogSklad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSklad)
{
    ui->setupUi(this);
}

DialogSklad::~DialogSklad()
{
    delete ui;
}

#include "dialogchangemnozstvi.h"
#include "ui_dialogchangemnozstvi.h"

Dialogchangemnozstvi::Dialogchangemnozstvi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogchangemnozstvi)
{
    ui->setupUi(this);
    this->setWindowTitle("Přidání množství léku");
}

Dialogchangemnozstvi::~Dialogchangemnozstvi()
{
    delete ui;
}

int Dialogchangemnozstvi::get_value()
{
    return ui->spinBox->value();
}

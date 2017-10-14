#ifndef DIALOGCHANGEMNOZSTVI_H
#define DIALOGCHANGEMNOZSTVI_H

#include <QDialog>

namespace Ui {
class Dialogchangemnozstvi;
}

class Dialogchangemnozstvi : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogchangemnozstvi(QWidget *parent = 0);
    ~Dialogchangemnozstvi();
public slots:
    int get_value();

private:
    Ui::Dialogchangemnozstvi *ui;
};

#endif // DIALOGCHANGEMNOZSTVI_H

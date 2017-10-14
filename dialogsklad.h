#ifndef DIALOGSKLAD_H
#define DIALOGSKLAD_H

#include <QDialog>

namespace Ui {
class DialogSklad;
}

class DialogSklad : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSklad(QWidget *parent = 0);
    ~DialogSklad();

private:
    Ui::DialogSklad *ui;
};

#endif // DIALOGSKLAD_H

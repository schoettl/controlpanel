#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QList>
#include <QDialog>

#include "buttonconfig.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    explicit MainDialog(const QList<ButtonConfig>&);
    ~MainDialog();

private:
    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H

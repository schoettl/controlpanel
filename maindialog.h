#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QList>
#include <QDialog>
#include "buttonconfig.h"
#include "mybutton.h"

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
    QList<MyButton*> buttonList;
private slots:
    void buttonClicked()
    {
        foreach (MyButton* button, buttonList)
        {
            button->updateVisibility();
        }
    }
};

#endif // MAINDIALOG_H

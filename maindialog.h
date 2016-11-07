#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "ui_maindialog.h"
#include "buttonconfig.h"
#include "mybutton.h"
#include <QDebug>
#include <QWidget>
#include <QList>
#include <QDialog>


namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::MainDialog *ui;
    QList<MyButton*> buttonList;

public:

    explicit MainDialog(QWidget *parent = NULL) :
        QDialog(parent),
        ui(new Ui::MainDialog)
    {
        ui->setupUi(this);
    }

    explicit MainDialog(const QList<ButtonConfig> &list) :
        MainDialog((QWidget*) NULL)
    {
        int insertIndex = 0;
        foreach (const ButtonConfig& bc, list)
        {
            qDebug() << bc.caption;
            MyButton* button = new MyButton(bc);
            QObject::connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
            buttonList.append(button);
            ui->buttonlist->insertWidget(insertIndex++, button);
        }
    }

    ~MainDialog()
    {
        delete ui;
    }
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

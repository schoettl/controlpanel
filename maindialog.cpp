#include "maindialog.h"
#include "ui_maindialog.h"
#include "mybutton.h"
#include <QDebug>
#include <QWidget>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::MainDialog(const QList<ButtonConfig> &list) :
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

MainDialog::~MainDialog()
{
    delete ui;
}

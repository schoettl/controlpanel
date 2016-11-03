#include "maindialog.h"
#include "ui_maindialog.h"
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
    foreach(const ButtonConfig& bc, list)
    {
        qDebug() << bc.caption;
        QPushButton* button = new QPushButton();
        button->setText(bc.caption);
        // TODO set action
        // QObject::connect(button, SIGNAL(clicked()), &
        ui->buttonlist->insertWidget(insertIndex++, button);
    }
}

// TODO on show: set visibility of buttons

MainDialog::~MainDialog()
{
    delete ui;
}

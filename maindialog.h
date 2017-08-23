#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "ui_maindialog.h"
#include "buttonconfig.h"
#include "mybutton.h"
#include <QDebug>
#include <QWidget>
#include <QList>
#include <QDialog>
#include <QCloseEvent>
#include <QIcon>
#include <QSystemTrayIcon>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

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
        trayIcon = new QSystemTrayIcon(this);
        trayIcon->setIcon(QIcon(":/images/menu_white.png"));
        trayIcon->show();
        QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconClicked()));

        int insertIndex = 0;
        foreach (const ButtonConfig& bc, list)
        {
            //qDebug() << bc.caption;
            MyButton* button = new MyButton(bc);
            connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
            buttonList.append(button);
            ui->buttonlist->insertWidget(insertIndex++, button);
        }

        adjustSize();

        // http://stackoverflow.com/questions/696209/non-resizeable-qdialog-with-fixed-size-in-qt
        // layout()->setSizeConstraint(QLayout::SetFixedSize);
        // -> Prgram crashes

        setFixedSize(size());

    }

    ~MainDialog()
    {
        delete ui;
    }

protected:
    virtual void closeEvent(QCloseEvent *event)
    {
        QDialog::closeEvent(event);
        event->ignore();
        hide();
    }

    virtual void showEvent(QShowEvent *event)
    {
        updateButtonVisibility();
    }

private slots:
    void buttonClicked()
    {
        updateButtonVisibility();
    }

    void trayIconClicked()
    {
        qDebug() << "Tray icon clicked.";
        if (isVisible())
        {
            qDebug() << "Hiding main window.";
            hide();
        }
        else
        {
            qDebug() << "Showing main window.";
            show();
        }
    }

private:
    Ui::MainDialog *ui;
    QSystemTrayIcon* trayIcon;
    QList<MyButton*> buttonList;

    void updateButtonVisibility()
    {
        qDebug() << "Updating visibility for all buttons.";
        foreach (MyButton* button, buttonList)
        {
            button->updateVisibility();
        }
    }
};

#endif // MAINDIALOG_H

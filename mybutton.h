#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QApplication>
#include <QThread>

#include "buttonconfig.h"

class MyButton : public QPushButton
{
    Q_OBJECT // required to enable use of slots
private:
    const ButtonConfig& buttonConfig;
public:
    MyButton(const ButtonConfig &buttonConfig) :
        buttonConfig(buttonConfig)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        setText(buttonConfig.getCaption());
        updateVisibility();
    }

    void updateVisibility()
    {
        if (buttonConfig.getShellCommandToDetermineVisibility() != "")
        {
            setVisible(ButtonConfig::runShellAndReturnExitStatusSuccess(buttonConfig.getShellCommandToDetermineVisibility()));
        }
    }

public slots:
    void buttonClicked()
    {
        if (buttonConfig.isSpecialCommand("close"))
        {
            window()->close();
        }
        else if (buttonConfig.isSpecialCommand("quit"))
        {
            QApplication::quit();
        }
        else
        {
            buttonConfig.runPrimaryShellCommand();
            QThread::msleep(50); // sleep 50 ms before updating button visibility
            updateVisibility();
        }
    }
};

#endif // MYBUTTON_H

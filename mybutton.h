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
            if (buttonConfig.shouldHideWindowOnClick())
            {
                window()->close();
            }
            else
            {
                QThread::msleep(20);
                // There is another slot registered for buttons, which updates the button visibility.
                // Give them a little time.
            }
        }
    }
};

#endif // MYBUTTON_H

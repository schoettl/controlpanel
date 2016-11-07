#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QApplication>

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
        setText(buttonConfig.caption);
        updateVisibility();
    }

    void updateVisibility()
    {
        if (buttonConfig.command2 != "")
        {
            setVisible(ButtonConfig::runShellAndReturnExitStatusSuccess(buttonConfig.command2));
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
        else if (buttonConfig.command1 != "")
        {
            ButtonConfig::runShellAndReturnExitStatusSuccess(buttonConfig.command1);
        }
    }
};

#endif // MYBUTTON_H

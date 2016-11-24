#ifndef BUTTONCONFIG_H
#define BUTTONCONFIG_H

#include <QString>
#include <string>
#include <cstdlib>

using namespace std;

class ButtonConfig
{
private:
    QString caption;
    QString primaryShellCommand;
    QString shellCommandToDetermineVisibility;
    bool hideWindowOnClick;
public:
    ButtonConfig(const QString& caption, const QString& primaryShellCommand, const QString& shellCommandToDetermineVisibility, bool hideWindowOnClick) :
        caption(caption),
        primaryShellCommand(primaryShellCommand),
        shellCommandToDetermineVisibility(shellCommandToDetermineVisibility),
        hideWindowOnClick(hideWindowOnClick)
    {
    }

    // Run a shell command an return true if the exit status is 0.
    // The command should not be started in background, i.e. no trailing "&".
    static bool runShellAndReturnExitStatusSuccess(const QString& command)
    {
        string commandstr = command.toUtf8().constData();
        int ret = system(commandstr.c_str());
        return WIFEXITED(ret) && WEXITSTATUS(ret) == 0;
    }

    bool isSpecialCommand(const QString& command) const
    {
        return primaryShellCommand == ':' + command;
    }

    const QString& getShellCommandToDetermineVisibility() const
    {
        return shellCommandToDetermineVisibility;
    }

    const QString& getCaption() const
    {
        return caption;
    }

    bool shouldHideWindowOnClick() const
    {
        return hideWindowOnClick;
    }

    void runPrimaryShellCommand() const
    {
        if (primaryShellCommand != "")
            runShellAndReturnExitStatusSuccess(primaryShellCommand);
    }

};

#endif // BUTTONCONFIG_H

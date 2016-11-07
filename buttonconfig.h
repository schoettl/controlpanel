#ifndef BUTTONCONFIG_H
#define BUTTONCONFIG_H

#include <QString>
#include <string>
#include <cstdlib>

using namespace std;

class ButtonConfig
{
public:
    QString caption;
    QString command1;
    QString command2;
public:
    ButtonConfig(const QString& caption, const QString& command1, const QString& command2) :
        caption(caption),
        command1(command1),
        command2(command2)
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
        return command1 == ':' + command;
    }

};

#endif // BUTTONCONFIG_H

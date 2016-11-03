#ifndef BUTTONCONFIG_H
#define BUTTONCONFIG_H

#include <QString>

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
};

#endif // BUTTONCONFIG_H

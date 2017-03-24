#include "maindialog.h"
#include "buttonconfig.h"
#include <QApplication>
#include <QStandardPaths>
#include <QList>
#include <QFile>
#include <QDir>
#include <QtGlobal>
#include <QDebug>
#include <QRegExp>

#define APP_NAME_LOWER_CASE "controlpanel"

void exitWithError(const QString &message)
{
    // qInfo() << message; // not available in Qt 5.2
    qWarning() << message;
    QApplication::exit(1); // does not work: app remain open
    // maybe because it does not quit when the main window is closed
}

struct CommandLineArgs
{
    bool launchInBackground = false; // quiet
};

void parseCommandLineArgs(int argc, char *argv[], CommandLineArgs &args)
{
    if (argc == 2)
    {
        QString option = argv[1];
        if (option == "-q")
            args.launchInBackground = true;
        else
            exitWithError("Invalid command line option.");
    }
    else if (argc > 1)
    {
        exitWithError("Invalid command line options.");
    }
}

void readTextFile(const QString &filename, QStringList &lines)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textStream(&file);
    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            lines.append(line);
    }
}

void readButtonConfig(const QString &filename, QList<ButtonConfig> &list)
{
    QStringList lines;
    readTextFile(filename, lines);

    foreach(QString line, lines)
    {
        //qDebug() << line;
        QRegExp ignoreLineRegex("#.*|\\s*");
        if (ignoreLineRegex.exactMatch(line))
            continue;
        QStringList parts = line.split("\t");
        QString s1 = parts[0];
        QString s2 = parts.size() > 1 ? parts[1] : NULL;
        QString s3 = parts.size() > 2 ? parts[2] : NULL;
        QString s4 = parts.size() > 3 ? parts[3] : NULL;
        bool hide = s4 != "0";
        ButtonConfig *bc = new ButtonConfig(s1, s2, s3, hide);
        list.append(*bc);
    }

}

QString getConfigFilename(const QString &basename)
{
    //QString s = QStandardPaths::locate(QStandardPaths::ConfigLocation, APP_NAME_LOWER_CASE, QStandardPaths::LocateDirectory);
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    qDebug() << configDir;

    QString configDir2 = configDir + "/" + APP_NAME_LOWER_CASE;
    QDir dir(configDir2);
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    return configDir2 + "/" + basename;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CommandLineArgs args;
    parseCommandLineArgs(argc, argv, args);

    QList<ButtonConfig> list;
    readButtonConfig(getConfigFilename("buttons.conf"), list);

    QStringList stylesheetLines;
    readTextFile(getConfigFilename("stylesheet.css"), stylesheetLines);
    QString stylesheet = stylesheetLines.join("");
    a.setStyleSheet(stylesheet);

    MainDialog d(list);
    if (!args.launchInBackground)
        d.show();

    return a.exec();
}

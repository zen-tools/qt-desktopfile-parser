#include <QCoreApplication>
#include <QDebug>
#include <QLocale>

#include "desktopfile.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DesktopFile file("/usr/share/applications/medit.desktop");
    qDebug() << file.value(Q_KEY_FILE_DESKTOP_KEY_NAME);

    return 0;
}

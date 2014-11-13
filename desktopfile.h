#ifndef DESKTOPFILE_H
#define DESKTOPFILE_H

#include <QLocale>
#include <QRegExp>
#include <QString>
#include <QSettings>
#include <QStringList>
#include <QMap>
#include <QDebug>

#include "config.h"

class DesktopFile : public QObject
{
    Q_OBJECT
    QMap <QString, QString> data;
    QStringList key_list;
public:
    explicit DesktopFile(QString file);
    QString value(QString key);
private:

signals:

public slots:

};

#endif // DESKTOPFILE_H

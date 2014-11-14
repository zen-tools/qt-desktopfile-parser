#ifndef DESKTOPFILE_H
#define DESKTOPFILE_H

#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QMap>
#include <QDebug>
#include <QRegExp>
#include <QStringList>

#include "config.h"

class DesktopFile : public QObject {
    #define Q_GROUP_DELIMETR "/"
    Q_OBJECT
    QMap <QString, QString> values;
    QString currentGroup;
public:
    explicit DesktopFile( QString file, QObject *parent = 0 );

    QString value( QString key, QString default_value );

    QString value( QString key, QStringList preferedLocales, QString defaultValue );

    inline void beginGroup( QString group ) {
        this->currentGroup = group;
    }

    inline void endGroup() {
        this->currentGroup = "";
    }

    inline QString group() {
        return this->currentGroup;
    }
signals:
    
public slots:
    
};

#endif // DESKTOPFILE_H

#include <QCoreApplication>
#include <QDebug>
#include <QLocale>
#include <QStringList>
#include <QDirIterator>
#include <QFileInfo>
#include <QPointer>
#include <QQueue>
#include <QList>
#include <QLocale>
#include <QTextStream>

#include "desktopfile.h"
#include "config.h"

int main( int argc, char *argv[] ) {
    QCoreApplication a( argc, argv );

    QStringList locales;
    locales << QLocale().name() << QLocale().name().remove( QRegExp( "_.*" ) );

    QQueue < QPointer<DesktopFile> > applications;

    QDir dir( "/usr/share/applications/" );
    QFileInfoList file_list = dir.entryInfoList( QStringList( Q_DESKTOP_FILE_EXTENSION ), QDir::Files | QDir::Readable );

    foreach( QFileInfo file, file_list )
        applications.enqueue( new DesktopFile( file.absoluteFilePath() ) );

    while( !applications.isEmpty() ) {
        QTextStream( stdout ) << "In queue: " << applications.count() << endl;
        DesktopFile *tmp = applications.dequeue();
        tmp->beginGroup( Q_KEY_FILE_DESKTOP_GROUP );
        QTextStream( stdout ) << "Name: " << tmp->value( Q_KEY_FILE_DESKTOP_KEY_NAME, locales, QString( "" ) ) << endl;
        QTextStream( stdout ) << "Exec: " << tmp->value( Q_KEY_FILE_DESKTOP_KEY_EXEC, QString( "" ) ) << endl;
        QTextStream( stdout ) << "Icon: " << tmp->value( Q_KEY_FILE_DESKTOP_KEY_ICON, QString( "" ) ) << endl;
        QTextStream( stdout ) << "Categories: " << tmp->value( Q_KEY_FILE_DESKTOP_KEY_CATEGORIES, QString( "" ) ) << endl << endl;
        tmp->endGroup();
        delete tmp;
    }

    return 0;
}

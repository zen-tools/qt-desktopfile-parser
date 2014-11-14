#include "desktopfile.h"

DesktopFile::DesktopFile( QString file, QObject *parent ) :
    QObject( parent )
{
    QFile rfile( file, parent );
    if( rfile.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        QTextStream in( &rfile );
        QString groupName = "";

        QRegExp entry_rx( "^\\[(.*)\\]$" );
        QRegExp data_rx( "^([a-zA-Z]*(\\[\\S*\\])?)=(.*)" );
        QRegExp skip_rx( "^$|^#.*" );

        while( !in.atEnd() ) {
            QString line = in.readLine().trimmed();
            if( line.contains( entry_rx ) ) {
                entry_rx.indexIn( line );
                groupName = entry_rx.cap( 1 );
                #ifdef QT_DEBUG
                qDebug() << "[GROUP]" << groupName;
                #endif
                continue;
            }
            else if( !groupName.isEmpty() && line.contains( data_rx ) )
            {
                data_rx.indexIn( line );
                values.insert( groupName + Q_GROUP_DELIMETR + data_rx.cap( 1 ), data_rx.cap( 3 ) );
                #ifdef QT_DEBUG
                qDebug() << "[DATA] " << data_rx.cap( 1 ) << values.value( groupName + Q_GROUP_DELIMETR + data_rx.cap( 1 ) );
                #endif
            }
            else if( line.contains( skip_rx ) ) {
                // Skip empty line or comment
                continue;
            }
        }
    }
    else {
        qWarning() << "[WARN] " << "Cannot read file: " + file;
    }
}

QString DesktopFile::value( QString key, QString defaultValue ) {
    return values.value( this->currentGroup + Q_GROUP_DELIMETR + key, defaultValue );
}

QString DesktopFile::value( QString key, QStringList preferedLocales, QString defaultValue ) {
    foreach( QString locale, preferedLocales ) {
        QString value = values.value( this->currentGroup + Q_GROUP_DELIMETR + key + "[" + locale + "]" );
        if( value.isEmpty() )
            continue;
        return value;
    }

    // I we have no one value by key + locale -> try to take from 'C' locale
    return this->value( key, defaultValue );
}

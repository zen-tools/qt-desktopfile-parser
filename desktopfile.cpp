#include "desktopfile.h"

DesktopFile::DesktopFile(QString file)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    // Build a list of keys that we need to read from file
    key_list << Q_KEY_FILE_DESKTOP_KEY_NAME
             << Q_KEY_FILE_DESKTOP_KEY_GENERIC_NAME
             << Q_KEY_FILE_DESKTOP_KEY_CATEGORIES
             << Q_KEY_FILE_DESKTOP_KEY_COMMENT
             << Q_KEY_FILE_DESKTOP_KEY_ICON
             << Q_KEY_FILE_DESKTOP_KEY_EXEC
             << Q_KEY_FILE_DESKTOP_KEY_TERMINAL;

    settings.beginGroup(Q_KEY_FILE_DESKTOP_GROUP);

    foreach (QString key, key_list)
    {
        key = settings.contains(key + "[" + QLocale().name() + "]")
            ? key + "[" + QLocale().name() + "]"
            : settings.contains(key + "[" + QLocale().name().remove(QRegExp("_.*")) + "]")
              ? key + "[" + QLocale().name().remove(QRegExp("_.*")) + "]"
              : key;

        QString value = settings.value(key, "").toString();

        if(!value.isEmpty())
            data.insert(key, value);

        #ifdef QT_DEBUG
            qWarning() << "[WARNING]"
                + tr(" Cannot find data by key: '")
                + key
                + tr("' in file: ")
                + file;
        #endif
    }

    /*if (settings.) {
        qWarning() << tr("Cannot find group: ")
                   << Q_KEY_FILE_DESKTOP_GROUP
                   << tr(" in file:")
                   << this->file;
        return;
    }*/

    settings.endGroup();
}

QString DesktopFile::value(QString key)
{
    return data.value(key, "");
}

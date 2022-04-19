#include <QFile>
#include "common.h"

/**
 * @brief readFile
 * @param path: The path to file
 * @param data: Buffer to store data
 * @return true if it is successed, false if it encountered an error
 */
bool readFile(QString &path, QByteArray* data)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        *data = file.readAll();
        file.close();
        return true;
    }
    else
    {
        // TODO handle error
        return false;
    }
}

QString fileUrlToPath(QString &fileUrl)
{
    if (fileUrl.startsWith("file://"))
    {
        return fileUrl.right(fileUrl.size() - 7);
    } else {
        return fileUrl;
    }
}

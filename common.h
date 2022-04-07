#ifndef COMMON_H
#define COMMON_H

#include <QString>


bool readFile(QString &path, QByteArray &data);

QString fileUrlToPath(QString &fileUrl);
#endif // COMMON_H

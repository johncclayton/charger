#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include <QByteArray>
#include <QVariantMap>

QByteArray variantMapToJson(QVariantMap data);
QVariantMap jsonToVariantMap(QByteArray data);

#endif // JSON_HELPER_H

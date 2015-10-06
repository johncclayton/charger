#include "json_helper.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#define HAS_QT_JSON
#else
#include <serializer.h>
#include <parser.h>
#endif

#ifdef HAS_QT_JSON
#include <QJsonDocument>
#include <QJsonObject>
#endif

QByteArray variantMapToJson(QVariantMap data) {
#ifdef HAS_QT_JSON
    QJsonDocument d = QJsonDocument::fromVariant(data);
    return d.toJson(QJsonDocument::Compact);
#else
    QJson::Serializer serializer;
    return serializer.serialize(data);
#endif    
}

QVariantMap jsonToVariantMap(QByteArray data) {
#ifdef HAS_QT_JSON
    QJsonDocument d = QJsonDocument::fromJson(data);
    return d.object().toVariantMap();
#else
    QJson::Parser parser;
    return parser.parse(data).toMap();
#endif    
}

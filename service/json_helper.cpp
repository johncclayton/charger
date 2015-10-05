
#include "json_helper.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#define HAS_QT_JSON
#else
#include <serializer.h>
#endif

#ifdef HAS_QT_JSON
#include <QJsonDocument>
#include <QJsonObject>
#endif

QByteArray makeJsonByteArray(QVariantMap data) {
#ifdef HAS_QT_JSON
    QJsonDocument d = QJsonDocument::fromVariant(data);
    return d.toJson();
#else
    QJson::Serializer serializer;
    return serializer.serialize(data);
#endif    
}



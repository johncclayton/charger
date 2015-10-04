#pragma once

#include <QString>
#include <QMetaType>

class BonjourRecord
{
public:
    BonjourRecord()
    {
    }
    BonjourRecord( const QString&name, const QString& regType, const QString& domain = QString() )
        : serviceName( name ), 
          registeredType( regType ), 
          replyDomain( domain )
    {
    }
    
    QString serviceName;
    QString registeredType;
    QString replyDomain;
};

static inline bool operator==( const BonjourRecord& lhs, const BonjourRecord& rhs )
{
    return lhs.serviceName == rhs.serviceName &&
           lhs.registeredType == rhs.registeredType &&
           lhs.replyDomain == rhs.replyDomain;
}

static inline bool operator!=( const BonjourRecord& lhs, const BonjourRecord& rhs ) { return !operator==( lhs, rhs ); }

Q_DECLARE_METATYPE(BonjourRecord)

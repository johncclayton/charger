#ifndef FORMAT_H
#define FORMAT_H

#include <QObject>

class Format : public QObject
{
    Q_OBJECT
public:
    explicit Format(QObject *parent = 0);
    
    Q_INVOKABLE QString valueStr(double val, int dp = 2) { return QString::number(val, 'f', dp); }
};

#endif // FORMAT_H

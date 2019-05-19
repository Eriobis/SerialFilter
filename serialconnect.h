#ifndef SERIALCONNECT_H
#define SERIALCONNECT_H

#include <QObject>

class SerialConnect : public QObject
{
    Q_OBJECT
public:
    explicit SerialConnect(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SERIALCONNECT_H
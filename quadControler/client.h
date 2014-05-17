#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QtCore>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

public slots:
    void connectToHost(QString host);
    void writeData(QByteArray data);

private slots:
    QByteArray IntToArray(qint32 source);

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H

#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QTcpSocket>

class Server;

class clientConnection : public QTcpSocket
{
    Q_OBJECT

public:
    clientConnection(qintptr socketDescriptor, QObject* parent = nullptr);

    Server* server();

signals:
    void disconnectedFromServer(clientConnection* client);

private slots:
    void onReadyRead();
    void onDisconnected();

private:

    QString username;
};

#endif // CLIENTCONNECTION_H

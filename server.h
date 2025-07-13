#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QSet>
#include <QMap>

class clientConnection;

class Server: public QTcpServer
{
    Q_OBJECT

    friend class clientConnection;

public:
    Server(QObject *parent = nullptr);
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onClientDisconnected(clientConnection* client);

private:
    QSet<clientConnection*> clients;
    QMap<QString, QString> registeredUsers;
    QSet<QString> openRooms;




};

#endif // SERVER_H

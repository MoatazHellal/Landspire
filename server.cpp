#include "Server.h"
#include "ClientConnection.h"
#include <QDebug>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    if (!listen(QHostAddress::Any, 4242)) {
        qCritical() << "Unable to start server!";
        exit(EXIT_FAILURE);
    }
    qDebug() << "Server started on port" << serverPort();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    auto client = new clientConnection(socketDescriptor, this);
    clients.insert(client);

    connect(client, &clientConnection::disconnectedFromServer,
            this, &Server::onClientDisconnected);
}

void Server::onClientDisconnected(clientConnection* client)
{
    clients.remove(client);
    client->deleteLater();
}

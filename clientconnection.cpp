#include "clientConnection.h"
#include "Server.h"
#include <QDebug>

clientConnection::clientConnection(qintptr socketDescriptor, QObject* parent)
    : QTcpSocket(parent)
{
    setSocketDescriptor(socketDescriptor);

    connect(this, &QTcpSocket::readyRead, this, &clientConnection::onReadyRead);
    connect(this, &QTcpSocket::disconnected, this, &clientConnection::onDisconnected);
}

void clientConnection::onReadyRead()
{
    while (canReadLine()) {
        QString line = readLine().trimmed();
        QStringList parts = line.split(":");
        QString command = parts.value(0).toUpper();

        if (command == "REGISTER" && parts.size() == 3) {
            QString user = parts[1], pass = parts[2];
            if (server()->registeredUsers.contains(user)) {
                write("REGISTER_FAIL\n");
            } else {
                server()->registeredUsers[user] = pass;
                write("REGISTER_OK\n");
            }
        }
        else if (command == "LOGIN" && parts.size() == 3) {
            QString user = parts[1], pass = parts[2];
            if (server()->registeredUsers.value(user) == pass) {
                username = user;
                write("LOGIN_OK\n");
            } else {
                write("LOGIN_FAIL\n");
            }
        }
        else if (command == "CREATEROOM" && parts.size() == 2) {
            QString roomName = parts[1];
            if (server()->openRooms.contains(roomName)) {
                write("ROOM_EXISTS\n");
            } else {
                server()->openRooms.insert(roomName);
                write(QString("ROOM_CREATED:%1\n").arg(roomName).toUtf8());
            }
        }
        else if (command == "JOINROOM" && parts.size() == 2) {
            QString roomName = parts[1];
            if (server()->openRooms.contains(roomName)) {
                write(QString("ROOM_JOINED:%1\n").arg(roomName).toUtf8());
            } else {
                write("ROOM_NOT_FOUND\n");
            }
        }
        else {
            write("UNKNOWN_COMMAND\n");
        }
    }
}

void clientConnection::onDisconnected()
{
    emit disconnectedFromServer(this);
}

Server* clientConnection::server() {
    return qobject_cast<Server*>(parent());
}

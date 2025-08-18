#ifndef FIREBASEAPI_H
#define FIREBASEAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>

class FirebaseAPI : public QObject
{
    Q_OBJECT

public:
    explicit FirebaseAPI(QObject *parent = nullptr);
    QNetworkAccessManager* getNetworkManager();
    QString getDatabaseUrl();
    void setDatabaseUrl(const QString& url);
    QString getHostedRoomKey();
    QJsonObject getHostedRoom();
    void setHostedRoom(QJsonObject room);

    void registerUser(const QString& username, const QString& password);
    void loginUser(const QString& username, const QString& password);
    void createRoom(const QString &username);
    void joinRoom(const QString &roomName, const QString &username);

signals:
    void loginSuccess();
    void loginFailed(const QString& reason);
    void registerSuccess();
    void registerFailed(const QString& reason);

private slots:
    void onRegisterReply(QNetworkReply* reply);
    void onLoginReply(QNetworkReply* reply, const QString& password);

private:
    QNetworkAccessManager* networkManager;
    QString databaseUrl;

    QString hostedRoomKey;
    QJsonObject hostedRoom;
};

#endif // FIREBASEAPI_H

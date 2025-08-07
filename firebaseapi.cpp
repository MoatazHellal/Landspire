#include "firebaseapi.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

FirebaseAPI::FirebaseAPI(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

void FirebaseAPI::setDatabaseUrl(const QString& url)
{
    databaseUrl = url;
}

void FirebaseAPI::registerUser(const QString& username, const QString& password)
{
    QUrl url(databaseUrl + "/users/" + username + ".json");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject userData;
    userData["username"] = username;
    userData["password"] = password;

    QNetworkReply* reply = networkManager->put(request, QJsonDocument(userData).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { onRegisterReply(reply); });
}

void FirebaseAPI::loginUser(const QString& username, const QString& password)
{
    QUrl url(databaseUrl + "/users/" + username + ".json");
    QNetworkRequest request(url);

    QNetworkReply* reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, password]() {
        onLoginReply(reply, password);
    });
}

void FirebaseAPI::onRegisterReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        emit registerSuccess();
    } else {
        emit registerFailed(reply->errorString());
    }
    reply->deleteLater();
}

void FirebaseAPI::onLoginReply(QNetworkReply* reply,const QString& password)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit loginFailed("Network error");
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if (!jsonDoc.isObject()) {
        emit loginFailed("Invalid response");
        reply->deleteLater();
        return;
    }

    QJsonObject obj = jsonDoc.object();
    if (obj["password"].toString() == password) {
        emit loginSuccess();
    } else {
        emit loginFailed("Wrong password");
    }

    reply->deleteLater();
}

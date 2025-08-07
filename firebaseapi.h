#ifndef FIREBASEAPI_H
#define FIREBASEAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class FirebaseAPI : public QObject
{
    Q_OBJECT

public:
    explicit FirebaseAPI(QObject *parent = nullptr);
    void setDatabaseUrl(const QString& url);

    void registerUser(const QString& username, const QString& password);
    void loginUser(const QString& username, const QString& password);

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
};

#endif // FIREBASEAPI_H

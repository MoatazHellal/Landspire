#ifndef CONNECTDIALOGUE_H
#define CONNECTDIALOGUE_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class connectDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit connectDialogue(QWidget *parent = nullptr);

signals:
    void loginRequested(const QString& username, const QString& password);
    void registerRequested(const QString& username, const QString& password);

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    void handleLogin(const QString& username, const QString& password, QDialog* dialog);

    // Login widgets
    QLineEdit* loginUsernameEdit;
    QLineEdit* loginPasswordEdit;
    QPushButton* loginButton;

    // Register widgets
    QLineEdit* registerUsernameEdit;
    QLineEdit* registerPasswordEdit;
    QPushButton* registerButton;
};

#endif // CONNECTDIALOGUE_H

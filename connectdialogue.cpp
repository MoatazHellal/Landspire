#include "connectdialogue.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

connectDialogue::connectDialogue(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Connect to Server");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    // --- Login Section ---
    QLabel* loginLabel = new QLabel("<b>Login</b>");
    mainLayout->addWidget(loginLabel);

    QFormLayout* loginForm = new QFormLayout();
    loginUsernameEdit = new QLineEdit();
    loginPasswordEdit = new QLineEdit();
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginForm->addRow("Username:", loginUsernameEdit);
    loginForm->addRow("Password:", loginPasswordEdit);
    mainLayout->addLayout(loginForm);

    loginButton = new QPushButton("Login");
    mainLayout->addWidget(loginButton);
    connect(loginButton, &QPushButton::clicked, this, &connectDialogue::onLoginClicked);

    // --- Register Section ---
    QLabel* registerLabel = new QLabel("<b>Register</b>");
    mainLayout->addWidget(registerLabel);

    QFormLayout* registerForm = new QFormLayout();
    registerUsernameEdit = new QLineEdit();
    registerPasswordEdit = new QLineEdit();
    registerPasswordEdit->setEchoMode(QLineEdit::Password);
    registerForm->addRow("Username:", registerUsernameEdit);
    registerForm->addRow("Password:", registerPasswordEdit);
    mainLayout->addLayout(registerForm);

    registerButton = new QPushButton("Register");
    mainLayout->addWidget(registerButton);
    connect(registerButton, &QPushButton::clicked, this, &connectDialogue::onRegisterClicked);

    setLayout(mainLayout);
}

void connectDialogue::onLoginClicked()
{
    emit loginRequested(loginUsernameEdit->text(), loginPasswordEdit->text());
}

void connectDialogue::onRegisterClicked()
{
    emit registerRequested(registerUsernameEdit->text(), registerPasswordEdit->text());
}

void handleLogin(const QString& username, const QString& password, QDialog* dialog)
{

}

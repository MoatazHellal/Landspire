#include "inputdialog.h"
#include <QVBoxLayout>

InputDialog::InputDialog(const QString& labelText, QWidget* parent) : QDialog(parent) {
    setWindowTitle("Input");

    QLabel* label = new QLabel(labelText);
    lineEdit = new QLineEdit;

    QPushButton* okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, this, &InputDialog::accept);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(okButton);

    setLayout(layout);
}

QString InputDialog::getInputText() const {
    return lineEdit->text();
}

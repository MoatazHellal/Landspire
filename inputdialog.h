#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class InputDialog : public QDialog {
    Q_OBJECT
public:
    explicit InputDialog(const QString& labelText, QWidget* parent = nullptr);

    QString getInputText() const;

private:
    QLineEdit* lineEdit;
};

#endif // INPUTDIALOG_H

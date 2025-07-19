#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QFrame>
#include <QString>
#include <QPixmap>
#include "cardAffinities.h"

class QLabel;

class cardWidget : public QFrame
{
    Q_OBJECT

public:
    explicit cardWidget(const QString& name, const Affinity affinity, const QString& description, const QPixmap& pixmap, QWidget* parent = nullptr);
    QString name() const;
    QString description() const;
    Affinity affinity() const;
    QLabel* imageLabel() const;

    void resize(const float width, const float height);

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void hovered(cardWidget* card);
    void clicked(cardWidget* card);
    void rightClicked(cardWidget* card);

private:
    QString m_name;
    QString m_description;
    Affinity m_affinity;
    QLabel* m_imageLabel;
};

#endif // CARDWIDGET_H

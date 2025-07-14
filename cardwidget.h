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
    explicit cardWidget(const QString& name, const Affinity affinity, const QPixmap& pixmap, QWidget* parent = nullptr);
    QString name() const;
    Affinity affinity() const;
    QLabel* imageLabel() const;

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void hovered(cardWidget* card);
    void clicked(cardWidget* card);

private:
    QString m_name;
    Affinity m_affinity;
    QLabel* m_imageLabel;
};

#endif // CARDWIDGET_H

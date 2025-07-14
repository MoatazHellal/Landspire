#include "cardwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "cardAffinities.h"

cardWidget::cardWidget(const QString& name, const Affinity affinity, const QPixmap& pixmap, QWidget* parent) : QFrame(parent), m_name(name), m_affinity(affinity)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    setLineWidth(2);
    setFixedSize(100, 140); // Size of the card

    m_imageLabel = new QLabel(this);
    m_imageLabel->setPixmap(pixmap.scaled(100, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_imageLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_imageLabel);
    setLayout(layout);

}

QString cardWidget::name() const
{
    return m_name;
}

Affinity cardWidget::affinity() const
{
    return m_affinity;
}

QLabel* cardWidget::imageLabel() const
{
    return m_imageLabel;
}
void cardWidget::enterEvent(QEnterEvent* event)
{
    emit hovered(this);
    QFrame::enterEvent(event);
}

void cardWidget::leaveEvent(QEvent* event)
{
    QFrame::leaveEvent(event);
}

void cardWidget::mousePressEvent(QMouseEvent* event)
{
    emit clicked(this);
    QFrame::mousePressEvent(event);
}






#include "cardwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include "cardAffinities.h"

cardWidget::cardWidget(const QString& name, const Affinity affinity, const QString& description, const QPixmap& pixmap, QWidget* parent) : QFrame(parent), m_name(name), m_description(description), m_affinity(affinity)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    setLineWidth(2);
    setFixedSize(100, 140);

    m_imageLabel = new QLabel(this);
    m_imageLabel->setPixmap(pixmap.scaled(100, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setScaledContents(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_imageLabel);


    setLayout(layout);

}

void cardWidget::resize(const float width, const float height)
{
    setFixedSize(width, height);
    m_imageLabel->setPixmap(m_imageLabel->pixmap().scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QString cardWidget::name() const
{
    return m_name;
}

QString cardWidget::description() const
{
    return m_description;
}

Affinity cardWidget::affinity() const
{
    return m_affinity;
}

QLabel* cardWidget::imageLabel() const
{
    return m_imageLabel;
}

cardWidget* cardWidget::original() const
{
    return m_original;
}

void cardWidget::setOriginal(cardWidget* card)
{
    m_original = card;
}

cardWidget* cardWidget::clone(QWidget* newParent)
{
    cardWidget* copy = new cardWidget(m_name, m_affinity, m_description, m_imageLabel->pixmap(), newParent);
    copy->setOriginal(this);
    return copy;
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

    if (event->button() == Qt::LeftButton) {
        QDrag* drag = new QDrag(this);
        QMimeData* mime = new QMimeData;

        mime->setData("application/x-card", QByteArray::number(reinterpret_cast<quintptr>(this)));

        drag->setMimeData(mime);

        Qt::DropAction action = (m_dragContext == DragContext::DeckEditor) ? Qt::CopyAction : Qt::MoveAction;

        drag->exec(action);
    }
    else if (event->button() == Qt::RightButton)
    {
        emit rightClicked(this);
    }
    QFrame::mousePressEvent(event);
}






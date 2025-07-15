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
        auto mimeData = new QMimeData();
        mimeData->setText(m_name);

        auto drag = new QDrag(this);
        drag->setMimeData(mimeData);

        drag->exec(Qt::CopyAction);
    }
    else if (event->button() == Qt::RightButton)
    {
        emit rightClicked(this);
    }
    QFrame::mousePressEvent(event);
}






#include "CardCollectionViewer.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>

CardCollectionViewer::CardCollectionViewer(const QVector<cardWidget*>& cards, const QString& title, QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Viewing " + title);
    setMinimumSize(250, 200);
    buildUI(cards);
}

void CardCollectionViewer::buildUI(const QVector<cardWidget*>& cards) {
    QScrollArea* scroll = new QScrollArea(this);
    QWidget* container = new QWidget();
    QGridLayout* layout = new QGridLayout(container);

    const int maxCols = 5;
    int row = 0, col = 0;
    foreach (cardWidget* card, cards)
    {
        cardWidget* copy = card->clone(this);
        m_cardPreviews.append(copy);
        layout->addWidget(copy, row, col);
        if (++col >= maxCols)
        {
            col = 0;
            ++row;
        }
    }

    container->setLayout(layout);
    scroll->setWidget(container);
    scroll->setWidgetResizable(true);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scroll);
    setLayout(mainLayout);
}

QVector<cardWidget*> CardCollectionViewer::cardPreviews()
{
    return m_cardPreviews;
}

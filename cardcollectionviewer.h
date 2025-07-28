#ifndef CARDCOLLECTIONVIEWER_H
#define CARDCOLLECTIONVIEWER_H

#include "cardwidget.h"
#include <QDialog>

class CardCollectionViewer : public QDialog {
    Q_OBJECT

public:
    CardCollectionViewer(const QVector<cardWidget*>& cards, const QString& title, QWidget* parent = nullptr);
    QVector<cardWidget*> cardPreviews();

private:
    void buildUI(const QVector<cardWidget*>& cards);

    QVector<cardWidget*> m_cardPreviews;
};

#endif // CARDCOLLECTIONVIEWER_H

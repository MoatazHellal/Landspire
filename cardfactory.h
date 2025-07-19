#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include <QString>
#include <QVector>
#include <QMap>
#include "cardwidget.h"

class CardFactory
{
public:
    static void loadCards(const QString& jsonPath);
    static cardWidget* createCard(const QString& name);

private:
    struct CardData {
        QString name;
        QString description;
        Affinity affinity;
        QString imagePath;
    };

    static QMap<QString, CardData> s_cardData;
};

#endif // CARDFACTORY_H

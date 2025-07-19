#include "cardfactory.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

QMap<QString, CardFactory::CardData> CardFactory::s_cardData;

void CardFactory::loadCards(const QString& jsonPath) {
    QFile file(jsonPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open card JSON file!");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray array = doc.array();

    for (const QJsonValue& value : array) {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        QString description = obj["description"].toString();
        QString image = obj["image"].toString();
        QString affinityStr = obj["affinity"].toString();

        Affinity affinity;
        if (affinityStr == "incantation") affinity = Affinity::incantation;
        else if (affinityStr == "fire") affinity = Affinity::Fire;
        // ... add all enum conversions

        s_cardData[name] = {name, description, affinity, image};
    }
}

cardWidget* CardFactory::createCard(const QString& name) {
    if (!s_cardData.contains(name)) return nullptr;

    const CardData& data = s_cardData[name];
    QPixmap pixmap(data.imagePath);
    return new cardWidget(data.name, data.affinity, data.description, pixmap);
}

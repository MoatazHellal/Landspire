#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectdialogue.h"
#include "cardwidget.h"
#include "cardfactory.h"


#include <qevent.h>
#include <QMimeData>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    this->setWindowTitle(defaultWindowTitle);

    createActions();
    createMenus();

    firebase = new FirebaseAPI(this);
    firebase->setDatabaseUrl("https://landspire-57cac-default-rtdb.europe-west1.firebasedatabase.app/");

    connect(ui->RefreshButton, &QPushButton::clicked, this, &MainWindow::fetchConnectedUsersOnce);
    connect(ui->CreateRoomBtn, &QPushButton::clicked, this, &MainWindow::createRoom);
    connect(ui->JoinRoomBtn, &QPushButton::clicked, this, [=]() {
    QModelIndex index = ui->RoomsList->currentIndex();
    if (!index.isValid()) {
        qDebug() << "No selection";
        return;
    }
    int row = index.row();
    QString selectedRoom = roomKeyMapping.value(row);
    joinRoom(selectedRoom);
    });

    ui->CardPreview->setPixmap(QPixmap(":/cards/card.png").scaled(200, 280, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    deckModel = new QStringListModel(this);
    ui->DeckList->setModel(deckModel);

    CardFactory::loadCards(":/data/cards.json");

    QVector<cardWidget*> cards = createCardWidgets();
    int maxCols = 4;
    int row = 0, col = 0;
    foreach (auto card, cards) {
        ui->CardsGrid->addWidget(card, row, col);
        if (++col >= maxCols)
        {
            col = 0;
            ++row;
        }

        connect(card, &cardWidget::hovered, this, &MainWindow::setCardPreview);
        connect(card, &cardWidget::rightClicked, this, &MainWindow::addCard);
    }

    ui->DeckList->setAcceptDrops(true);
    ui->DeckList->setDropIndicatorShown(true);
    ui->DeckList->setDragDropMode(QAbstractItemView::DropOnly);
    ui->DeckList->installEventFilter(this);

    connect(ui->ClearDeck, &QPushButton::clicked, this, &MainWindow::clearDeck);
    connect(ui->ExportDeck, &QPushButton::clicked, this, &MainWindow::onExportDeckClicked);
    connect(ui->ImportDeck, &QPushButton::clicked, this, &MainWindow::onImportDeckClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    connectAct = new QAction(tr("Connect"), this);
    connectAct->setShortcut(QKeySequence("Ctrl+L"));
    connect(connectAct, &QAction::triggered, this, &MainWindow::serverConnect);

    disconnectAct = new QAction(tr("Disconnect"), this);
    connect(disconnectAct, &QAction::triggered, this, &MainWindow::serverDisconnect);
    disconnectAct->setEnabled(false);

    fullscreenAct = new QAction(tr("Fullscreen"), this);
    fullscreenAct->setShortcut(QKeySequence::FullScreen);
    connect(fullscreenAct, &QAction::triggered, this, &MainWindow::fullscreen);

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &MainWindow::exit);

    aboutLandspireAct = new QAction(tr("About Landspire"), this);
    connect(aboutLandspireAct, &QAction::triggered, this, &MainWindow::about);

    gameRulesAct = new QAction(tr("Game rules"), this);
    connect(gameRulesAct, &QAction::triggered, this, &MainWindow::gameRules);
}

void MainWindow::createMenus()
{
    landspireMenu = new QMenu(tr("Landspire"), this);
    landspireMenu->addAction(connectAct);
    landspireMenu->addAction(disconnectAct);
    landspireMenu->addSeparator();
    landspireMenu->addAction(fullscreenAct);
    landspireMenu->addSeparator();
    landspireMenu->addAction(exitAct);

    helpMenu = new QMenu(tr("Help"), this);
    helpMenu->addAction(aboutLandspireAct);
    helpMenu->addAction(gameRulesAct);*

    menuBar()->addMenu(landspireMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::serverConnect()
{
    connectDialogue* Dialog = new connectDialogue(this);

    // Disconnect any previous login/register signal handlers to prevent stacking
    disconnect(firebase, &FirebaseAPI::loginSuccess, this, nullptr);
    disconnect(firebase, &FirebaseAPI::loginFailed, this, nullptr);
    disconnect(firebase, &FirebaseAPI::registerSuccess, this, nullptr);
    disconnect(firebase, &FirebaseAPI::registerFailed, this, nullptr);

    connect(Dialog, &connectDialogue::loginRequested, this, [this, Dialog](const QString& user, const QString& pass){
        connect(firebase, &FirebaseAPI::loginSuccess, this, [this, Dialog, user]() {
            qDebug() << "Login success!";

            connectAct->setEnabled(false);
            disconnectAct->setEnabled(true);
            this->setWindowTitle(defaultWindowTitle + " @" + user);
            ui->StatusLabel->setText("You are connected as " + user);

            currentUsername = user;

            // Add user to Firebase
            QJsonObject userData;
            userData["username"] = user;
            QJsonDocument doc(userData);
            QNetworkRequest request(QUrl(firebase->getDatabaseUrl() + "/connectedUsers/" + user + ".json"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            firebase->getNetworkManager()->put(request, doc.toJson());

            // Start listening after the user has been added
            startListeningForConnectedUsers();
            startListeningForRooms();

            Dialog->accept();
        });
        connect(firebase, &FirebaseAPI::loginFailed, this, [Dialog](const QString& reason) {
            qDebug() << "Login failed:" << reason;
        });
        firebase->loginUser(user, pass);
    });

    connect(Dialog, &connectDialogue::registerRequested, this, [this, Dialog](const QString& user, const QString& pass){
        connect(firebase, &FirebaseAPI::registerSuccess, this, [this, Dialog, user]() {
            qDebug() << "Register success!";

            connectAct->setEnabled(false);
            disconnectAct->setEnabled(true);
            this->setWindowTitle(defaultWindowTitle + " @" + user);
            ui->StatusLabel->setText("You are connected as " + user);

            currentUsername = user;

            QJsonObject userData;
            userData["username"] = user;
            QJsonDocument doc(userData);
            QNetworkRequest request(QUrl(firebase->getDatabaseUrl() + "/connectedUsers/" + user + ".json"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            firebase->getNetworkManager()->put(request, doc.toJson());

            startListeningForConnectedUsers();
            startListeningForRooms();

            Dialog->accept();
        });
        connect(firebase, &FirebaseAPI::registerFailed, this, [Dialog](const QString& reason) {
            qDebug() << "Register failed:" << reason;
        });
        firebase->registerUser(user, pass);
    });

    Dialog->exec();
}

void MainWindow::serverDisconnect()
{
    if (!currentUsername.isEmpty()) {
        // Remove user from Firebase
        QNetworkRequest request(QUrl(firebase->getDatabaseUrl() + "/connectedUsers/" + currentUsername + ".json"));
        firebase->getNetworkManager()->deleteResource(request);
    }

    // Stop listening and clean up stream
    if (connectedUsersReply) {
        connectedUsersReply->abort();
        connectedUsersReply->deleteLater();
        connectedUsersReply = nullptr;
    }

    currentUsername.clear();
    updateConnectedUsersList({});

    connectAct->setEnabled(true);
    disconnectAct->setEnabled(false);
    this->setWindowTitle(defaultWindowTitle);
    ui->StatusLabel->setText("You are not connected");
}

void MainWindow::startListeningForConnectedUsers()
{
    // Clean up previous listener if any
    if (connectedUsersReply) {
        connectedUsersReply->abort();
        connectedUsersReply->deleteLater();
        connectedUsersReply = nullptr;
    }

    QNetworkRequest request(QUrl(firebase->getDatabaseUrl() + "/connectedUsers.json"));
    request.setRawHeader("Accept", "text/event-stream");

    connectedUsersReply = firebase->getNetworkManager()->get(request);

    connect(connectedUsersReply, &QIODevice::readyRead, this, [this]() {
        while (connectedUsersReply->canReadLine()) {
            QByteArray line = connectedUsersReply->readLine();
            if (line.startsWith("data: ")) {
                QString jsonStr = line.mid(6).trimmed();
                if (!jsonStr.isEmpty() && jsonStr != "null") {
                    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
                    if (doc.isObject()) {
                        QStringList users;
                        QJsonObject obj = doc.object();
                        for (auto it = obj.begin(); it != obj.end(); ++it) {
                            QString username = it.value().toObject()["username"].toString();
                            users << username;
                        }
                        updateConnectedUsersList(users);
                    }
                }
            }
        }
    });
    connect(connectedUsersReply, &QNetworkReply::finished, this, [this]() {
        qDebug() << "ConnectedUsers stream finished. Restarting...";
        startListeningForConnectedUsers(); // auto-reconnect
    });
}

void MainWindow::updateConnectedUsersList(const QStringList &users)
{
    auto *model = new QStringListModel(users, this);
    ui->ConnectedUsersHome->setModel(model);
    ui->ConnectedUsersLobby->setModel(model);
}

void MainWindow::fetchConnectedUsersOnce()
{
    QNetworkRequest request(QUrl(firebase->getDatabaseUrl() + "/connectedUsers.json"));
    auto *reply = firebase->getNetworkManager()->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        QByteArray body = reply->readAll();
        reply->deleteLater();

        QStringList users;
        if (!body.isEmpty() && body != "null") {
            QJsonDocument doc = QJsonDocument::fromJson(body);
            if (doc.isObject()) {
                QJsonObject obj = doc.object();
                for (auto it = obj.begin(); it != obj.end(); ++it) {
                    users << it.value().toObject().value("username").toString(it.key());
                }
            }
        }
        updateConnectedUsersList(users);
    });
}

void MainWindow::startListeningForRooms()
{
    QNetworkRequest request(QUrl(firebase->getDatabaseUrl() + "/rooms.json"));
    request.setRawHeader("Accept", "text/event-stream");

    roomsReply = firebase->getNetworkManager()->get(request);

    connect(roomsReply, &QIODevice::readyRead, this, [this]() {
        static QMap<QString, QJsonObject> roomsCache; // keep local copy

        while (roomsReply->canReadLine()) {
            QByteArray line = roomsReply->readLine();
            if (line.startsWith("data: ")) {
                QString jsonStr = line.mid(6).trimmed();
                if (jsonStr.isEmpty() || jsonStr == "null")
                    continue;

                QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
                if (!doc.isObject())
                    continue;

                QJsonObject rootObj = doc.object();
                if (!rootObj.contains("data"))
                    continue;

                QString path = rootObj.value("path").toString();
                QJsonValue dataVal = rootObj.value("data");

                if (path == "/") {
                    // Full update
                    roomsCache.clear();
                    if (dataVal.isObject()) {
                        QJsonObject allRooms = dataVal.toObject();
                        for (auto it = allRooms.begin(); it != allRooms.end(); ++it) {
                            if (it.value().isObject())
                                roomsCache[it.key()] = it.value().toObject();

                            // 🔽 Extra check for hosted room on full update
                            if (it.key() == firebase->getHostedRoomKey()) {
                                firebase->setHostedRoom(it.value().toObject());
                            }
                        }
                    }
                } else {
                    // Patch update
                    QString roomName = path.mid(1); // remove leading "/"
                    if (dataVal.isNull()) {
                        roomsCache.remove(roomName);
                    } else if (dataVal.isObject()) {
                        roomsCache[roomName] = dataVal.toObject();

                        // 🔽 Hosted room sync
                        if (roomName == firebase->getHostedRoomKey()) {
                            firebase->setHostedRoom(dataVal.toObject());

                            QString state = firebase->getHostedRoom().value("state").toString();
                            QString host = firebase->getHostedRoom().value("Host").toString();

                            if (host == currentUsername) {
                                ui->StartGameBtn->setEnabled(state == "ready");
                            } else {
                                ui->StartGameBtn->setEnabled(false);
                            }

                            if (state == "started") {

                            }
                        }
                    }
                }

                // Build formatted room list
                QStringList displayList;
                QStringList keyList;
                for (auto it = roomsCache.begin(); it != roomsCache.end(); ++it) {
                    QString roomKey = it.key();
                    QString host = it.value().value("Host").toString();
                    QString guest = it.value().value("Guest").toString();
                    QString state = it.value().value("state").toString();
                    if (state.isEmpty()) state = "waiting";
                    if (guest.isEmpty()) guest = "...";
                    QString display = QString("Room of %1: %2 VS %3 (%4)")
                                          .arg(host)
                                          .arg(host)
                                          .arg(guest)
                                          .arg(state);
                    displayList << display;
                    keyList << roomKey;
                }

                updateRoomsList(displayList);
                roomKeyMapping = keyList;
            }
        }
    });
}


void MainWindow::updateRoomsList(const QStringList &rooms)
{
    auto *model = new QStringListModel(rooms, this);
    ui->RoomsList->setModel(model);
}

void MainWindow::createRoom()
{
    firebase->createRoom(currentUsername);
}

void MainWindow::joinRoom(const QString &roomName)
{
    firebase->joinRoom(roomName, currentUsername);
}

void MainWindow::fullscreen()
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void MainWindow::exit()
{
    qApp->quit();
}

void MainWindow::about()
{

}

void MainWindow::gameRules()
{

}

QVector<cardWidget*> MainWindow::createCardWidgets()
{
    QStringList cardNames = {
        "Clairvoyance", "Seek scriptures", "Detect evil and good",
        "Protection from evil and good", "Augury", "Borrowed knowledge", "Daring exploration", "Guided exploration"
    };

    QVector<cardWidget*> cards;
    for (const QString& name : cardNames) {
        cardWidget* card = CardFactory::createCard(name);
        if (card) cards.append(card);
    }
    return cards;
}

void MainWindow::addCard(cardWidget* card)
{
    QStringList deck = deckModel->stringList();
    deck << card->name();
    deckModel->setStringList(deck);
    int cardCount = ui->CardCount->text().toInt();
    cardCount++;
    ui->CardCount->setText(QString::number(cardCount));
}

void MainWindow::clearDeck()
{
    deckModel->setStringList({});
    ui->CardCount->setText("0");
}

void MainWindow::setCardPreview(cardWidget* card)
{
            ui->CardPreview->setPixmap(QPixmap(":/cards/" + card->name().toLower().replace(" ", "_") + ".png").scaled(200, 280));
            ui->CardDescription->setText(card->description());
}

void MainWindow::onExportDeckClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Deck"), "", "Landspire Deck (*.lspdeck)");
    if (!fileName.isEmpty()) {
        exportDeck(fileName);
    }
}

void MainWindow::onImportDeckClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Deck"), "", "Landspire Deck (*.lspdeck)");
    if (!fileName.isEmpty()) {
        importDeck(fileName);
    }
}

void MainWindow::exportDeck(const QString& path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file for writing" << path;
        return;
    }

    QTextStream out(&file);

    const QStringList cards = deckModel->stringList();
    for(const QString& card : cards)
    {
        out << card << "\n";
    }

    file.close();
}

void MainWindow::importDeck(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for reading:" << path;
        return;
    }

    QStringList cards;
    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
        {
            cards << line;
        }
    }

    file.close();
    deckModel->setStringList(cards);
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->DeckList) {
        if (event->type() == QEvent::DragEnter || event->type() == QEvent::DragMove) {
            auto dragEvent = static_cast<QDragMoveEvent*>(event);
            //if (dragEvent->mimeData()->hasText()) {
            if (dragEvent->mimeData()->hasFormat("application/x-card"))
                dragEvent->acceptProposedAction();
                return true;
            }
        else if (event->type() == QEvent::Drop) {
            if (auto dropEvent = dynamic_cast<QDropEvent*>(event)) {
                //if (dropEvent->mimeData()->hasText()) {
                if (dropEvent->mimeData()->hasFormat("application/x-card")){
                    //QString name = dropEvent->mimeData()->text();

                    QByteArray raw = dropEvent->mimeData()->data("application/x-card");
                    quintptr ptrValue = raw.toULongLong();
                    cardWidget* card = reinterpret_cast<cardWidget*>(ptrValue);

                    if (card) {
                        QString name = card->name();

                        QStringList deck = deckModel->stringList();
                        deck << name;
                        deckModel->setStringList(deck);

                        dropEvent->acceptProposedAction();
                        int cardCount = ui->CardCount->text().toInt();
                        cardCount++;
                        ui->CardCount->setText(QString::number(cardCount));
                        return true;}
                }
            }
        }
        else if (event->type() == QEvent::ContextMenu) {
            QContextMenuEvent* contextEvent = static_cast<QContextMenuEvent*>(event);
            QModelIndex index = ui->DeckList->indexAt(contextEvent->pos());

            if (index.isValid()) {
                QStringList deck = deckModel->stringList();
                deck.removeAt(index.row());
                deckModel->setStringList(deck);
                ui->CardCount->setText(QString::number(deck.size()));
                return true;
            }
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!currentUsername.isEmpty() && firebase) {
        QNetworkRequest request(QUrl(firebase->getDatabaseUrl() + "/connectedUsers/" + currentUsername + ".json"));
        firebase->getNetworkManager()->deleteResource(request);
    }
    QMainWindow::closeEvent(event);
}

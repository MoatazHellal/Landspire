#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "cardwidget.h"
#include "cardfactory.h"
#include <qevent.h>
#include "inputdialog.h"
#include "cardcollectionviewer.h"

#include <QLabel>
#include <QFileDialog>
#include <algorithm>
#include <random>
#include <QMimeData>
#include <QDrag>
#include <QRandomGenerator>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    ui->PlayerDeck->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->PlayerDeck, &QWidget::customContextMenuRequested, this, &GameWindow::onDeckContextMenuRequested);
    ui->PlayerGraveyard->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->PlayerGraveyard, &QWidget::customContextMenuRequested, this, &GameWindow::onGraveyardContextMenuRequested);

    ui->PlayerDeck->installEventFilter(this);
    ui->PlayerGraveyard->installEventFilter(this);
    ui->HandWidget->installEventFilter(this);
    ui->PlayerMainField->installEventFilter(this);

    ui->PlayerDeck->setAcceptDrops(true);
    ui->PlayerGraveyard->setAcceptDrops(true);
    ui->HandWidget->setAcceptDrops(true);
    ui->PlayerMainField->setAcceptDrops(true);


}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::createActions()
{
    loadDeckAct = new QAction(tr("Load Deck"), this);
    loadDeckAct->setShortcut(QKeySequence("Ctrl+L"));
    connect(loadDeckAct, &QAction::triggered, this, &GameWindow::loadDeck);

    setLPAct =new QAction(tr("Set LP"), this);
    setLPAct->setShortcut(QKeySequence("Ctrl+K"));
    connect(setLPAct, &QAction::triggered, this, &GameWindow::setLP);

    rollDiceAct =new QAction(tr("Roll Dice"), this);
    rollDiceAct->setShortcut(QKeySequence("Ctrl+I"));
    connect(rollDiceAct, &QAction::triggered, this, &GameWindow::rollDice);
}

void GameWindow::createMenus()
{
    gameMenu = new QMenu(tr("Game"), this);
    gameMenu->addAction(loadDeckAct);
    gameMenu->addAction(setLPAct);
    gameMenu->addAction(rollDiceAct);

    menuBar()->addMenu(gameMenu);
}

void GameWindow::log(QString entry)
{
    QString currentText = ui->LogPanel->text();
    currentText.append(entry + "\n");
    ui->LogPanel->setText(currentText);
}

void GameWindow::loadDeck()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Deck"), "", "Landspire Deck (*.lspdeck)");

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for reading:" << fileName;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString cardName = in.readLine().trimmed();
        if (cardName.isEmpty())
            continue;

        cardWidget* card = CardFactory::createCard(cardName);
        if (!card) {
            qWarning() << "Card creation failed for name:" << cardName;
            continue;
        }

        PlayerDeck.append(card);
    }

    file.close();

    onDeckLoaded();
}

void GameWindow::onDeckLoaded()
{
    updateDeckSize();
    foreach (auto card, PlayerDeck)
    {
        card->setDragContext(DragContext::Game);
        connect(card, &cardWidget::hovered, this, &GameWindow::setCardPreview);
    }
    shuffleDeck();
}

void GameWindow::setLP() {
    int previousLP = ui->PlayerLP->text().split(": ").last().toInt();
    int newLP;
    InputDialog dialog("Enter new LP:", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString input = dialog.getInputText();
        bool ok;
        newLP = input.toInt(&ok);
        if (ok) {
            ui->PlayerLP->setText("LP : " + QString::number(newLP));
        }
    }
    int diff = newLP - previousLP;
    QString diffStr = (diff >= 0 ? "+" : "") + QString::number(diff);
    log("Your LP was set to " + QString::number(newLP) + " (" + diffStr + ")");
}

void GameWindow::takeCardFromDeck(QLayout* destination)
{
    if(!PlayerDeck.isEmpty())
    {
        cardWidget* card = PlayerDeck.takeFirst();
        card->resize(50,70);
        destination->addWidget(card);
    }
    updateDeckSize();
}

void GameWindow::drawCards() {
    InputDialog dialog("How many cards to draw?", this);
    int count;
    if (dialog.exec() == QDialog::Accepted) {
        bool ok;
        count = dialog.getInputText().toInt(&ok);
        if (ok && count > 0) {
            for (int i = 0; i < count; ++i)
                drawCard();
        }
    }
    log("You drew" + QString::number(count) + "cards");
}

void GameWindow::drawCard()
{
    takeCardFromDeck(ui->HandLayout);
    log("You drew 1 card");
}

void GameWindow::viewDeck()
{
    CardCollectionViewer* viewer = new CardCollectionViewer(PlayerDeck, "Deck", this);
    foreach (auto cardPreview, viewer->cardPreviews()) {
        connect(cardPreview, &cardWidget::hovered, this, &GameWindow::setCardPreview);
    }
    viewer->setAttribute(Qt::WA_DeleteOnClose);
    viewer->show();
    log("You're viewing your deck");
}

void GameWindow::viewGraveyard()
{
    CardCollectionViewer* viewer = new CardCollectionViewer(PlayerGraveyard, "Graveyard", this);
    foreach (auto cardPreview, viewer->cardPreviews()) {
        connect(cardPreview, &cardWidget::hovered, this, &GameWindow::setCardPreview);
    }
    viewer->setAttribute(Qt::WA_DeleteOnClose);
    viewer->show();
    log("You're viewing your Graveyard");
}

void GameWindow::revealTopCard()
{
    takeCardFromDeck(ui->PlayerMainFieldLayout);
}

void GameWindow::millTopCard()
{
    if (!PlayerDeck.isEmpty())
    {
        auto card = PlayerDeck.takeFirst();
        PlayerGraveyard.prepend(card);
        updateDeckSize();
        updateGraveyardSize();
    }
}

void GameWindow::shuffleDeck()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(PlayerDeck.begin(), PlayerDeck.end(), g);

    log("You shuffled your deck");
}

void GameWindow::rollDice() {
    InputDialog dialog("Enter dice type. d", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString input = dialog.getInputText();
        bool ok;
        int sides = input.toInt(&ok);
        if (ok) {
            log("You rolled a " + QString::number(QRandomGenerator::global()->bounded(1, sides + 1)));
        }
    }
}

void GameWindow::onDeckContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(this);
    QAction* drawCardAct = contextMenu.addAction("Draw card");
    QAction* drawCardsAct = contextMenu.addAction("Draw cards");
    contextMenu.addSeparator();
    QAction* viewDeckAct = contextMenu.addAction("View deck");
    contextMenu.addSeparator();
    QAction* shuffleAct = contextMenu.addAction("Shuffle deck");

    connect(drawCardAct, &QAction::triggered, this, &GameWindow::drawCard);
    connect(drawCardsAct, &QAction::triggered, this, &GameWindow::drawCards);
    connect(viewDeckAct, &QAction::triggered, this, &GameWindow::viewDeck);
    connect(shuffleAct, &QAction::triggered, this, &GameWindow::shuffleDeck);

    contextMenu.exec(ui->PlayerDeck->mapToGlobal(pos));
}

void GameWindow::onGraveyardContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(this);
    QAction* viewGraveAct = contextMenu.addAction("View graveyard");

    connect(viewGraveAct, &QAction::triggered, this, &GameWindow::viewGraveyard);

    contextMenu.exec(ui->PlayerGraveyard->mapToGlobal(pos));
}

void GameWindow::setCardPreview(cardWidget* card)
{
    ui->ImagePreview->setPixmap(QPixmap(":/cards/" + card->name().toLower().replace(" ", "_") + ".png").scaled(200, 280));
    ui->DescriptionPreview->setText(card->description());
}

void GameWindow::updateDeckSize()
{
    ui->DeckSize->setText(QString::number(PlayerDeck.size()));
}

void GameWindow::updateGraveyardSize()
{
    ui->GraveyardSize->setText(QString::number(PlayerGraveyard.size()));
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
    QPoint globalPos = mapToGlobal(event->pos());
    QPoint labelPos = ui->PlayerLP->mapFromGlobal(globalPos);

    if (ui->PlayerLP->rect().contains(labelPos))
    {
        int lp = ui->PlayerLP->text().split(": ").last().toInt();
        if (event->button() == Qt::LeftButton)
        {
            lp++;
            log("Your LP was set to " + QString::number(lp) + " (+1)");
        }
        else if (event->button() == Qt::RightButton)
        {
            lp--;
            log("Your LP was set to " + QString::number(lp) + " (-1)");
        }
        ui->PlayerLP->setText("LP : " + QString::number(lp));
    }
    if (event->button() == Qt::LeftButton){
        QDrag* drag = new QDrag(this);
        QMimeData* mime = new QMimeData;

        if (ui->PlayerDeck->geometry().contains(event->pos()))
            mime->setData("application/x-deckaction", "deckdrag");

        drag->setMimeData(mime);
        drag->exec(Qt::MoveAction);
    }

    QMainWindow::mousePressEvent(event);
}

bool GameWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::DragEnter || event->type() == QEvent::DragMove) {
        auto dragEvent = static_cast<QDragMoveEvent*>(event);
        if (dragEvent->mimeData()->hasFormat("application/x-card") ||
            dragEvent->mimeData()->hasFormat("application/x-deckaction")){
            dragEvent->acceptProposedAction();
            return true;
        }
    }
    if (event->type() == QEvent::Drop) {
        auto dropEvent = dynamic_cast<QDropEvent*>(event);
        if (dropEvent->mimeData()->hasFormat("application/x-card")) {
                QByteArray raw = dropEvent->mimeData()->data("application/x-card");
                quintptr ptrValue = raw.toULongLong();
                cardWidget* card = reinterpret_cast<cardWidget*>(ptrValue);

            if(card) {
            if (watched == ui->PlayerDeck) {
                if (QLayout* parentLayout = card->parentWidget()->layout()) {
                    parentLayout->removeWidget(card);
                    card->setParent(nullptr);
                }
                PlayerDeck.prepend(card);
                updateDeckSize();
            }else if (watched == ui->PlayerGraveyard){
                if (QLayout* parentLayout = card->parentWidget()->layout()) {
                    parentLayout->removeWidget(card);
                    card->setParent(nullptr);
                }
                PlayerGraveyard.prepend(card);
                updateGraveyardSize();
            }
            else if (watched == ui->PlayerMainField) {
                if(card->original())
                {
                    card->setParent(nullptr);
                    card = card->original();
                }
                PlayerDeck.removeOne(card);
                PlayerGraveyard.removeOne(card);
                updateDeckSize();
                updateGraveyardSize();
                card->resize(50,70);
                ui->PlayerMainFieldLayout->addWidget(card);
            } else if (watched == ui->HandWidget) {
                if(card->original())
                {
                    card->setParent(nullptr);
                    card = card->original();
                }
                PlayerDeck.removeOne(card);
                PlayerGraveyard.removeOne(card);
                updateDeckSize();
                updateGraveyardSize();
                card->resize(50,70);
                ui->HandLayout->addWidget(card);
            }
            }

            dropEvent->acceptProposedAction();
            return true;
        }
        else if (dropEvent->mimeData()->hasFormat("application/x-deckaction")) {
            if (watched == ui->HandWidget) {
                drawCard();
            } else if (watched == ui->PlayerMainField) {
                revealTopCard();
            }else if (watched == ui->PlayerGraveyard) {
                millTopCard();
            }

            dropEvent->acceptProposedAction();
            return true;
        }

    }
    return QMainWindow::eventFilter(watched, event);
}

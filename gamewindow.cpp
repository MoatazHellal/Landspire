#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "cardwidget.h"
#include "cardfactory.h"
#include <qevent.h>
#include "inputdialog.h"

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

    ui->PlayerDeck->installEventFilter(this);
    ui->HandWidget->installEventFilter(this);
    ui->PlayerMainField->installEventFilter(this);

    ui->PlayerDeck->setAcceptDrops(true);
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
    InputDialog dialog("Enter new LP:", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString input = dialog.getInputText();
        bool ok;
        int lp = input.toInt(&ok);
        if (ok) {
            ui->PlayerLP->setText(QString::number(lp));
        }
    }
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
    if (dialog.exec() == QDialog::Accepted) {
        bool ok;
        int count = dialog.getInputText().toInt(&ok);
        if (ok && count > 0) {
            for (int i = 0; i < count; ++i)
                drawCard();
        }
    }
}

void GameWindow::drawCard()
{
    takeCardFromDeck(ui->HandLayout);
}

void GameWindow::revealTopCard()
{
    takeCardFromDeck(ui->PlayerMainFieldLayout);
}

void GameWindow::shuffleDeck()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(PlayerDeck.begin(), PlayerDeck.end(), g);
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
    QAction* shuffleAct = contextMenu.addAction("Shuffle deck");

    connect(drawCardAct, &QAction::triggered, this, &GameWindow::drawCard);
    connect(drawCardsAct, &QAction::triggered, this, &GameWindow::drawCards);
    connect(shuffleAct, &QAction::triggered, this, &GameWindow::shuffleDeck);

    contextMenu.exec(ui->PlayerDeck->mapToGlobal(pos));
}

void GameWindow::setCardPreview(cardWidget* card)
{
    ui->ImagePreview->setPixmap(QPixmap(":/cards/" + card->name().toLower().replace(" ", "_") + ".png").scaled(200, 280));
    ui->DescriptionPreview->setText(card->description());
}

void GameWindow::updateDeckSize()
{
    if(PlayerDeck.size() != 0)
        ui->DeckSize->setText(QString::number(PlayerDeck.size()));
    else {
        ui->DeckSize->setText(QString::number(PlayerDeck.size()));
    }
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton &&
        ui->PlayerDeck->geometry().contains(event->pos())) {
        QDrag* drag = new QDrag(this);
        QMimeData* mime = new QMimeData;
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
            dragEvent->mimeData()->hasFormat("application/x-deckaction")) {
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
            } else if (watched == ui->PlayerMainField) {
                ui->PlayerMainFieldLayout->addWidget(card);
            } else if (watched == ui->HandWidget) {
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
            }

            dropEvent->acceptProposedAction();
            return true;
        }

    }
    return QMainWindow::eventFilter(watched, event);
}

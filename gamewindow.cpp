#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "cardwidget.h"
#include "cardfactory.h"

#include <QStackedLayout>
#include <QLabel>
#include <QFileDialog>
#include <algorithm>
#include <random>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    ui->PlayerDeck->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->PlayerDeck, &QWidget::customContextMenuRequested, this, &GameWindow::onDeckContextMenuRequested);

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
}

void GameWindow::createMenus()
{
    gameMenu = new QMenu(tr("Game"), this);
    gameMenu->addAction(loadDeckAct);

    menuBar()->addMenu(gameMenu);
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
        connect(card, &cardWidget::hovered, this, &GameWindow::setCardPreview);
    }
    shuffleDeck();
}

void GameWindow::drawCard()
{
    if(!PlayerDeck.isEmpty())
    {
        cardWidget* card = PlayerDeck.takeFirst();
        card->resize(50,70);
        ui->HandLayout->addWidget(card);
    }
    updateDeckSize();
}

void GameWindow::shuffleDeck()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(PlayerDeck.begin(), PlayerDeck.end(), g);
}
void GameWindow::onDeckContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(this);
    QAction* drawCardAct = contextMenu.addAction("Draw card");
    QAction* drawCardsAct = contextMenu.addAction("Draw cards");
    contextMenu.addSeparator();
    QAction* shuffleAct = contextMenu.addAction("Shuffle deck");

    connect(drawCardAct, &QAction::triggered, this, &GameWindow::drawCard);
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

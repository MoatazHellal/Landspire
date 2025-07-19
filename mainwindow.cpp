#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "connectdialogue.h"
#include "cardwidget.h"
#include "cardfactory.h"
#include <qevent.h>
#include <QMimeData>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);

    createActions();
    createMenus();

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

    connect(Dialog, &connectDialogue::loginRequested, this, [this, Dialog](const QString& user, const QString& pass){
        // TODO: Add login code here
        qDebug() << "Login requested: " << user << pass;
        Dialog->accept();
    });

    connect(Dialog, &connectDialogue::registerRequested, this, [this, Dialog](const QString& user, const QString& pass){
        // TODO: Add registration code here
        qDebug() << "Register requested: " << user << pass;
        Dialog->accept();
    });

    Dialog->exec();
}

void MainWindow::serverDisconnect()
{

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
        "Protection from evil and good", "Augury", "Borrowed knowledge",
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
            if (dragEvent->mimeData()->hasText()) {
                dragEvent->acceptProposedAction();
                return true;
            }
        } else if (event->type() == QEvent::Drop) {
            if (auto dropEvent = dynamic_cast<QDropEvent*>(event)) {
                if (dropEvent->mimeData()->hasText()) {
                    QString name = dropEvent->mimeData()->text();

                    QStringList deck = deckModel->stringList();
                    deck << name;
                    deckModel->setStringList(deck);

                    dropEvent->acceptProposedAction();
                    int cardCount = ui->CardCount->text().toInt();
                    cardCount++;
                    ui->CardCount->setText(QString::number(cardCount));
                    return true;
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

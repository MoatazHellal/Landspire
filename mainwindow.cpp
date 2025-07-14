#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "connectdialogue.h"
#include "cardwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);

    createActions();
    createMenus();

    ui->CardPreview->setPixmap(QPixmap(":/cards/card.png").scaled(200,280));

    QVector<cardWidget*> cards = createCardWidgets();
    int maxCols = 6;
    int row = 0, col = 0;
    foreach (auto card, cards) {
        ui->CardsGrid->addWidget(card, row, col);
        if (++col >= maxCols)
        {
            col = 0;
            ++row;
        }
        connect(card, &cardWidget::hovered, this, [this](cardWidget* c) {
            ui->CardPreview->setPixmap(QPixmap(":/cards/" + c->name().toLower().replace(" ", "_") + ".png").scaled(200, 280));});
    }
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

}

void MainWindow::exit()
{

}

void MainWindow::about()
{

}

void MainWindow::gameRules()
{

}

QVector<cardWidget*> MainWindow::createCardWidgets()
{
    QVector<cardWidget*> cards;

    cardWidget* card = new cardWidget("Fire Village", Affinity::Fire, QPixmap(":/cards/card.png"));
    cards.append(card);
    cardWidget* card1 = new cardWidget("Fire Village", Affinity::Fire, QPixmap(":/cards/card.png"));
    cards.append(card1);
    cardWidget* card2 = new cardWidget("Fire Village", Affinity::Fire, QPixmap(":/cards/card.png"));
    cards.append(card2);
    cardWidget* card3 = new cardWidget("Fire Village", Affinity::Fire, QPixmap(":/cards/card.png"));
    cards.append(card3);

    return cards;
}

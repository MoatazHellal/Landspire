#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "cardwidget.h"
#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void loadDeck();
    void setLP();
    void rollDice();

    void onDeckContextMenuRequested(const QPoint &pos);
    void drawCards();
    void drawCard();
    void revealTopCard();
    void shuffleDeck();

private:
    Ui::GameWindow *ui;

    void createActions();
    void createMenus();

    void onDeckLoaded();

    void log(QString entry);
    void setCardPreview(cardWidget* card);
    void takeCardFromDeck(QLayout* destination);
    void updateDeckSize();

    void mousePressEvent(QMouseEvent* event) override;

    QAction* loadDeckAct;
    QAction* setLPAct;
    QAction* rollDiceAct;

    QMenu* gameMenu;

    QVector<cardWidget*> PlayerDeck;
};

#endif // GAMEWINDOW_H

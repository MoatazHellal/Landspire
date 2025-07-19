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

private slots:
    void loadDeck();

    void onDeckContextMenuRequested(const QPoint &pos);
    void drawCard();
    void shuffleDeck();

private:
    Ui::GameWindow *ui;

    void createActions();
    void createMenus();

    void onDeckLoaded();

    void setCardPreview(cardWidget* card);
    void updateDeckSize();

    QAction* loadDeckAct;

    QMenu* gameMenu;

    QVector<cardWidget*> PlayerDeck;
};

#endif // GAMEWINDOW_H

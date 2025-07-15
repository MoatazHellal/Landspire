#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "cardwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;


private slots:
    void serverConnect();
    void serverDisconnect();
    void fullscreen();
    void exit();
    void about();
    void gameRules();

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();


    QVector<cardWidget*> createCardWidgets();

    void addCard(cardWidget* card);
    void clearDeck();
    void setCardPreview(cardWidget* card);

    QMenu* landspireMenu;
    QMenu* helpMenu;

    QAction* connectAct;
    QAction* disconnectAct;
    QAction* fullscreenAct;
    QAction* exitAct;
    QAction* aboutLandspireAct;
    QAction* gameRulesAct;

    QStringListModel* deckModel;
};
#endif // MAINWINDOW_H

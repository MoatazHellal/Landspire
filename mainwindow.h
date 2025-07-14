#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    QMenu* landspireMenu;
    QMenu* helpMenu;

    QAction* connectAct;
    QAction* disconnectAct;
    QAction* fullscreenAct;
    QAction* exitAct;
    QAction* aboutLandspireAct;
    QAction* gameRulesAct;
};
#endif // MAINWINDOW_H

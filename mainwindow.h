#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "cardwidget.h"
#include "firebaseapi.h"


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
    void closeEvent(QCloseEvent *event) override;

private slots:
    void serverConnect();
    void serverDisconnect();
    void fullscreen();
    void exit();
    void about();
    void gameRules();

    void onExportDeckClicked();
    void onImportDeckClicked();

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();


    QVector<cardWidget*> createCardWidgets();

    void addCard(cardWidget* card);
    void clearDeck();
    void setCardPreview(cardWidget* card);

    void exportDeck(const QString& path);
    void importDeck(const QString& path);

    void startListeningForConnectedUsers();
    void fetchConnectedUsersOnce();
    void updateConnectedUsersList(const QStringList &users);

    void createRoom();
    void joinRoom(const QString &roomName);
    void startListeningForRooms();
    void updateRoomsList(const QStringList &rooms);

    const QString defaultWindowTitle = "Landspire";

    QMenu* landspireMenu;
    QMenu* helpMenu;

    QAction* connectAct;
    QAction* disconnectAct;
    QAction* fullscreenAct;
    QAction* exitAct;
    QAction* aboutLandspireAct;
    QAction* gameRulesAct;

    QStringList connectedUsers;
    QStringListModel* connectedUsersModel;
    QStringListModel* deckModel;

    FirebaseAPI* firebase;
    QNetworkReply* connectedUsersReply = nullptr;
    QNetworkReply* roomsReply = nullptr;
    QString currentUsername;
    QStringList roomKeyMapping;
};
#endif // MAINWINDOW_H

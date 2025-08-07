/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QListView *listView;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QGridLayout *CardsGrid;
    QWidget *RightPane;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_2;
    QWidget *Image;
    QHBoxLayout *horizontalLayout_6;
    QLabel *CardPreview;
    QWidget *Description;
    QHBoxLayout *horizontalLayout_10;
    QLabel *CardDescription;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *ImportDeck;
    QPushButton *ExportDeck;
    QLabel *CardCount;
    QPushButton *ClearDeck;
    QListView *DeckList;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QListView *listView_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QListView *listView_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1096, 679);
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_5 = new QHBoxLayout(centralwidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(tab);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        listView = new QListView(tab);
        listView->setObjectName("listView");

        horizontalLayout_2->addWidget(listView);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 2);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        scrollArea = new QScrollArea(tab_2);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 620, 547));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName("gridLayout_3");
        CardsGrid = new QGridLayout();
        CardsGrid->setObjectName("CardsGrid");

        gridLayout_3->addLayout(CardsGrid, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(scrollArea);

        RightPane = new QWidget(tab_2);
        RightPane->setObjectName("RightPane");
        verticalLayout_2 = new QVBoxLayout(RightPane);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        tabWidget_2 = new QTabWidget(RightPane);
        tabWidget_2->setObjectName("tabWidget_2");
        Image = new QWidget();
        Image->setObjectName("Image");
        horizontalLayout_6 = new QHBoxLayout(Image);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        CardPreview = new QLabel(Image);
        CardPreview->setObjectName("CardPreview");

        horizontalLayout_6->addWidget(CardPreview);

        tabWidget_2->addTab(Image, QString());
        Description = new QWidget();
        Description->setObjectName("Description");
        horizontalLayout_10 = new QHBoxLayout(Description);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        CardDescription = new QLabel(Description);
        CardDescription->setObjectName("CardDescription");
        CardDescription->setWordWrap(true);

        horizontalLayout_10->addWidget(CardDescription);

        tabWidget_2->addTab(Description, QString());

        verticalLayout->addWidget(tabWidget_2);

        widget = new QWidget(RightPane);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(20, 20));
        horizontalLayout_7 = new QHBoxLayout(widget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        ImportDeck = new QPushButton(widget);
        ImportDeck->setObjectName("ImportDeck");

        horizontalLayout_7->addWidget(ImportDeck);

        ExportDeck = new QPushButton(widget);
        ExportDeck->setObjectName("ExportDeck");

        horizontalLayout_7->addWidget(ExportDeck);

        CardCount = new QLabel(widget);
        CardCount->setObjectName("CardCount");
        CardCount->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_7->addWidget(CardCount);

        ClearDeck = new QPushButton(widget);
        ClearDeck->setObjectName("ClearDeck");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ClearDeck->sizePolicy().hasHeightForWidth());
        ClearDeck->setSizePolicy(sizePolicy2);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        ClearDeck->setIcon(icon);

        horizontalLayout_7->addWidget(ClearDeck);


        verticalLayout->addWidget(widget);

        DeckList = new QListView(RightPane);
        DeckList->setObjectName("DeckList");

        verticalLayout->addWidget(DeckList);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(2, 2);

        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout_3->addWidget(RightPane);

        horizontalLayout_3->setStretch(0, 3);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout_5->addLayout(horizontalLayout_3);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        horizontalLayout_8 = new QHBoxLayout(tab_3);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        listView_2 = new QListView(tab_3);
        listView_2->setObjectName("listView_2");

        verticalLayout_3->addWidget(listView_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(tab_3);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_3->addLayout(horizontalLayout);


        horizontalLayout_8->addLayout(verticalLayout_3);

        listView_3 = new QListView(tab_3);
        listView_3->setObjectName("listView_3");

        horizontalLayout_8->addWidget(listView_3);

        horizontalLayout_8->setStretch(0, 3);
        horizontalLayout_8->setStretch(1, 2);
        tabWidget->addTab(tab_3, QString());

        horizontalLayout_5->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1096, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Home", nullptr));
        CardPreview->setText(QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(Image), QCoreApplication::translate("MainWindow", "Image", nullptr));
        CardDescription->setText(QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(Description), QCoreApplication::translate("MainWindow", "Description", nullptr));
        ImportDeck->setText(QCoreApplication::translate("MainWindow", "Import Deck", nullptr));
        ExportDeck->setText(QCoreApplication::translate("MainWindow", "Export Deck", nullptr));
        CardCount->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        ClearDeck->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Deck", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Create Room", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Join Room", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Lobby", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

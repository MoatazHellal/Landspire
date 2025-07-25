/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *PhaseLayout;
    QVBoxLayout *FieldLayout;
    QWidget *OpponentMainField;
    QWidget *ShowdownField;
    QWidget *PlayerMainField;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *PlayerMainFieldLayout;
    QWidget *HandWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *HandLayout;
    QVBoxLayout *SideLayout;
    QLabel *OpponentLP;
    QWidget *OpponentDeck;
    QWidget *OpponentGraveyard;
    QSpacerItem *verticalSpacer;
    QWidget *PlayerGraveyard;
    QVBoxLayout *verticalLayout_4;
    QLabel *GraveyardSize;
    QWidget *PlayerDeck;
    QVBoxLayout *verticalLayout;
    QLabel *DeckSize;
    QLabel *PlayerLP;
    QVBoxLayout *InfoLayout;
    QTabWidget *CardPreview;
    QWidget *Image;
    QVBoxLayout *verticalLayout_3;
    QLabel *ImagePreview;
    QWidget *Description;
    QVBoxLayout *verticalLayout_2;
    QLabel *DescriptionPreview;
    QLabel *LogPanel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName("GameWindow");
        GameWindow->resize(1022, 804);
        centralwidget = new QWidget(GameWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        PhaseLayout = new QVBoxLayout();
        PhaseLayout->setObjectName("PhaseLayout");

        horizontalLayout_2->addLayout(PhaseLayout);

        FieldLayout = new QVBoxLayout();
        FieldLayout->setObjectName("FieldLayout");
        OpponentMainField = new QWidget(centralwidget);
        OpponentMainField->setObjectName("OpponentMainField");
        OpponentMainField->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #555;\n"
"        border-radius: 10px;\n"
""));

        FieldLayout->addWidget(OpponentMainField);

        ShowdownField = new QWidget(centralwidget);
        ShowdownField->setObjectName("ShowdownField");
        ShowdownField->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #555;\n"
"        border-radius: 10px;\n"
""));

        FieldLayout->addWidget(ShowdownField);

        PlayerMainField = new QWidget(centralwidget);
        PlayerMainField->setObjectName("PlayerMainField");
        PlayerMainField->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #555;\n"
"        border-radius: 10px;\n"
""));
        horizontalLayout_4 = new QHBoxLayout(PlayerMainField);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        PlayerMainFieldLayout = new QHBoxLayout();
        PlayerMainFieldLayout->setObjectName("PlayerMainFieldLayout");

        horizontalLayout_4->addLayout(PlayerMainFieldLayout);


        FieldLayout->addWidget(PlayerMainField);

        HandWidget = new QWidget(centralwidget);
        HandWidget->setObjectName("HandWidget");
        HandWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #555;\n"
"        border-radius: 10px;"));
        horizontalLayout_3 = new QHBoxLayout(HandWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        HandLayout = new QHBoxLayout();
        HandLayout->setObjectName("HandLayout");

        horizontalLayout_3->addLayout(HandLayout);


        FieldLayout->addWidget(HandWidget);

        FieldLayout->setStretch(0, 2);
        FieldLayout->setStretch(1, 1);
        FieldLayout->setStretch(2, 2);
        FieldLayout->setStretch(3, 1);

        horizontalLayout_2->addLayout(FieldLayout);

        SideLayout = new QVBoxLayout();
        SideLayout->setObjectName("SideLayout");
        OpponentLP = new QLabel(centralwidget);
        OpponentLP->setObjectName("OpponentLP");
        OpponentLP->setAlignment(Qt::AlignmentFlag::AlignCenter);

        SideLayout->addWidget(OpponentLP);

        OpponentDeck = new QWidget(centralwidget);
        OpponentDeck->setObjectName("OpponentDeck");
        OpponentDeck->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #555;\n"
"        border-radius: 10px;"));

        SideLayout->addWidget(OpponentDeck);

        OpponentGraveyard = new QWidget(centralwidget);
        OpponentGraveyard->setObjectName("OpponentGraveyard");
        OpponentGraveyard->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #555;\n"
"        border-radius: 10px;"));

        SideLayout->addWidget(OpponentGraveyard);

        verticalSpacer = new QSpacerItem(20, 150, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        SideLayout->addItem(verticalSpacer);

        PlayerGraveyard = new QWidget(centralwidget);
        PlayerGraveyard->setObjectName("PlayerGraveyard");
        PlayerGraveyard->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #555;\n"
"        border-radius: 10px;"));
        verticalLayout_4 = new QVBoxLayout(PlayerGraveyard);
        verticalLayout_4->setObjectName("verticalLayout_4");
        GraveyardSize = new QLabel(PlayerGraveyard);
        GraveyardSize->setObjectName("GraveyardSize");
        QFont font;
        font.setBold(true);
        GraveyardSize->setFont(font);
        GraveyardSize->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(GraveyardSize);


        SideLayout->addWidget(PlayerGraveyard);

        PlayerDeck = new QWidget(centralwidget);
        PlayerDeck->setObjectName("PlayerDeck");
        PlayerDeck->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #555;\n"
"        border-radius: 10px;"));
        verticalLayout = new QVBoxLayout(PlayerDeck);
        verticalLayout->setObjectName("verticalLayout");
        DeckSize = new QLabel(PlayerDeck);
        DeckSize->setObjectName("DeckSize");
        DeckSize->setFont(font);
        DeckSize->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(DeckSize);


        SideLayout->addWidget(PlayerDeck);

        PlayerLP = new QLabel(centralwidget);
        PlayerLP->setObjectName("PlayerLP");
        PlayerLP->setAlignment(Qt::AlignmentFlag::AlignCenter);

        SideLayout->addWidget(PlayerLP);

        SideLayout->setStretch(1, 1);
        SideLayout->setStretch(2, 1);
        SideLayout->setStretch(3, 1);
        SideLayout->setStretch(4, 1);
        SideLayout->setStretch(5, 1);

        horizontalLayout_2->addLayout(SideLayout);

        InfoLayout = new QVBoxLayout();
        InfoLayout->setObjectName("InfoLayout");
        CardPreview = new QTabWidget(centralwidget);
        CardPreview->setObjectName("CardPreview");
        Image = new QWidget();
        Image->setObjectName("Image");
        verticalLayout_3 = new QVBoxLayout(Image);
        verticalLayout_3->setObjectName("verticalLayout_3");
        ImagePreview = new QLabel(Image);
        ImagePreview->setObjectName("ImagePreview");

        verticalLayout_3->addWidget(ImagePreview);

        CardPreview->addTab(Image, QString());
        Description = new QWidget();
        Description->setObjectName("Description");
        verticalLayout_2 = new QVBoxLayout(Description);
        verticalLayout_2->setObjectName("verticalLayout_2");
        DescriptionPreview = new QLabel(Description);
        DescriptionPreview->setObjectName("DescriptionPreview");
        DescriptionPreview->setWordWrap(true);

        verticalLayout_2->addWidget(DescriptionPreview);

        CardPreview->addTab(Description, QString());

        InfoLayout->addWidget(CardPreview);

        LogPanel = new QLabel(centralwidget);
        LogPanel->setObjectName("LogPanel");
        LogPanel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        LogPanel->setWordWrap(true);

        InfoLayout->addWidget(LogPanel);

        InfoLayout->setStretch(0, 1);
        InfoLayout->setStretch(1, 1);

        horizontalLayout_2->addLayout(InfoLayout);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 10);
        horizontalLayout_2->setStretch(2, 2);
        horizontalLayout_2->setStretch(3, 4);
        GameWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1022, 26));
        GameWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(GameWindow);
        statusbar->setObjectName("statusbar");
        GameWindow->setStatusBar(statusbar);

        retranslateUi(GameWindow);

        CardPreview->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QCoreApplication::translate("GameWindow", "MainWindow", nullptr));
        OpponentLP->setText(QCoreApplication::translate("GameWindow", "0", nullptr));
        GraveyardSize->setText(QCoreApplication::translate("GameWindow", "0", nullptr));
        DeckSize->setText(QCoreApplication::translate("GameWindow", "0", nullptr));
        PlayerLP->setText(QCoreApplication::translate("GameWindow", "0", nullptr));
        ImagePreview->setText(QString());
        CardPreview->setTabText(CardPreview->indexOf(Image), QCoreApplication::translate("GameWindow", "Image", nullptr));
        DescriptionPreview->setText(QString());
        CardPreview->setTabText(CardPreview->indexOf(Description), QCoreApplication::translate("GameWindow", "Description", nullptr));
        LogPanel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *chatbox;
    QLineEdit *msgbox;
    QPushButton *sendBtn;
    QPushButton *timedMsgBtn;
    QLabel *label_3;
    QListWidget *contacts;
    QPushButton *addContactBtn;
    QLineEdit *new_contact_bar;
    QPushButton *rem_contact;
    QFrame *frame;
    QLabel *title;
    QPushButton *login;
    QLabel *login_status;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1000, 600);
        MainWindow->setMinimumSize(QSize(1000, 600));
        MainWindow->setMaximumSize(QSize(1000, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/logo.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background: #121212;\n"
"color: #ffffff ;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        chatbox = new QTextBrowser(centralwidget);
        chatbox->setObjectName("chatbox");
        chatbox->setGeometry(QRect(260, 80, 720, 400));
        QFont font;
        font.setPointSize(14);
        chatbox->setFont(font);
        chatbox->setStyleSheet(QString::fromUtf8("border: 1px solid #00e676;\n"
"color: #fff;"));
        msgbox = new QLineEdit(centralwidget);
        msgbox->setObjectName("msgbox");
        msgbox->setGeometry(QRect(260, 485, 580, 105));
        QFont font1;
        font1.setPointSize(12);
        msgbox->setFont(font1);
        msgbox->setStyleSheet(QString::fromUtf8("border: 1px solid #00e676;\n"
"padding: 0 20px;"));
        msgbox->setFrame(true);
        msgbox->setReadOnly(false);
        sendBtn = new QPushButton(centralwidget);
        sendBtn->setObjectName("sendBtn");
        sendBtn->setGeometry(QRect(845, 485, 135, 50));
        QFont font2;
        font2.setPointSize(11);
        sendBtn->setFont(font2);
        sendBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #00e676;\n"
"	color: #fff;\n"
"	border: 0;\n"
"	border-radius: 0;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #00c853;\n"
"}"));
        timedMsgBtn = new QPushButton(centralwidget);
        timedMsgBtn->setObjectName("timedMsgBtn");
        timedMsgBtn->setGeometry(QRect(845, 540, 135, 50));
        timedMsgBtn->setFont(font2);
        timedMsgBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #00e676;\n"
"	color: #fff;\n"
"	border: 0;\n"
"	border-radius: 0;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #00c853;\n"
"}"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 80, 200, 40));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("color: #00e676;\n"
"border: 1px solid #00e676;"));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        contacts = new QListWidget(centralwidget);
        contacts->setObjectName("contacts");
        contacts->setEnabled(true);
        contacts->setGeometry(QRect(20, 120, 200, 360));
        QFont font4;
        font4.setPointSize(16);
        contacts->setFont(font4);
        contacts->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        contacts->setStyleSheet(QString::fromUtf8("border: 1px solid #00e676;"));
        contacts->setViewMode(QListView::ViewMode::ListMode);
        contacts->setItemAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        addContactBtn = new QPushButton(centralwidget);
        addContactBtn->setObjectName("addContactBtn");
        addContactBtn->setGeometry(QRect(120, 530, 100, 60));
        addContactBtn->setFont(font2);
        addContactBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #00e676;\n"
"	color: #fff;\n"
"	border: 0;\n"
"	border-left: 1px solid #121212;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #00c853;\n"
"}"));
        new_contact_bar = new QLineEdit(centralwidget);
        new_contact_bar->setObjectName("new_contact_bar");
        new_contact_bar->setGeometry(QRect(20, 485, 200, 40));
        new_contact_bar->setFont(font1);
        new_contact_bar->setStyleSheet(QString::fromUtf8("border: 1px solid #00e676;\n"
"padding: 0 5px;\n"
"color :#fff;"));
        new_contact_bar->setFrame(true);
        new_contact_bar->setReadOnly(false);
        rem_contact = new QPushButton(centralwidget);
        rem_contact->setObjectName("rem_contact");
        rem_contact->setGeometry(QRect(20, 530, 100, 60));
        rem_contact->setFont(font2);
        rem_contact->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #00e676;\n"
"	color: #fff;\n"
"	border: 0;\n"
"	border-right: 1px solid #121212;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #00c853;\n"
"}"));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1200, 60));
        frame->setStyleSheet(QString::fromUtf8("border: 0;\n"
"background: #00e676;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        title = new QLabel(frame);
        title->setObjectName("title");
        title->setGeometry(QRect(0, 0, 200, 60));
        QFont font5;
        font5.setPointSize(24);
        font5.setBold(true);
        font5.setItalic(true);
        font5.setStrikeOut(false);
        font5.setKerning(true);
        title->setFont(font5);
        title->setStyleSheet(QString::fromUtf8("color: #fff;"));
        title->setAlignment(Qt::AlignmentFlag::AlignCenter);
        login = new QPushButton(frame);
        login->setObjectName("login");
        login->setGeometry(QRect(880, 10, 100, 40));
        QFont font6;
        font6.setPointSize(18);
        login->setFont(font6);
        login->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: #fff;\n"
"	border: 1px solid #fff;\n"
"	border-radius: 20px;\n"
"	padding-bottom: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: #121212;\n"
"	border: 1px solid #121212;\n"
"}"));
        login_status = new QLabel(frame);
        login_status->setObjectName("login_status");
        login_status->setGeometry(QRect(450, 0, 200, 60));
        QFont font7;
        font7.setPointSize(13);
        login_status->setFont(font7);
        login_status->setStyleSheet(QString::fromUtf8("color: #121212;"));
        login_status->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CR Connect", nullptr));
        msgbox->setPlaceholderText(QCoreApplication::translate("MainWindow", "  Enter the message", nullptr));
        sendBtn->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
        timedMsgBtn->setText(QCoreApplication::translate("MainWindow", "Timed", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Contacts", nullptr));
        addContactBtn->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        new_contact_bar->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter Name of Contact to Add", nullptr));
        rem_contact->setText(QCoreApplication::translate("MainWindow", "Remove\n"
"Contact", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "CR Connect", nullptr));
        login->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        login_status->setText(QCoreApplication::translate("MainWindow", "Logged in", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

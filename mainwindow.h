#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void updateChatbox(const QString &msg);

public slots:
    void onUpdateChatbox(const QString &msg);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void recv_message(SOCKET s, std::string msg);
    void send_message(SOCKET s, std::string name, std::string message);
    bool initialize();
    void on_sendBtn_clicked();
    void on_msgbox_returnPressed();
    void on_timedMsgBtn_clicked();
    void on_addContactBtn_clicked();
    void readFileAndAddContacts(const QString &filePath);
    void login(const QString &filePath);
    void on_contacts_itemClicked(QListWidgetItem *item);
    void on_login_clicked();



    void on_rem_contact_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *userLabel;
};
#endif // MAINWINDOW_H

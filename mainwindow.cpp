#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect.h"
#include "login.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <QFile>
#include <QString>
#include <string>
#include <QPropertyAnimation>

using namespace std;

#pragma comment(lib, "ws2_32.lib") //Links to the ws2_32.lib library

//Global Variables
QString serverAddr = "";
string serveraddrs;
string name;
string message;
string msg = "";
QString content = "";
QString prev_content = "";
SOCKET s;
bool connected = false;
string receiver_name;
int success = 1;


//Struct that is used for sending information to server
typedef struct
{
    SOCKET client;
    string username;
}dict;




//Function to run when Main Window starts
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Check if Winsock library is initialized correctly or not
    if (!initialize())
    {
        cout << "Initialization failed..." << endl;
    }
    cout << "Client program started..." << endl;


    //Creation of socket to be used by client
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
    {
        cout << "Invalid socket created" << endl;
        return;
    }

    //Window to be displayed that will get the address of the servr to connect to
    Connect dialogue(this);
    dialogue.exec();
    serveraddrs = dialogue.get_addr();

    //Port for connection
    int port = 12345;

    sockaddr_in serveraddr; //Struct that will store server address info

    serveraddr.sin_family = AF_INET; //Specifies the use of Ipv4 address
    serveraddr.sin_port = htons(port); //Sets the port
    inet_pton(AF_INET, serveraddrs.c_str(), &(serveraddr.sin_addr)); //Converts the address info to the usable binary form


    //Connecting to server
    if (::connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
    {
        cout << "Not able to connect to server. Error: " << WSAGetLastError() << endl;
        connected = false;
        closesocket(s);
        WSACleanup();
        return;
    };
    cout << "Socket: " << s << endl;
    cout << "Successfuly connected to server..." << endl;
    connected = true;


    //Starting a thread that will receive messages while the chat app runs
    std::thread receiverthread(bind(&MainWindow::recv_message, this, s, msg));


    //Login using previously saved login info
    login("info.txt");


    receiverthread.detach();

    //Read saved contacts and add them to the contacts bar
    readFileAndAddContacts("contacts.txt");
    ui->contacts->setStyleSheet(
        "QListWidget {border: 1px solid #00e676; padding: 0 40px;}"
        "QListWidget::item {color: #00e676;}"
        "QListWidget::item:hover {color: white; background-color: #00e676;}"
        "QListWidget::item:selected {color: white; background-color: #00e676; border: white;}"
        );




}


//Function to run when Main Window is closed
//This basically destroys the GUI elements and closes the socket that was created
MainWindow::~MainWindow()
{
    delete ui;
    closesocket(s);
    WSACleanup();

}



/*              Functions that are used in the Main Window function and other areas              */


//Initialize Winsock library to be used
bool MainWindow::initialize()
{
    WSADATA data;

    // Initialize Winsock library version 2.2
    // Returns true if the initialization is successful, otherwise false
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}




//Function to run that will add the message to the screen after it is received
void MainWindow::onUpdateChatbox(const QString &msg)
{
    int p = msg.indexOf(QChar(':'));
    int len = msg.length();

    if (msg.mid(0, p-1).toStdString() != name)
    {
        if (msg.contains("#.#"))
        {
            content += "<div style='text-align: right; color: #2D2D2D;'>" + name + " joined the chat..." + "</div>\n";
            ui->chatbox->setHtml(content);
            prev_content = content;
            send(s, name.c_str(), name.length(), 0);
            ui->login_status->setText("Logged in as: " + QString::fromStdString(name));
            return;
        }
        if(!msg.contains("TIME:"))
            content += "<div style='text-align: left; display: block; border: 2px; color: #E1E1E1; background-color: #3E3E3E; margin-bottom: 20px; margin_left: 25px; margin-right: " + QString::number(630 - len * 11) + "px;'>" + msg + "</div>\n";
        else
        {
            //Removing the time from the message if it is a timed message
            int time_pos = msg.indexOf("TIME: ");
            QString rem_msg = msg;
            rem_msg.remove(time_pos, 30);
            content += "<div style='text-align: left; display: block; border: 2px; color: #E1E1E1; background-color: #3E3E3E; margin-bottom: 20px; margin_left: 25px; margin-right: " + QString::number(630 - len * 11) + "px;'>" + rem_msg + "</div>\n";
        }
    }
    //if message received is from his/her own history so it will be displayed at right
    else
        content += "<div style='text-align: right; border: 2px; color: #E1E1E1; background-color: #2D2D2D; margin-bottom: 20px; margin_right: 25px; margin-left: " + QString::number(620 - len * 11) + "px;'>" + msg.mid(p+1, msg.length() - p+1) + "</div>\n";

    ui->chatbox->setHtml(content);

}


//Function to receive message
void MainWindow::recv_message(SOCKET s, string msg)
{
    char buffer[4096]; //Buffer that will store the message
    int recvlength; //Length of received message

    //Keep iterating infinitely till app is closed
    while (true)
    {
        recvlength = recv(s, buffer, sizeof(buffer), 0);

        if (recvlength <= 0)
        {
            cout << "Disconnected from the server..." << endl;
            // delete ui;
            break;
        }
        else
        {
            msg = string(buffer, recvlength);
            cout << msg << endl;
            QString qMsg = QString::fromStdString(msg);

            if (msg.find("#.#") != string::npos)
            {
                QMetaObject::invokeMethod(this, "onUpdateChatbox", Qt::QueuedConnection, Q_ARG(QString, qMsg));
            }
            else if (msg.find("Invalid password!") != string::npos)
            {
                QMetaObject::invokeMethod(this, [=]()
                                          {
                                              ui->login_status->setText("Logged in as: ");
                                              QMessageBox::warning(this, "Invalid Login", "Incorrect Password");
                                              on_login_clicked();
                                          }, Qt::QueuedConnection);
            }
            else if (msg.find("Invalid Login!") == string::npos)
            {
                //Call the function to display the message
                QMetaObject::invokeMethod(this, "onUpdateChatbox", Qt::QueuedConnection, Q_ARG(QString, qMsg));
            }
            else
            {
                QMetaObject::invokeMethod(this, [=]()
                {
                    ui->login_status->setText("Logged in as: ");
                    QMessageBox::warning(this, "Invalid Login", "Username already in use");
                    on_login_clicked();
                }, Qt::QueuedConnection);
            }
        }
    }

    //Close socket after loop ends (which will happen when user disconnects)
    closesocket(s);
    WSACleanup();


}


//Function to send messages
void MainWindow::send_message(SOCKET s, string name, string message)
{
    //Construct the message by adding the names of sender and receiver which will be processed by the server
    string msg = receiver_name + ":" + name + " : " + message;

    //Send the message
    int bytesent = send(s, msg.c_str(), msg.length(), 0);
    if (bytesent == SOCKET_ERROR)
    {
        cout << "Error sending message..." << endl;
        return;
    }


}


//Function that is called when sendBtn is pressed

/*
 * First we get the message written in the msgbox
 * Then we display this message on screen as it is sent
 * We empty the msgbox for next message
 * Finally we start a thread for sending messages
*/
void MainWindow::on_sendBtn_clicked()
{
    if (connected)
    {
        message = ui->msgbox->text().toStdString();
        cout << "Message: " << message << endl;
        int len = message.length();
        content += "<div style='text-align: right; border: 2px; color: #E1E1E1; background-color: #2D2D2D; margin-bottom: 20px; margin_right: 25px; margin-left: " + QString::number(620 - len * 11) + "px;'>" + QString::fromStdString(message) + "</div>\n";
        ui->chatbox->setHtml(content);
        ui->msgbox->setText("");
        std::thread senderthread(bind(&MainWindow::send_message, this, s, name, message));

        senderthread.detach();
    }
    else
    {
        content += "<div style='text-align: center; color: red;'>" + name + "Not connected to the server!" + "</div>\n";
        ui->chatbox->setHtml(content);
        ui->msgbox->setText("");
    }
}

//Same things to happen as above when ENTER is pressed by keyboard in msgbox
void MainWindow::on_msgbox_returnPressed()
{
    if (connected)
    {
        message = ui->msgbox->text().toStdString();
        cout << "Message: " << message << endl;
        int len = message.length();
        content += "<div style='text-align: right; border: 2px; color: #E1E1E1; background-color: #2D2D2D; margin-bottom: 20px; margin_right: 25px; margin-left: " + QString::number(620 - len * 11) + "px;'>" + QString::fromStdString(message) + "</div>\n";
        ui->chatbox->setHtml(content);
        ui->msgbox->setText("");
        std::thread senderthread(bind(&MainWindow::send_message, this, s, name, message));

        senderthread.detach();
    }
    else
    {
        content += "<div style='text-align: center; color: red;'>" + name + "Not connected to the server!" + "</div>\n";
        ui->chatbox->setHtml(content);
        ui->msgbox->setText("");
    }
}


//Function that reads a file and adds contacts
void MainWindow::readFileAndAddContacts(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        content += "No contact file found";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        // for (int i = 0; i < 250 - line.length() * 11; i++)
        //     line = " " + line;
        // QListWidgetItem* newcontact = new QListWidgetItem(line);
        ui->contacts->addItem(line);
    }
}


//Login function which reads name from info file and sets the username
void MainWindow::login(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        content += "No login file found";
        return;
    }

    QTextStream in(&file);
    name = in.readLine().toStdString();
    string password = in.readLine().toStdString();


    if (connected)
    {
        if (name != "") //Name must not be empty
        {

            content = "";
            cout << "Name: " << name << endl;


            string flagmsg = "LOGIN:" + name + " " + password;
            int bytesent = send(s, flagmsg.c_str(), flagmsg.length(), 0);
            if (bytesent == SOCKET_ERROR)
            {
                cout << "Error sending message..." << endl;
                return;
            }

        }
        else
        {
            content += "<div style='text-align: center; color: red;'>" + name + "Enter your username first..." + "</div>\n";
            ui->chatbox->setHtml(content);
        }
    }
    else
    {
        content += "<div style='text-align: center; color: red;'>" + name + "Not connected to the server!" + "</div>\n";
        ui->chatbox->setHtml(content);
    }


}



//Function to call for Timed Messages

/*
 * First it checks whether message is already typed
 * For that it stores whatever is currently typed in a var
 * Then it gets the current time + 30sec in a specific format and adds the specific words "TIME: {time}" before the message
 * This will serve as an identification to server for timed messages
 * Time can be adjusted by typing it after pressing time button
*/
void MainWindow::on_timedMsgBtn_clicked()
{
    QString msg = ui->msgbox->text();
    auto now = chrono::system_clock::now();
    now = now + chrono::seconds(30);
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm localTime;
    localtime_s(&localTime, &currentTime);

    // Adjust the buffer size to accommodate the full formatted string
    char timeString[100];
    strftime(timeString, sizeof(timeString), "TIME: %a %b %d %H:%M:%S %Y", &localTime);

    // Update the msgbox with the formatted time string
    ui->msgbox->setText(QString::fromStdString(timeString) + " " + msg);
}





//Function to run when any of the contacts is selected

/*
 * This gets the receiver name from the contact clicked
 * Then it sends the server a flag message with the receivers name that will tell server to send the previous chat of user with the receiver
 * Which is then displayed on the screen
*/
void MainWindow::on_contacts_itemClicked(QListWidgetItem *item)
{
    receiver_name = item->text().toStdString();
    cout << receiver_name << endl;
    string flag_msg = "chat:";
    content = "";
    content += "<div style='text-align: center; color: #00e676;'> Sending to " + receiver_name + "</div>\n";
    ui->chatbox->setHtml(content);
    send_message(s, name, flag_msg);


}


//Function to run when addContact is clicked
void MainWindow::on_addContactBtn_clicked()
{
    QString new_contact = ui->new_contact_bar->text();
    ui->contacts->addItem(new_contact);
    QFile file("contacts.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Unable to open file";
        return;
    }
    QTextStream out(&file);
    out << new_contact + "\n";
    file.close();
}


//Function to run when login button is pressed
void MainWindow::on_login_clicked()
{
    //Create a new window for login box to appear

    static bool loginInProgress = false;
    if (loginInProgress) return;
    loginInProgress = true;

    Login dialogue(this);
    dialogue.exec();

    //Calling log in function
    login("info.txt");
    loginInProgress = false;
}


void remove_text(QString filePath, QString text)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error: Unable to open file for reading";
        return;
    }
    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();
    fileContent.remove(text);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error: Unable to open file for writing";
        return;
    }
    QTextStream out(&file);
    out << fileContent;
    file.close();
}



void MainWindow::on_rem_contact_clicked()
{
    QListWidgetItem* curr_item = ui->contacts->currentItem();
    if (curr_item)
    {
        remove_text("contacts.txt", curr_item->text() + "\n");
        ui->contacts->removeItemWidget(curr_item);
        delete curr_item;
        ui->contacts->clearSelection();
        content = "";
        ui->chatbox->setHtml(content);
    }
    else
    {
        content += "<div style='text-align: center; color: red;'> No contact selected </div>\n";
        ui->chatbox->setHtml(content);
    }
}


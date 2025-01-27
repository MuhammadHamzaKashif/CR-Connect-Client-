#ifndef CONNECT_H
#define CONNECT_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <cstdlib>
#include <QStandardPaths>
#include <QFile>

using namespace std;
extern QString serverAddr;
class Connect : public QDialog {
    Q_OBJECT

public:
    explicit Connect(QWidget *parent = nullptr) : QDialog(parent)
    {
        //Adding widgets and stylesheets for the widgets
        QLabel *label = new QLabel("Server Address: ", this);

        inputField = new QLineEdit(this);
        inputField->setPlaceholderText("Enter Server ip Address");

        //Adding function to the Connect button
        QPushButton *connectBtn = new QPushButton("Connect", this);

        connect(connectBtn, &QPushButton::clicked, this, &Connect::onConnectClicked);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(inputField);
        layout->addWidget(connectBtn);

        setLayout(layout);

        setWindowTitle("Connect to Server");
        resize(400, 200);

        setStyleSheet("CustomDialog { background-color: #1E1E1E; }"
                      "QLabel { font-size: 16px; color: #4CAF50; }"
                      "QLineEdit { padding: 5px; font-size: 14px; border: 1px solid #E1E1E1; color:#E1E1E1; }"
                      "QPushButton { background-color: #4CAF50; color: #E1E1E1; padding: 10px; border: 1px solid #E1E1E1; }"
                      "QPushButton:hover { background-color: #45a049;}"
                      );
    }
    string get_addr()
    {
        return serverAddr.toStdString();
    }

private slots:
    //Sets server address
    void onConnectClicked()
    {
        QString a = inputField->text();

        if (!a.isEmpty()) {
            serverAddr = a;
            accept();
        } else {
            QMessageBox::warning(this, "Input Error", "Please enter a valid Username");
        }
    }

private:
    QLineEdit *inputField;
};

#endif

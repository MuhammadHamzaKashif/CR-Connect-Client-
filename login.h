#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <cstdlib>
#include <QStandardPaths>
#include <QFile>

class Login : public QDialog {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr) : QDialog(parent)
    {
        //Adding widgets and stylesheets for the widgets
        QLabel *label = new QLabel("Username: ", this);

        inputField = new QLineEdit(this);
        inputField->setPlaceholderText("Enter name");

        QLabel *label2 = new QLabel("Password: ", this);

        passwordField = new QLineEdit(this);
        passwordField->setPlaceholderText("Enter password");

        QPushButton *loginBtn = new QPushButton("Login", this);

        //Adding function to the Login button
        connect(loginBtn, &QPushButton::clicked, this, &Login::onLoginClicked);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(inputField);
        layout->addWidget(label2);
        layout->addWidget(passwordField);
        layout->addWidget(loginBtn);

        setLayout(layout);

        setWindowTitle("Login");
        resize(400, 200);

        setStyleSheet("CustomDialog { background-color: #1E1E1E; }"
                      "QLabel { font-size: 16px; color: #4CAF50; }"
                      "QLineEdit { padding: 5px; font-size: 14px; border: 1px solid #E1E1E1; color:#E1E1E1; }"
                      "QPushButton { background-color: #4CAF50; color: #E1E1E1; padding: 10px; border: 1px solid #E1E1E1; }"
                      "QPushButton:hover { background-color: #45a049;}"
                      );
    }

private slots:
    void onLoginClicked()
    {
        QString name = inputField->text();
        QString password = passwordField->text();
        //Changes logined username in the info file

        if (!name.isEmpty() && !password.isEmpty())
        {
            QFile file("info.txt");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug() << "Unable to open file";
                return;
            }
            QTextStream out(&file);
            out << name + "\n";
            out << password;
            file.close();
            accept();
        }
        else
        {
            QMessageBox::warning(this, "Input Error", "Please enter a valid Username");
        }
    }

private:
    QLineEdit *inputField;
    QLineEdit *passwordField;
};

#endif

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Style
    QString style = R"(
    QPushButton{
    color: #F5F5F5;
    background-color: blue;
    border: 2px solid #E1E1E1;
};
    QPushButton:hover{
    background-color: #45a049;
};
    QListWidgetItem{
    padding: 0 45px;
};
)";
    a.setStyleSheet(style);
    return a.exec();
}

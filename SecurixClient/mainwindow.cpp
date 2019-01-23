#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    QString hostname = ui->server_ip->toPlainText();
    quint16 port = ui->server_port->toPlainText().toUInt();
    QString username = ui->username->toPlainText();
    QString room = ui->room_name->toPlainText();

    network_manager.connectToSecureHost(hostname, port, username, room);
    network_manager.initUiFields(*ui->history, *ui->users);
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_sendBtn_clicked() {
    QString message = ui->message->toPlainText();
    network_manager.sendMessage(message);
    ui->message->clear();
}


void MainWindow::on_message_textChanged() {
    if (ui->message->toPlainText().size() >= 1 && ui->message->toPlainText()[ui->message->toPlainText().size() - 1] == '\n') {
        ui->message->textCursor().deletePreviousChar();
        this->on_sendBtn_clicked();
    }
}

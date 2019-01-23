#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "securenetworkmanager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_sendBtn_clicked();
    void on_message_textChanged();
private:
    Ui::MainWindow *ui;
    SecureNetworkManager network_manager;
};

#endif
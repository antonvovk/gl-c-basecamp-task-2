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
private:
    SecureNetworkManager network_manager;
    Ui::MainWindow *ui;
};

#endif

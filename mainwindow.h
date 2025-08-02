#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AdbClient.h"

class UniversalMethodHandler;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_DisableFTY_clicked();

private:
    Ui::MainWindow *ui;
    AdbClient adbHandler;
    UniversalMethodHandler *universalHandler = nullptr;
};

#endif // MAINWINDOW_H
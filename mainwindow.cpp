#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "universalmethodhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , adbHandler()
{
    ui->setupUi(this);
    
    // Initialize the universal method handler
    // Assuming your UI has ConsoleLogs (QPlainTextEdit) and progressBar
    universalHandler = new UniversalMethodHandler(
        &adbHandler,
        ui->ConsoleLogs,
        ui->progressBar,
        this,
        this
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DisableFTY_clicked()
{
    // Clear console logs like other handlers
    ui->ConsoleLogs->clear();
    
    // Run the universal method handler
    universalHandler->run();
}


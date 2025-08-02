#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class AdbClient;
class UniversalMethodHandler;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onUniversalMethodClicked();

private:
    // UI Components
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QPlainTextEdit *logTextEdit;
    QPushButton *universalMethodButton;
    QProgressBar *progressBar;
    QLabel *statusLabel;

    // Core components
    AdbClient *m_adbClient;
    UniversalMethodHandler *m_universalHandler;
    
    // Helper methods
    void setupUI();
};

#endif // MAINWINDOW_H
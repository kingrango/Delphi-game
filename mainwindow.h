#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QThread>
#include <QMutex>
#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QColor>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QDebug>

class AdbWorker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButton15Clicked();
    void onAdbCheckFinished(bool success);
    void onDeviceSearchFinished(bool found);
    void onApkInstallFinished(bool success);
    void onProcessFinished();

private:
    // UI Components
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QTextEdit *logTextEdit;
    QPushButton *button15;
    QProgressBar *progressBar;
    QLabel *statusLabel;

    // ADB related
    QProcess *adbProcess;
    QString adbDeviceSerial;
    QString dataFolderPath;
    
    // Helper methods
    void setupUI();
    void logs(const QString &message, const QColor &color = Qt::white);
    bool checkRunAdb();
    bool findAdbDevice();
    void waitForDevices();
    void installApk(const QString &apkFileName, const QString &command);
    void executeAdbCommand(const QString &command);
    QString getApplicationPath();
    void resetProgress();
    
    // Async operations
    void startAdbCheck();
    void startDeviceSearch();
    void startApkInstall();
    void startDeviceAdminSetup();
};

// Worker class for background operations
class AdbWorker : public QObject
{
    Q_OBJECT

public:
    enum OperationType {
        CheckAdb,
        SearchDevices,
        InstallApk,
        SetupAdmin
    };

public slots:
    void performOperation(OperationType type, const QString &param1 = "", const QString &param2 = "");

signals:
    void operationFinished(bool success, const QString &result = "");

private:
    QString executeCommand(const QString &command);
};

#endif // MAINWINDOW_H
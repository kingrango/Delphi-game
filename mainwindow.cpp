#include "mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(nullptr)
    , mainLayout(nullptr)
    , logTextEdit(nullptr)
    , button15(nullptr)
    , progressBar(nullptr)
    , statusLabel(nullptr)
    , adbProcess(nullptr)
{
    setupUI();
    dataFolderPath = getApplicationPath() + "/data";
}

MainWindow::~MainWindow()
{
    if (adbProcess) {
        adbProcess->kill();
        adbProcess->waitForFinished(3000);
    }
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    
    // Status label
    statusLabel = new QLabel("Ready", this);
    statusLabel->setStyleSheet("QLabel { font-weight: bold; }");
    mainLayout->addWidget(statusLabel);
    
    // Log text area
    logTextEdit = new QTextEdit(this);
    logTextEdit->setReadOnly(true);
    logTextEdit->setStyleSheet("QTextEdit { background-color: #2b2b2b; color: white; font-family: 'Courier New'; }");
    logTextEdit->setMinimumHeight(300);
    mainLayout->addWidget(logTextEdit);
    
    // Progress bar
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    mainLayout->addWidget(progressBar);
    
    // Button
    button15 = new QPushButton("Universal Method - Disable Factory Reset", this);
    button15->setStyleSheet("QPushButton { padding: 10px; font-size: 12px; font-weight: bold; }");
    connect(button15, &QPushButton::clicked, this, &MainWindow::onButton15Clicked);
    mainLayout->addWidget(button15);
    
    setWindowTitle("ADB Device Manager - Qt Version");
    setMinimumSize(600, 500);
    
    logs("Application started", Qt::green);
}

void MainWindow::logs(const QString &message, const QColor &color)
{
    QTextCursor cursor = logTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    
    QTextCharFormat format;
    format.setForeground(QBrush(color));
    cursor.setCharFormat(format);
    
    cursor.insertText(message);
    logTextEdit->setTextCursor(cursor);
    logTextEdit->ensureCursorVisible();
    
    QApplication::processEvents();
}

QString MainWindow::getApplicationPath()
{
    return QApplication::applicationDirPath();
}

void MainWindow::onButton15Clicked()
{
    button15->setEnabled(false);
    resetProgress();
    
    logs("\n\nChecking ADB Server..", QColor("#FFFAF0")); // FloralWhite
    QTimer::singleShot(100, this, &MainWindow::startAdbCheck);
}

void MainWindow::startAdbCheck()
{
    // Create worker thread for ADB check
    QThread *thread = new QThread;
    AdbWorker *worker = new AdbWorker;
    worker->moveToThread(thread);
    
    connect(thread, &QThread::started, [worker]() {
        worker->performOperation(AdbWorker::CheckAdb);
    });
    
    connect(worker, &AdbWorker::operationFinished, this, &MainWindow::onAdbCheckFinished);
    connect(worker, &AdbWorker::operationFinished, thread, &QThread::quit);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    
    thread->start();
}

void MainWindow::onAdbCheckFinished(bool success)
{
    if (!success) {
        waitForDevices();
        return;
    }
    
    logs(" Running\n", Qt::green);
    QTimer::singleShot(10, [this]() {
        logs("Searching devices..\n", QColor("#FFFAF0"));
        QTimer::singleShot(10, this, &MainWindow::startDeviceSearch);
    });
}

void MainWindow::startDeviceSearch()
{
    QThread *thread = new QThread;
    AdbWorker *worker = new AdbWorker;
    worker->moveToThread(thread);
    
    connect(thread, &QThread::started, [worker]() {
        worker->performOperation(AdbWorker::SearchDevices);
    });
    
    connect(worker, &AdbWorker::operationFinished, this, &MainWindow::onDeviceSearchFinished);
    connect(worker, &AdbWorker::operationFinished, thread, &QThread::quit);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    
    thread->start();
}

void MainWindow::onDeviceSearchFinished(bool found)
{
    if (!found) {
        logs("No devices found\n", Qt::red);
        button15->setEnabled(true);
        return;
    }
    
    QTimer::singleShot(10, [this]() {
        QMessageBox::information(this, "Info", "This Is Universal Method");
        logs("\n Wait a While\n", QColor("#FFD700")); // Gold
        progressBar->setValue(30);
        startApkInstall();
    });
}

void MainWindow::startApkInstall()
{
    QThread *thread = new QThread;
    AdbWorker *worker = new AdbWorker;
    worker->moveToThread(thread);
    
    connect(thread, &QThread::started, [worker]() {
        worker->performOperation(AdbWorker::InstallApk, "adm.apk", "install");
    });
    
    connect(worker, &AdbWorker::operationFinished, this, &MainWindow::onApkInstallFinished);
    connect(worker, &AdbWorker::operationFinished, thread, &QThread::quit);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    
    thread->start();
}

void MainWindow::onApkInstallFinished(bool success)
{
    QTimer::singleShot(2000, [this]() {
        logs("\n Disabling...", QColor("#FFFAF0"));
        progressBar->setValue(50);
        startDeviceAdminSetup();
    });
}

void MainWindow::startDeviceAdminSetup()
{
    QThread *thread = new QThread;
    AdbWorker *worker = new AdbWorker;
    worker->moveToThread(thread);
    
    connect(thread, &QThread::started, [worker]() {
        worker->performOperation(AdbWorker::SetupAdmin);
    });
    
    connect(worker, &AdbWorker::operationFinished, this, &MainWindow::onProcessFinished);
    connect(worker, &AdbWorker::operationFinished, thread, &QThread::quit);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    
    thread->start();
}

void MainWindow::onProcessFinished()
{
    QTimer::singleShot(1500, [this]() {
        logs("Ok\n", Qt::green);
        progressBar->setValue(100);
        logs("\n Successful Disabled", QColor("#FFD700"));
        
        QTimer::singleShot(2000, [this]() {
            progressBar->setValue(0);
            button15->setEnabled(true);
        });
    });
}

void MainWindow::waitForDevices()
{
    logs("Waiting for devices...\n", Qt::yellow);
    button15->setEnabled(true);
}

void MainWindow::resetProgress()
{
    progressBar->setValue(0);
}

bool MainWindow::checkRunAdb()
{
    QProcess process;
    process.start("adb", QStringList() << "version");
    process.waitForFinished(5000);
    return process.exitCode() == 0;
}

bool MainWindow::findAdbDevice()
{
    QProcess process;
    process.start("adb", QStringList() << "devices");
    process.waitForFinished(5000);
    
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n');
    
    for (const QString &line : lines) {
        if (line.contains('\t') && line.contains("device")) {
            adbDeviceSerial = line.split('\t').first();
            return true;
        }
    }
    return false;
}

void MainWindow::executeAdbCommand(const QString &command)
{
    QProcess process;
    QStringList args = command.split(' ');
    process.start("adb", args);
    process.waitForFinished(10000);
}

// AdbWorker implementation
QString AdbWorker::executeCommand(const QString &command)
{
    QProcess process;
    QStringList parts = command.split(' ');
    QString program = parts.takeFirst();
    
    process.start(program, parts);
    process.waitForFinished(10000);
    
    return process.readAllStandardOutput();
}

void AdbWorker::performOperation(OperationType type, const QString &param1, const QString &param2)
{
    bool success = false;
    QString result;
    
    try {
        switch (type) {
            case CheckAdb: {
                QProcess process;
                process.start("adb", QStringList() << "version");
                success = process.waitForFinished(5000) && process.exitCode() == 0;
                break;
            }
            
            case SearchDevices: {
                QProcess process;
                process.start("adb", QStringList() << "devices");
                if (process.waitForFinished(5000)) {
                    QString output = process.readAllStandardOutput();
                    success = output.contains("device") && !output.contains("List of devices attached\n\n");
                }
                break;
            }
            
            case InstallApk: {
                QString apkPath = QApplication::applicationDirPath() + "/data/" + param1;
                QProcess process;
                process.start("adb", QStringList() << param2 << apkPath);
                if (process.waitForFinished(30000)) {
                    QString output = process.readAllStandardOutput();
                    success = output.toLower().contains("success");
                    result = output;
                }
                break;
            }
            
            case SetupAdmin: {
                // Set device owner
                QProcess process1;
                process1.start("adb", QStringList() << "shell" << "dpm" << "set-device-owner" << "com.mdmfixtool.mdmfixtool/.DeviceAdmin");
                process1.waitForFinished(10000);
                
                QThread::msleep(500);
                
                // Start activity
                QProcess process2;
                process2.start("adb", QStringList() << "shell" << "am" << "start" << "--user" << "0" << "-n" << "com.mdmfixtool.mdmfixtool/.DisableFactoryReset");
                success = process2.waitForFinished(10000);
                break;
            }
        }
    }
    catch (...) {
        success = false;
    }
    
    emit operationFinished(success, result);
}

#include "mainwindow.moc"
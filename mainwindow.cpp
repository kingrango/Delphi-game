#include "mainwindow.h"
#include "universalmethodhandler.h"
#include "AdbClient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(nullptr)
    , mainLayout(nullptr)
    , logTextEdit(nullptr)
    , universalMethodButton(nullptr)
    , progressBar(nullptr)
    , statusLabel(nullptr)
    , m_adbClient(nullptr)
    , m_universalHandler(nullptr)
{
    setupUI();
    
    // Initialize ADB client
    m_adbClient = new AdbClient(this);
    
    // Initialize handlers
    m_universalHandler = new UniversalMethodHandler(m_adbClient, logTextEdit, progressBar, this, this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    
    // Status label
    statusLabel = new QLabel("KRDT Utility Pro - Ready", this);
    statusLabel->setStyleSheet("QLabel { font-weight: bold; color: #2E8B57; }");
    mainLayout->addWidget(statusLabel);
    
    // Log text area
    logTextEdit = new QPlainTextEdit(this);
    logTextEdit->setReadOnly(true);
    logTextEdit->setStyleSheet("QPlainTextEdit { background-color: #2b2b2b; color: white; font-family: 'Courier New'; }");
    logTextEdit->setMinimumHeight(300);
    logTextEdit->appendPlainText("Application started - Ready for operations");
    mainLayout->addWidget(logTextEdit);
    
    // Progress bar
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    mainLayout->addWidget(progressBar);
    
    // Universal Method Button
    universalMethodButton = new QPushButton("Universal Method - Disable Factory Reset", this);
    universalMethodButton->setStyleSheet("QPushButton { padding: 10px; font-size: 12px; font-weight: bold; background-color: #4CAF50; color: white; }");
    connect(universalMethodButton, &QPushButton::clicked, this, &MainWindow::onUniversalMethodClicked);
    mainLayout->addWidget(universalMethodButton);
    
    setWindowTitle("KRDT Utility Pro - ADB Device Manager");
    setMinimumSize(600, 500);
}

void MainWindow::onUniversalMethodClicked()
{
    universalMethodButton->setEnabled(false);
    
    // Run the universal method handler
    m_universalHandler->run();
    
    // Re-enable button after completion
    universalMethodButton->setEnabled(true);
}


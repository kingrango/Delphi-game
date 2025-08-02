#include "universalmethodhandler.h"
#include "AdbClient.h"
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QTimer>
#include <QMessageBox>
#include <QCoreApplication>

UniversalMethodHandler::UniversalMethodHandler(AdbClient* adb, QPlainTextEdit* logs, QProgressBar* progress, QWidget* parentWidget, QObject* parent)
    : QObject(parent), m_adb(adb), m_logs(logs), m_progress(progress), m_parentWidget(parentWidget), m_step(0)
{
}

void UniversalMethodHandler::run()
{
    if (QMessageBox::question(m_parentWidget, "KRDT Utility Pro", "Do You Want To Continue\nThis Is Universal Method?") != QMessageBox::Yes) {
        m_logs->appendPlainText("Operation Cancelled by User");
        return;
    }
    
    m_logs->clear();
    m_logs->appendPlainText("Operation: Universal Method - Disable Factory Reset");
    m_step = StepCheckAdb;
    QTimer::singleShot(100, this, &UniversalMethodHandler::nextStep);
}

void UniversalMethodHandler::nextStep()
{
    switch (m_step) {
    case StepCheckAdb:
        logMessage("Checking ADB Server..");
        if (m_progress) m_progress->setValue(10);
        
        // Check if ADB is running
        if (!m_adb->isAdbRunning()) {
            m_logs->appendPlainText("ADB Server not running - Please start ADB");
            if (m_progress) m_progress->setValue(0);
            return;
        }
        
        logMessage(" Running");
        m_step = StepSearchDevices;
        QTimer::singleShot(100, this, &UniversalMethodHandler::nextStep);
        break;
        
    case StepSearchDevices:
        logMessage("Searching devices..");
        if (m_progress) m_progress->setValue(20);
        
        // Check for connected devices
        if (!m_adb->hasConnectedDevices()) {
            m_logs->appendPlainText("No devices found");
            if (m_progress) m_progress->setValue(0);
            return;
        }
        
        logMessage(" Found");
        m_step = StepDeviceInfo;
        QTimer::singleShot(10, this, &UniversalMethodHandler::nextStep);
        break;
        
    case StepDeviceInfo: {
        auto info = m_adb->readFullPhoneInfo();
        if (!info.valid) {
            m_logs->appendPlainText("Device not found or unauthorized");
            if (m_progress) m_progress->setValue(0);
            return;
        }
        
        m_logs->appendPlainText("Device Info:");
        m_logs->appendPlainText("Model --- " + info.model);
        m_logs->appendPlainText("Brand --- " + info.brand);
        m_logs->appendPlainText("Android Version --- " + info.androidVersion);
        
        if (m_progress) m_progress->setValue(25);
        m_step = StepShowMessage;
        QTimer::singleShot(10, this, &UniversalMethodHandler::nextStep);
        break;
    }
    
    case StepShowMessage:
        QMessageBox::information(m_parentWidget, "KRDT Utility Pro", "This Is Universal Method");
        logMessage("Wait a While");
        if (m_progress) m_progress->setValue(30);
        m_step = StepInstallApk;
        QTimer::singleShot(100, this, &UniversalMethodHandler::nextStep);
        break;
        
    case StepInstallApk: {
        logMessage("Deploying Data: ");
        
        QString baseDir = QCoreApplication::applicationDirPath();
        QString apkPath = baseDir + "/data/adm.apk";
        bool apkOk = m_adb->installApkDirect(apkPath);
        
        if (apkOk) {
            logMessage("Success");
        } else {
            logMessage("Failed");
            if (m_progress) m_progress->setValue(0);
            return;
        }
        
        if (m_progress) m_progress->setValue(40);
        m_step = StepWaitInstall;
        QTimer::singleShot(2000, this, &UniversalMethodHandler::nextStep);
        break;
    }
    
    case StepWaitInstall:
        m_step = StepDisabling;
        QTimer::singleShot(100, this, &UniversalMethodHandler::nextStep);
        break;
        
    case StepDisabling:
        logMessage("Disabling...");
        if (m_progress) m_progress->setValue(50);
        m_step = StepSetDeviceOwner;
        QTimer::singleShot(500, this, &UniversalMethodHandler::nextStep);
        break;
        
    case StepSetDeviceOwner:
        // Set device owner
        m_adb->executeShellCommand("dpm set-device-owner \"com.mdmfixtool.mdmfixtool/.DeviceAdmin\"");
        m_logs->appendPlainText("Set device owner");
        
        if (m_progress) m_progress->setValue(70);
        m_step = StepStartActivity;
        QTimer::singleShot(500, this, &UniversalMethodHandler::nextStep);
        break;
        
    case StepStartActivity:
        // Start disable factory reset activity
        m_adb->executeShellCommand("am start --user 0 -n com.mdmfixtool.mdmfixtool/.DisableFactoryReset");
        m_logs->appendPlainText("Started disable activity");
        
        if (m_progress) m_progress->setValue(90);
        m_step = StepCompleted;
        QTimer::singleShot(1500, this, &UniversalMethodHandler::nextStep);
        break;
        
    case StepCompleted:
        logMessage("Ok");
        if (m_progress) m_progress->setValue(100);
        logMessage("Successful Disabled");
        
        m_step = StepDone;
        QTimer::singleShot(2000, this, &UniversalMethodHandler::nextStep);
        break;
        
    case StepDone:
        if (m_progress) m_progress->setValue(0);
        m_logs->appendPlainText("Operation --- Completed");
        break;
    }
}

void UniversalMethodHandler::logMessage(const QString& message)
{
    m_logs->appendPlainText(message);
}
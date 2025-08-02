#include "AdbClient.h"
#include <QDebug>
#include <QFileInfo>

AdbClient::AdbClient(QObject *parent)
    : QObject(parent)
{
}

bool AdbClient::isAdbRunning()
{
    QProcess process;
    process.start("adb", QStringList() << "version");
    bool finished = process.waitForFinished(5000);
    return finished && process.exitCode() == 0;
}

bool AdbClient::hasConnectedDevices()
{
    QString output = executeAdbCommand(QStringList() << "devices");
    QStringList lines = output.split('\n');
    
    for (const QString &line : lines) {
        if (line.contains('\t') && line.contains("device")) {
            return true;
        }
    }
    return false;
}

QString AdbClient::executeShellCommand(const QString &command)
{
    QStringList args;
    args << "shell" << command;
    return executeAdbCommand(args);
}

bool AdbClient::installApkDirect(const QString &apkPath)
{
    // Check if APK file exists
    QFileInfo fileInfo(apkPath);
    if (!fileInfo.exists()) {
        qDebug() << "APK file does not exist:" << apkPath;
        return false;
    }
    
    QString output = executeAdbCommand(QStringList() << "install" << apkPath);
    return output.toLower().contains("success");
}

PhoneInfo AdbClient::readFullPhoneInfo()
{
    PhoneInfo info;
    
    // Check if device is connected
    if (!hasConnectedDevices()) {
        return info;
    }
    
    info.model = getDeviceProperty("ro.product.model").trimmed();
    info.brand = getDeviceProperty("ro.product.brand").trimmed();
    info.version = getDeviceProperty("ro.build.version.release").trimmed();
    info.buildDate = getDeviceProperty("ro.build.date").trimmed();
    info.securityPatch = getDeviceProperty("ro.build.version.security_patch").trimmed();
    info.androidVersion = getDeviceProperty("ro.build.version.release").trimmed();
    
    // Mark as valid if we got at least the model
    info.valid = !info.model.isEmpty();
    
    return info;
}

QString AdbClient::executeAdbCommand(const QStringList &args)
{
    QProcess process;
    process.start("adb", args);
    
    if (!process.waitForFinished(10000)) {
        qDebug() << "ADB command timed out:" << args.join(" ");
        return QString();
    }
    
    if (process.exitCode() != 0) {
        QString error = process.readAllStandardError();
        if (!error.isEmpty()) {
            qDebug() << "ADB command error:" << error;
        }
    }
    
    return process.readAllStandardOutput();
}

QString AdbClient::getDeviceProperty(const QString &property)
{
    return executeShellCommand("getprop " + property);
}
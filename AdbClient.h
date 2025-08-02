#ifndef ADBCLIENT_H
#define ADBCLIENT_H

#include <QObject>
#include <QString>
#include <QProcess>

struct PhoneInfo {
    bool valid = false;
    QString model;
    QString brand;
    QString version;
    QString buildDate;
    QString securityPatch;
    QString androidVersion;
};

class AdbClient : public QObject
{
    Q_OBJECT

public:
    explicit AdbClient(QObject *parent = nullptr);
    
    // ADB operations
    bool isAdbRunning();
    bool hasConnectedDevices();
    QString executeShellCommand(const QString &command);
    bool installApkDirect(const QString &apkPath);
    PhoneInfo readFullPhoneInfo();

private:
    QString executeAdbCommand(const QStringList &args);
    QString getDeviceProperty(const QString &property);
};

#endif // ADBCLIENT_H
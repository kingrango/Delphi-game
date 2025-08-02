#ifndef UNIVERSALMETHODHANDLER_H
#define UNIVERSALMETHODHANDLER_H

#include <QObject>
#include <QStringList>

class AdbClient;
class QPlainTextEdit;
class QProgressBar;
class QWidget;

class UniversalMethodHandler : public QObject
{
    Q_OBJECT

public:
    explicit UniversalMethodHandler(AdbClient* adb, QPlainTextEdit* logs, QProgressBar* progress, QWidget* parentWidget, QObject* parent = nullptr);

    void run();

private slots:
    void nextStep();

private:
    enum Step {
        StepCheckAdb,
        StepSearchDevices,
        StepDeviceInfo,
        StepShowMessage,
        StepInstallApk,
        StepWaitInstall,
        StepDisabling,
        StepSetDeviceOwner,
        StepStartActivity,
        StepCompleted,
        StepDone
    };

    AdbClient* m_adb;
    QPlainTextEdit* m_logs;
    QProgressBar* m_progress;
    QWidget* m_parentWidget;
    int m_step;

    void logMessage(const QString& message);
};

#endif // UNIVERSALMETHODHANDLER_H
#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QPlainTextEdit *ConsoleLogs;
    QProgressBar *progressBar;
    QPushButton *DisableFTY;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setText("KRDT Utility Pro - Universal Method");
        titleLabel->setStyleSheet("QLabel { font-weight: bold; color: #2E8B57; font-size: 14px; }");
        titleLabel->setAlignment(Qt::AlignCenter);
        verticalLayout->addWidget(titleLabel);
        
        ConsoleLogs = new QPlainTextEdit(centralwidget);
        ConsoleLogs->setObjectName(QString::fromUtf8("ConsoleLogs"));
        ConsoleLogs->setReadOnly(true);
        ConsoleLogs->setStyleSheet("QPlainTextEdit { background-color: #2b2b2b; color: white; font-family: 'Courier New'; }");
        ConsoleLogs->setMinimumHeight(350);
        verticalLayout->addWidget(ConsoleLogs);
        
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setRange(0, 100);
        progressBar->setValue(0);
        verticalLayout->addWidget(progressBar);
        
        DisableFTY = new QPushButton(centralwidget);
        DisableFTY->setObjectName(QString::fromUtf8("DisableFTY"));
        DisableFTY->setText("Universal Method - Disable Factory Reset");
        DisableFTY->setStyleSheet("QPushButton { padding: 10px; font-size: 12px; font-weight: bold; background-color: #4CAF50; color: white; }");
        DisableFTY->setMinimumHeight(40);
        verticalLayout->addWidget(DisableFTY);
        
        MainWindow->setCentralWidget(centralwidget);
        MainWindow->setWindowTitle("KRDT Utility Pro - Universal Method");

        QMetaObject::connectSlotsByName(MainWindow);
    }
};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
}

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
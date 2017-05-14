/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *txtEditor;
    QPushButton *bConnect;
    QPushButton *bDisconncet;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(372, 293);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        txtEditor = new QPlainTextEdit(centralWidget);
        txtEditor->setObjectName(QStringLiteral("txtEditor"));
        txtEditor->setGeometry(QRect(0, 30, 371, 251));
        bConnect = new QPushButton(centralWidget);
        bConnect->setObjectName(QStringLiteral("bConnect"));
        bConnect->setGeometry(QRect(0, 0, 191, 23));
        bDisconncet = new QPushButton(centralWidget);
        bDisconncet->setObjectName(QStringLiteral("bDisconncet"));
        bDisconncet->setGeometry(QRect(190, 0, 181, 23));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Editor client", 0));
        bConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        bDisconncet->setText(QApplication::translate("MainWindow", "Disconnect", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qfi/qfi_AI.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblX;
    QLabel *lblY;
    QLabel *lblZ;
    qfi_AI *AI;
    QTextEdit *txtStatus;
    QPushButton *btnRead;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(713, 815);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblX = new QLabel(centralwidget);
        lblX->setObjectName(QString::fromUtf8("lblX"));
        QFont font;
        font.setPointSize(24);
        lblX->setFont(font);

        verticalLayout->addWidget(lblX);

        lblY = new QLabel(centralwidget);
        lblY->setObjectName(QString::fromUtf8("lblY"));
        lblY->setFont(font);

        verticalLayout->addWidget(lblY);

        lblZ = new QLabel(centralwidget);
        lblZ->setObjectName(QString::fromUtf8("lblZ"));
        lblZ->setFont(font);

        verticalLayout->addWidget(lblZ);

        AI = new qfi_AI(centralwidget);
        AI->setObjectName(QString::fromUtf8("AI"));

        verticalLayout->addWidget(AI);

        txtStatus = new QTextEdit(centralwidget);
        txtStatus->setObjectName(QString::fromUtf8("txtStatus"));

        verticalLayout->addWidget(txtStatus);

        btnRead = new QPushButton(centralwidget);
        btnRead->setObjectName(QString::fromUtf8("btnRead"));

        verticalLayout->addWidget(btnRead);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 713, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblX->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        lblY->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        lblZ->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        txtStatus->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        btnRead->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

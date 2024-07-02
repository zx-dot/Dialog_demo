/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *errorBtn;
    QPushButton *warningBtn;
    QPushButton *infoBtn;
    QPushButton *mutilMessageBtn;
    QPushButton *waittingBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        QFont font;
        font.setPointSize(18);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        errorBtn = new QPushButton(centralwidget);
        errorBtn->setObjectName("errorBtn");
        errorBtn->setGeometry(QRect(380, 310, 161, 91));
        errorBtn->setFont(font);
        warningBtn = new QPushButton(centralwidget);
        warningBtn->setObjectName("warningBtn");
        warningBtn->setGeometry(QRect(590, 310, 161, 91));
        warningBtn->setFont(font);
        infoBtn = new QPushButton(centralwidget);
        infoBtn->setObjectName("infoBtn");
        infoBtn->setGeometry(QRect(770, 310, 161, 91));
        infoBtn->setFont(font);
        mutilMessageBtn = new QPushButton(centralwidget);
        mutilMessageBtn->setObjectName("mutilMessageBtn");
        mutilMessageBtn->setGeometry(QRect(970, 310, 181, 91));
        mutilMessageBtn->setFont(font);
        waittingBtn = new QPushButton(centralwidget);
        waittingBtn->setObjectName("waittingBtn");
        waittingBtn->setGeometry(QRect(1180, 310, 181, 91));
        waittingBtn->setFont(font);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        errorBtn->setText(QCoreApplication::translate("MainWindow", "\351\224\231\350\257\257\344\277\241\346\201\257", nullptr));
        warningBtn->setText(QCoreApplication::translate("MainWindow", "\350\255\246\345\221\212\344\277\241\346\201\257", nullptr));
        infoBtn->setText(QCoreApplication::translate("MainWindow", "\346\217\220\347\244\272\344\277\241\346\201\257", nullptr));
        mutilMessageBtn->setText(QCoreApplication::translate("MainWindow", "\345\244\232\346\235\241\346\230\276\347\244\272", nullptr));
        waittingBtn->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\347\255\211\345\276\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dialog;
    delete dialog1;
}

void MainWindow::on_errorBtn_clicked()
{


    dialog = new MessageDialog(MessageType::Error,"This is an error message");
    dialog->exec();


}




void MainWindow::on_warningBtn_clicked()
{
    dialog = new MessageDialog(MessageType::Warning,"This is an Warning message");
    dialog->show();
}


void MainWindow::on_infoBtn_clicked()
{
    dialog = new MessageDialog(MessageType::Information,"This is an Information message");
    dialog->show();
}


void MainWindow::on_mutilMessageBtn_clicked()
{
    dialog = new MessageDialog(MessageType::Information,"This is an Information message");
    dialog->show();
    dialog1 = new MessageDialog(MessageType::Warning,"This is an Warning message");
    dialog1->show();
    dialog2 = new MessageDialog(MessageType::Error,"This is an error message");
    dialog2->show();
}




void MainWindow::on_waittingBtn_clicked()
{
    waiting =new WaitingDialog();
    waiting->show();
    QTimer::singleShot(5000, waiting,&WaitingDialog::close);

//    QTimer closeWaitTimer;
//    closeWaitTimer.setSingleShot(true);
//    connect(closeWaitTimer, &QTimer::timeout, waiting, &WaitingDialog::close);
//    closeWaitTimer.start(1000); // 1 seconds timeout for Information messages
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    dialog->close();
    QMainWindow::closeEvent(event);
}


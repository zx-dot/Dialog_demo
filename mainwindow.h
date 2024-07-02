#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MessageDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_errorBtn_clicked();

    void on_mutilMessageBtn_clicked();

    void on_warningBtn_clicked();

    void on_infoBtn_clicked();

    void on_waittingBtn_clicked();

private:
    Ui::MainWindow *ui;
    MessageDialog *dialog;
    MessageDialog *dialog1;
    MessageDialog *dialog2;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H

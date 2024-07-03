//
// Created by otronic on 2024/7/2.
//采用工厂模式进行设计该等待弹窗：LoadingAnimBase作为加载动画的基类，动画类：SlinkyCircle，之后使用WaitingDialog的作为接口类

#ifndef DIALOG_TEST2_WAITTINGDIALOG_H
#define DIALOG_TEST2_WAITTINGDIALOG_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QDialog>

class LoadingAnimBase : public QWidget {
    Q_OBJECT
    Q_PROPERTY(qreal angle READ angle WRITE setAngle)
public:
    LoadingAnimBase(QWidget *parent = nullptr);

    virtual ~LoadingAnimBase();

    qreal angle() const;

    void setAngle(qreal an);

public slots:

    virtual void exec();

    virtual void start();

    virtual void stop();

protected:
    QPropertyAnimation mAnim;
    qreal mAngle;
};

class SlinkyCircle : public LoadingAnimBase {
    //可以伸缩的管子,绕着中心转动,就像弹簧圈,英语叫做slinky,查了好久才查到这个单词,有点强迫症😂
    Q_OBJECT
public:
    explicit SlinkyCircle(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
};


class WaitingDialog : public SlinkyCircle {
Q_OBJECT
public:
    explicit WaitingDialog(QWidget *parent = nullptr);
};


#endif //DIALOG_TEST2_WAITTINGDIALOG_H

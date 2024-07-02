//
// Created by otronic on 2024/7/2.
//

#ifndef DIALOG_TEST2_WAITTINGDIALOG_H
#define DIALOG_TEST2_WAITTINGDIALOG_H

#include <QPropertyAnimation>
#include <QWidget>

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



#endif //DIALOG_TEST2_WAITTINGDIALOG_H

//
// Created by otronic on 2024/7/2.
//

#include "WaitingDialog.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>


LoadingAnimBase::LoadingAnimBase(QWidget *parent) : QWidget(parent) {
    mAnim.setPropertyName("angle");
    mAnim.setTargetObject(this);
    mAnim.setDuration(2000);
    mAnim.setLoopCount(-1);//run forever
    mAnim.setEasingCurve(QEasingCurve::Linear);
    setFixedSize(200, 200);
    mAngle = 0;
}

LoadingAnimBase::~LoadingAnimBase() {}

void LoadingAnimBase::exec() {
    if (mAnim.state() == QAbstractAnimation::Stopped) {
        start();
    } else {
        stop();
    }
}

void LoadingAnimBase::start() {
    mAnim.setStartValue(0);
    mAnim.setEndValue(360);
    mAnim.start();
}

void LoadingAnimBase::stop() {
    mAnim.stop();
}

qreal LoadingAnimBase::angle() const { return mAngle; }

void LoadingAnimBase::setAngle(qreal an) {
    mAngle = an;
    update();
}

SlinkyCircle::SlinkyCircle(QWidget *parent) : LoadingAnimBase(parent) {
    mAnim.setEasingCurve(QEasingCurve::InOutCubic);
}

void SlinkyCircle::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    //画圆弧
    painter.setBrush(Qt::NoBrush);
    const int x = this->width();
    const int y = this->height();
    QPen pen("#008CD6");//
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(x / 20);
    painter.setPen(pen);

    painter.translate(x / 2, y / 2);

    static const qreal spanAngle = 90;//mAngle<=45,要把弧线拉伸出来
    static const qreal shrinkAngle = 360 - spanAngle;//mAngle==315时,要把弧线收缩起来

    auto arcRect = this->rect().adjusted(x / 5, y / 5, -x / 5, -y / 5);
    arcRect.translate(-x / 2, -y / 2);

    static const int direction = -1;//顺时针

    if (mAngle < spanAngle) {
        painter.drawArc(arcRect, 90 * 16, mAngle * 16 * direction);
    } else {//弧长是固定的
        //40 - 320 --> 320 , 280 --> 320
        if (mAngle > shrinkAngle) {
            painter.drawArc(arcRect, 90 * 16, -(360 - mAngle) * 16 * direction);
        } else {
            //我转动的角度是当前角度 - 拉伸门槛,因为有收尾的不动的时间段,占据了一段角度,所以要把转动的角度拉伸一些,
            //这个比例就是 (360-spanAngle) / (shrinkAngle - spanAngle)
            const auto delta = (mAngle - spanAngle) * (360 - spanAngle) / (shrinkAngle - spanAngle);
            painter.rotate(-delta * direction);
            painter.drawArc(arcRect, 90 * 16, spanAngle * 16 * direction);
        }
    }

}


WaitingDialog::WaitingDialog(QWidget *parent)
        : SlinkyCircle(parent)
{
    setAttribute(Qt::WA_TranslucentBackground); // 设置窗口背景透明
    //设置Widget为模态，隐藏窗口边框，将窗口设置在最顶层
    setWindowFlags(Qt::Tool |Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint|Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_ShowModal,true);
    setFixedSize(200, 200);             // 设置窗口固定大小
    start();
}





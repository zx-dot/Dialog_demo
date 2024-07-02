#include "MessageDialog.h"
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QPaintEvent>
#include <QPainter>
// #include <QPainter>
// #include <QtConcurrent>
// #include <QFutureWatcher>

int MessageDialog::stackCount = 0;

MessageDialog::MessageDialog(MessageType type, const QString &message, QWidget *parent)
    : QDialog(parent)
    ,messageType(type)
{
    initUI(message);
    setupAnimation();


    // Initialize close timer for Information messages
    if (messageType == MessageType::Information) {
        closeTimer = new QTimer(this);
        closeTimer->setSingleShot(true);
        connect(closeTimer, &QTimer::timeout, this, &MessageDialog::closeDialog);
        closeTimer->start(1000); // 1 seconds timeout for Information messages
    }
    // else if(messageType == MessageType::Waitting) {
    //         QFutureWatcher<void> *watcher = new QFutureWatcher<void>();
    //         connect(watcher, &QFutureWatcher<void>::finished, this, &MessageDialog::closeDialog);

    //         // Start the loading task in a separate thread
    //         QFuture<void> future = QtConcurrent::run([=]() {
    //             // Simulate a long-running task
    //             QThread::sleep(5); // Replace with actual loading task

    //             // Notify the watcher that the task is finished
    //             watcher->finish();
    //         });

    //         watcher->setFuture(future);
    //     }

}


MessageDialog::~MessageDialog()
{
    MessageDialog::stackCount =0;

}

void MessageDialog::initUI(const QString &message) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    // stackCount = 0;

    QHBoxLayout *layout = new QHBoxLayout();
    label = new QLabel();
    lblIcon =new QLabel();

    layout ->addWidget(lblIcon);
    layout->addWidget(label);
    layout->setSpacing(0);//将QHBoxLayout中控件的距离设置为0
    setLayout(layout);

    QPixmap errorPixmap(":/icons/Cancel.png");
    QPixmap warningPixmap(":/icons/Warning.png");
    QPixmap infoPixmap(":/icons/Info.png");



    switch (messageType) {
    case MessageType::Error:

        //设置图标
        lblIcon->setPixmap(errorPixmap);
        lblIcon->setFixedSize(100,errorPixmap.height());
        lblIcon->setStyleSheet("background-color: rgba(244,67,54,0.75);"
                             " border: 0px solid white;"
                             " border-top-left-radius: 15px;"
                             " border-bottom-left-radius: 15px;"
                             " padding-left: 40px;");

        //设置文字
        label->setStyleSheet("background-color: rgba(244,67,54,0.75);"
                             " border: 0px solid white;"
                             " border-top-right-radius: 15px;"
                             " border-bottom-right-radius: 15px;"
                             "color : white;"
                             "font-size: 22px;");

        label->setText("错误："+message);
        label->setAlignment(Qt::AlignCenter);//使文字居中显示
        break;

    case MessageType::Warning:

        lblIcon->setPixmap(warningPixmap);
        lblIcon->setFixedSize(100,warningPixmap.height());
        lblIcon->setStyleSheet("background-color: rgba(245,186,61,0.75);"
                               " border: 0px solid white;"
                               " border-top-left-radius: 15px;"
                               " border-bottom-left-radius: 15px;"
                               " padding-left: 40px;");

        label->setStyleSheet("background-color: rgba(245,186,61,0.75);"
                             " border: 0px solid white;"
                             " border-top-right-radius: 15px;"
                             " border-bottom-right-radius: 15px;"
                             "color : white;"
                             "font-size: 22px;");
        label->setText("警告："+message);
        label->setAlignment(Qt::AlignCenter);//使文字居中显示

        break;
    case MessageType::Information:
        //设置图标
        lblIcon->setPixmap(infoPixmap);
        lblIcon->setFixedSize(100,infoPixmap.height());
        lblIcon->setStyleSheet("background-color: rgba(33,150,243,0.75);"
                               " border: 0px solid white;"
                               " border-top-left-radius: 15px;"
                               " border-bottom-left-radius: 15px;"
                               " padding-left: 40px;");

        //设置文字
        label->setStyleSheet("background-color: rgba(33,150,243,0.75);"
                             " border: 0px solid white;"
                             " border-top-right-radius: 15px;"
                             " border-bottom-right-radius: 15px;"
                             "color : white;"
                             "font-size: 22px;");
        label->setText("提示："+message);
        label->setAlignment(Qt::AlignCenter);//使文字居中显示
        break;
//    case MessageType::Waitting:
//        QDialog dialog;
//       dialog.setModal(true); // 设置为模态对话框，阻塞主窗口的输入
//            // 创建加载动画组件
//        SlinkyCircle *loadingAnim = new SlinkyCircle(&dialog);
//        loadingAnim->start();
//            // 设置对话框布局
//        QVBoxLayout dialogLayout(&dialog);
//        dialogLayout.addWidget(loadingAnim);
//        break;
    default:
        break;
    }


    QRect screen = QGuiApplication::primaryScreen()->geometry();
    int dialogWidth = 1186;
    int dialogHeight = 60;
    int x = (screen.width() - dialogWidth) / 2;
    int y = screen.height() ;

    y -= (dialogHeight + 5) * MessageDialog::stackCount;

    setGeometry(x, y, dialogWidth, dialogHeight);
    qDebug() << "Screen Height:" << screen.height();
    // qDebug() << "Status Bar Height:" << statusBarHeight; // 输出状态栏高度的值
    qDebug() << "Dialog Position (x, y):" << x << "," << y; //
    qDebug()<< "stackCount" << MessageDialog::stackCount;
}

void MessageDialog::setupAnimation() {
    QRect screen = QGuiApplication::primaryScreen()->geometry();
    int endY = screen.height() - (height() * (MessageDialog::stackCount + 1)) - 5 * MessageDialog::stackCount - 60;

    animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(x(), screen.height(), width(), height()));
    animation->setEndValue(QRect(x(), endY, width(), height()));
    animation->start();
    MessageDialog::stackCount++;
}

void MessageDialog::closeDialog() {
    animation->setDirection(QPropertyAnimation::Backward);
    connect(animation, &QPropertyAnimation::finished, this, &QDialog::close);
    // connect(animation, &QPropertyAnimation::finished, this, &QDialog::accept);
    animation->start();
    MessageDialog::stackCount--;
}

void MessageDialog::mousePressEvent(QMouseEvent *event)
{
    if (messageType == MessageType::Error || messageType == MessageType::Warning) {
        // Close dialog on click for Error and Warning messages
        // accept();
        close();
        MessageDialog::stackCount--;
    }
    QDialog::mousePressEvent(event);
}


//添加了加载动画的部分
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

WaittingDialog::WaittingDialog(QWidget *parent) : LoadingAnimBase(parent) {
    mAnim.setEasingCurve(QEasingCurve::InOutCubic);
}

void WaittingDialog::paintEvent(QPaintEvent *event) {
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

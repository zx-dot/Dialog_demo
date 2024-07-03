#include "MessageDialog.h"
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QPaintEvent>
#include <QPainter>


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



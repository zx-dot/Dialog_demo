//通过QDialog设计消息弹窗，需求：弹窗从界面底部从下往上弹出；三个消息弹窗出现时，进行堆叠弹出；
// error,warning弹窗单击弹窗关闭；information弹窗定时自动关闭
//可以根据error、warning和information三种不同的消息类型，显示不同颜色的消息弹窗和文字
//根据不同消息的内容，可以选择不同的弹窗模态，exec()模态；show()非模态


#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMouseEvent>
#include <QWidget>

enum class MessageType {
    Error,
    Warning,
    Information,
//    Waitting
};

class MessageDialog : public QDialog {
    Q_OBJECT

public:
    explicit MessageDialog(MessageType type,const QString &message,  QWidget *parent = nullptr);
    ~MessageDialog();
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *label;
    QLabel *lblIcon;
    QPropertyAnimation *animation;
    QTimer *closeTimer;

    void initUI(const QString &message);
    void setupAnimation();
    void closeDialog();

    static int stackCount;
    MessageType messageType;
};



#endif // DIALOG_H

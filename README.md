通过QDialog设计消息弹窗，需求：弹窗从界面底部从下往上弹出；三个消息弹窗出现时，进行堆叠弹出；
error,warning弹窗单击弹窗关闭；information弹窗定时自动关闭
可以根据error、warning和information三种不同的消息类型，显示不同颜色的消息弹窗和文字
根据不同消息的内容，可以选择不同的弹窗模态，exec()模态；show()非模态

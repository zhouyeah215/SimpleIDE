#ifndef CUSTOMCODEEDITOR_H
#define CUSTOMCODEEDITOR_H

#include "codeeditor.h"
#include <QMenu>

class CustomCodeEditor : public CodeEditor {
    Q_OBJECT

public:
    explicit CustomCodeEditor(QWidget *parent = nullptr);

protected:
     void showCustomContextMenu(const QPoint &pos); // 使用自定义槽函数显示上下文菜单

private slots:
     void replaceSelectedText();           // 替换所有选中的文本
     void replaceSelectedTextInLine();     // 替换当前行所有选中的文本
     void commentSelectedText();           // 将选中内容标为注释

private:
};

#endif // CUSTOMCODEEDITOR_H

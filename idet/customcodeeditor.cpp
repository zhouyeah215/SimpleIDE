#include "customcodeeditor.h"
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QInputDialog>
#include <QMimeData>
#include <QApplication>
#include <QClipboard>
#include <QTextCursor>
#include <QTextDocument>
#include <QDebug>

CustomCodeEditor::CustomCodeEditor(QWidget *parent)
    : CodeEditor(parent) {
    // 其他初始化操作可以在此处进行

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QPlainTextEdit::customContextMenuRequested, this, &CustomCodeEditor::showCustomContextMenu);
}



void CustomCodeEditor::showCustomContextMenu(const QPoint &pos) {
    QMenu menu(this);



    QAction *undo = new QAction("恢复", this);
    undo->setShortcut(tr("Ctrl+Z"));
    QAction *selectAllAction = new QAction("全选", this);
    selectAllAction->setShortcut(tr("Ctrl+A"));
    QAction *copyAction = new QAction("拷贝", this);
    copyAction->setShortcut(tr("Ctrl+C"));
    QAction *pasteAction = new QAction("粘贴", this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    QAction *cutAction = new QAction("剪切", this);
    cutAction->setShortcut(tr("Ctrl+X"));
    QAction *replaceAction = new QAction("替换所有", this);
    replaceAction->setShortcut(tr("Ctrl+R"));
    QAction *replaceInLineAction = new QAction("替换本行", this);
    QAction *commentSelectedTextAction = new QAction("标为注释", this);  // 新增：添加菜单项
    replaceAction->setShortcut(tr("Ctrl+R"));
    replaceInLineAction->setShortcut(tr("Ctrl+L"));
    commentSelectedTextAction->setShortcut(tr("Ctrl+/"));

    connect(undo, &QAction::triggered, this, &QPlainTextEdit::undo);
    connect(copyAction, &QAction::triggered, this, &QPlainTextEdit::copy);
    connect(pasteAction, &QAction::triggered, this, &QPlainTextEdit::paste);
    connect(cutAction, &QAction::triggered, this, &QPlainTextEdit::cut);
    connect(selectAllAction, &QAction::triggered, this, &QPlainTextEdit::selectAll);
    connect(replaceAction, &QAction::triggered, this, &CustomCodeEditor::replaceSelectedText);
    connect(replaceInLineAction, &QAction::triggered, this, &CustomCodeEditor::replaceSelectedTextInLine);
    connect(commentSelectedTextAction, &QAction::triggered, this, &CustomCodeEditor::commentSelectedText);  // 绑定槽函数

    // 添加动作到菜单
    menu.addAction(undo);
    menu.addSeparator(); // 添加分隔符
    menu.addAction(copyAction);
    menu.addSeparator();
    menu.addAction(pasteAction);
    menu.addSeparator();
    menu.addAction(cutAction);
    menu.addSeparator();
    menu.addAction(selectAllAction);
    menu.addSeparator();
    menu.addAction(replaceAction);
    menu.addSeparator();
    menu.addAction(replaceInLineAction);
    menu.addSeparator();
    menu.addAction(commentSelectedTextAction);


    menu.exec(mapToGlobal(pos));
}
void CustomCodeEditor::replaceSelectedText() {
    qDebug() << "replaceSelectedText() called";
    QString selectedText = textCursor().selectedText();
    if (selectedText.isEmpty()) {
        QMessageBox::warning(this, "替换文本", "没有选中的文本！");
        return;
    }

    bool ok;
    QString replacementText = QInputDialog::getText(this, tr("替换文本"),
                                                    tr("将所有 \"%1\" 替换为：").arg(selectedText),
                                                    QLineEdit::Normal, "", &ok);
    if (ok && !replacementText.isEmpty()) {
        QString content = toPlainText();
        content.replace(selectedText, replacementText);
        setPlainText(content);
    }
}
void CustomCodeEditor::replaceSelectedTextInLine() {
    QString selectedText = textCursor().selectedText();
    if (selectedText.isEmpty()) {
        QMessageBox::warning(this, "替换文本", "没有选中的文本！");
        return;
    }

    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::LineUnderCursor);  // 选择当前行
    QString lineText = cursor.selectedText();  // 获取当前行文本

    bool ok;
    QString replacementText = QInputDialog::getText(this, tr("替换文本"),
                                                    tr("将本行所有 \"%1\" 替换为：").arg(selectedText),
                                                    QLineEdit::Normal, "", &ok);
    if (ok && !replacementText.isEmpty()) {
        lineText.replace(selectedText, replacementText);  // 替换本行中的文本

        cursor.insertText(lineText);  // 插入替换后的文本
    }
}
void CustomCodeEditor::commentSelectedText() {
    QTextCursor cursor = textCursor();
    if (cursor.selectedText().isEmpty()) return;
    int selectionStart = cursor.selectionStart();
    int selectionEnd = cursor.selectionEnd();
    cursor.beginEditBlock();
    cursor.setPosition(selectionStart);
    cursor.setPosition(selectionEnd, QTextCursor::KeepAnchor);
    QString selectedText = cursor.selectedText();
    cursor.insertText("/*" + selectedText + "*/");
    cursor.endEditBlock();
}


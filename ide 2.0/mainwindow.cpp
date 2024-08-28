#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //text1 = new QTextEdit;
    //QFont f;
    //f.setPixelSize(30);
    //text1->setFont(f);
    //QColor c;
    //c.setRgb(255,0,0);
    //text1->setTextColor(c);
    //this->setCentralWidget(text1);

    file = this->menuBar()->addMenu("文件");
    edit = this->menuBar()->addMenu("编辑");
    build = this->menuBar()->addMenu("构建");
    find = this->menuBar()->addMenu("查询");
    help = this->menuBar()->addMenu("帮助");

    file_new = new QAction("新建", this);
    file_new->setShortcut(tr("Ctrl+N"));
    file_open = new QAction("打开", this);
    file_open->setShortcut(tr("Ctrl+O"));
    file_save = new QAction("保存当前文件", this);
    file_save->setShortcut(tr("Ctrl+S"));
    file_save_all = new QAction("保存所有文件", this);
    file_save_all->setShortcut(tr("Ctrl+Shift+S"));
    file_close = new QAction("关闭当前文件", this);
    file_close->setShortcut(tr("Ctrl+W"));
    file_close_all = new QAction("关闭所有文件", this);
    file_close_all->setShortcut(tr("Ctrl+Shift+W"));
    file_exit = new QAction("退出", this);
    file_exit->setShortcut(tr("Ctrl+Q"));
    file->addAction(file_new);
    file->addSeparator();
    file->addAction(file_open);
    file->addSeparator();
    file->addAction(file_save);
    file->addSeparator();
    file->addAction(file_save_all);
    file->addSeparator();
    file->addAction(file_close);
    file->addSeparator();
    file->addAction(file_close_all);
    file->addSeparator();
    file->addAction(file_exit);

    edit_undo = new QAction("恢复", this);
    edit_undo->setShortcut(tr("Ctrl+Z"));
    edit_redo = new QAction("重做", this);
    edit_redo->setShortcut(tr("Ctrl+Y"));
    edit_cut = new QAction("剪切", this);
    edit_cut->setShortcut(tr("Ctrl+X"));
    edit_copy = new QAction("拷贝", this);
    edit_copy->setShortcut(tr("Ctrl+C"));
    edit_paste = new QAction("粘贴", this);
    edit_paste->setShortcut(tr("Ctrl+V"));
    edit_selectAll = new QAction("全选", this);
    edit_selectAll->setShortcut(tr("Ctrl+A"));
    edit->addAction(edit_undo);
    edit->addSeparator();
    edit->addAction(edit_redo);
    edit->addSeparator();
    edit->addAction(edit_cut);
    edit->addSeparator();
    edit->addAction(edit_copy);
    edit->addSeparator();
    edit->addAction(edit_paste);
    edit->addSeparator();
    edit->addAction(edit_selectAll);

    build_compile = new QAction("编译", this);
    build_compile->setShortcut(tr("F9"));
    build_run = new QAction("运行", this);
    build_run->setShortcut(tr("F10"));
    build->addAction(build_compile);
    edit->addSeparator();
    build->addAction(build_run);

    find_out = new QAction("查找", this);
    find->addAction(find_out);
    findDialog = new QDialog(this);
    findDialog->setWindowTitle(tr("查找"));
    findEdit = new QLineEdit(findDialog);

    QPushButton *btn = new QPushButton(tr("完成"), findDialog);

    QVBoxLayout *layout = new QVBoxLayout(findDialog);
    layout->addWidget(findEdit);
    layout->addWidget(btn);

    help_about = new QAction("关于", this);
    help_about->setShortcut(tr("Ctrl+H"));
    help->addAction(help_about);

    //Qt的消息槽机制
    connect(file_new,SIGNAL(triggered()),this,SLOT(on_new()));
    connect(file_open,SIGNAL(triggered()),this,SLOT(on_open()));
    connect(file_save,SIGNAL(triggered()),this,SLOT(on_save()));
    //第一个参数是触发这个事件的控件，第二个参数是对于ACTION来讲，固定写SIGNAL(triggered())
    //第三个固定this，第四个参数指定点击action后会执行哪个函数

    connect(help_about,SIGNAL(triggered()),this,SLOT(on_about()));
    connect(file_exit,SIGNAL(triggered()),this,SLOT(on_exit()));

    connect(edit_undo,SIGNAL(triggered()),this,SLOT(on_undo()));
    connect(edit_redo,SIGNAL(triggered()),this,SLOT(on_redo()));
    connect(edit_cut,SIGNAL(triggered()),this,SLOT(on_cut()));
    connect(edit_copy,SIGNAL(triggered()),this,SLOT(on_copy()));
    connect(edit_paste,SIGNAL(triggered()),this,SLOT(on_paste()));
    connect(edit_selectAll,SIGNAL(triggered()),this,SLOT(on_selectAll()));
    connect(build_compile,SIGNAL(triggered()),this,SLOT(on_compile()));
    connect(build_run,SIGNAL(triggered()),this,SLOT(on_run()));
    connect(find_out, SIGNAL(triggered()), this, SLOT(findText()));
    connect(btn, &QPushButton::clicked, findDialog, &QDialog::accept);
}

MainWindow::~MainWindow()
{
    delete text;
}

void MainWindow::on_new()
{
    text = new QTextEdit;
    QFont f;
    f.setPixelSize(30);
    text->setFont(f);
    //QColor c;
    //c.setRgb(255,0,0);
    //text1->setTextColor(c);
    this->setCentralWidget(text);
}

void MainWindow::on_open()
{
    on_new();
    filename=QFileDialog::getOpenFileName();
    //QMessageBox::information(this, "提示", filename);

    if(filename.isEmpty())
        return;
    QString content;//Qt定义的一个字符串
    FILE *p = fopen(filename.toStdString().data(),"r");
    if(p == NULL){
         QMessageBox::information(this,"错误","打开文件失败");
    }
    else
    {
        while(!feof(p)){
            char buf[1024] = { 0 };
            fgets(buf, sizeof(buf), p);
            content += buf;
        }
        fclose(p);
        text->setText(content);
    }
}

void MainWindow::on_save()
{
    QString filename = QFileDialog::getSaveFileName();
    if(filename.isEmpty())
        return;

    FILE *p = fopen(filename.toStdString().data(), "w");
    if(p == NULL)
    {
        QMessageBox::information(this,"错误","打开文件失败");
    }
    else
    {
        fputs(text->toPlainText().toStdString().data(), p);
        fclose(p);
    }
}

void MainWindow::on_about()
{
    QMessageBox::information(this,"关于","。。。\n???");
}

void MainWindow::on_exit()
{
    exit(0);
}

void MainWindow::on_cut()
{
    text->cut();
}

void MainWindow::on_copy()
{
    text->copy();
}

void MainWindow::on_paste()
{
    text->paste();
}

void MainWindow::on_selectAll()
{
    text->selectAll();
}

void MainWindow::on_undo()
{
    text->undo();
}

void MainWindow::on_redo()
{
    text->redo();
}

void MainWindow::on_compile()
{
    QString destname = filename;
    if (filename.endsWith(".c")) {
           destname.replace(".c", ".exe");
       } else if (filename.endsWith(".cpp")) {
           destname.replace(".cpp", ".exe");
       } else {
           QMessageBox::information(this, "错误", "不支持的文件类型");
           return;
       }
    // 构建 GCC 编译命令
    QString command = "gcc -o \"" + destname + "\" \"" + filename + "\"";

    int result = system(command.toStdString().c_str());

    if (result == 0) {
        QMessageBox::information(this, "提示", "编译成功！");
    }
    else {
        QMessageBox::information(this, "错误", "编译失败！");
    }
}

void MainWindow::on_run()
{
    QString destname = filename;
    if (filename.endsWith(".c")) {
           destname.replace(".c", ".exe");
       } else if (filename.endsWith(".cpp")) {
           destname.replace(".cpp", ".exe");
       } else {
           QMessageBox::information(this, "错误", "不支持的文件类型");
           return;
       }
    system(destname.toStdString().c_str());
}

/*void MainWindow::findText()
{
    QString str = findEdit->text();

    bool found = text1->find(str, QTextDocument::FindBackward);
    if (!found) {
        QMessageBox::warning(this, tr("查找"), tr("找不到%1").arg(str));
    }
}*/
void MainWindow::findText()
{
    // 显示查找对话框
    if (findDialog->exec() == QDialog::Accepted){
        QString str = findEdit->text();
        QTextDocument::FindFlags op = QTextDocument::FindFlags();
        bool find = text->find(str, op);
        if (!find){
            QMessageBox::warning(this, tr("查找"), tr("找不到%1").arg(str));
        }
        else {
            QTextCursor cursor = text->textCursor();
            QTextCharFormat highlightFormat;
            highlightFormat.setBackground(Qt::lightGray);
            QTextDocument *doc = text->document();
            cursor.setPosition(0);
            QTextDocument::FindFlags options = QTextDocument::FindFlags();
            while (!cursor.isNull() && !cursor.atEnd()){
                cursor = doc->find(str, cursor, options);
                if (!cursor.isNull()){
                    cursor.mergeCharFormat(highlightFormat);
                }
            }
        }
    }
    /*if (findDialog->exec() == QDialog::Accepted) {
        QString str = findEdit->text();
        qDebug() << "Searching for: " << str;
        qDebug() << "text1 is" << text1->toPlainText();
        bool found = text1->find(str, QTextDocument::FindBackward);
        QTextDocument::FindFlags options = QTextDocument::FindFlags();
        bool found = text->find(str, options);
        if (!found) {
            QMessageBox::warning(this, tr("查找"), tr("找不到%1").arg(str));
        }
    }*/
}


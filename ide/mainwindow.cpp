#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

CodeEditor *MainWindow::currentEditor()
{
    return qobject_cast<CodeEditor*>(tabWidget->currentWidget());
}

QString MainWindow::currentFileName()
{
    CodeEditor* editor = currentEditor();
    if(editor)
    {
        return editor->get_filename();
    }
    //QWidget *widget = tabWidget->widget(index);
    //if (widget) {
    //   return tabWidget->tabText(index);
    //}
    return QString();
}

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
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::on_close_tab);

    file = this->menuBar()->addMenu("文件");
    edit = this->menuBar()->addMenu("编辑");
    build = this->menuBar()->addMenu("构建");
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
    build_compile_run = new QAction("编译运行", this);
    build_compile_run->setShortcut(tr("F11"));
    build->addAction(build_compile);
    edit->addSeparator();
    build->addAction(build_run);
    edit->addSeparator();
    build->addAction(build_compile_run);


    help_about = new QAction("关于", this);
    help_about->setShortcut(tr("Ctrl+H"));
    help->addAction(help_about);

    //Qt的消息槽机制
    connect(file_new,SIGNAL(triggered()),this,SLOT(on_new()));
    connect(file_open,SIGNAL(triggered()),this,SLOT(on_open()));
    connect(file_save,SIGNAL(triggered()),this,SLOT(on_save()));
    connect(file_save_all,SIGNAL(triggered()),this,SLOT(on_save_all()));
    connect(file_close,SIGNAL(triggered()),this,SLOT(on_close()));
    connect(file_close_all,SIGNAL(triggered()),this,SLOT(on_close_all()));
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
    connect(build_compile_run,SIGNAL(triggered()),this,SLOT(on_compile_run()));
}

MainWindow::~MainWindow()
{
    //delete text1;
}

void MainWindow::on_close_tab(int index)
{
    QWidget *widget = tabWidget->widget(index);
    tabWidget->removeTab(index);
    delete widget;
}

void MainWindow::on_close()
{
    int currentIndex = tabWidget->currentIndex();
    on_close_tab(currentIndex);
}

void MainWindow::on_close_all()
{
    while (tabWidget->count() > 0)
    {
        QWidget *widget = tabWidget->widget(0);
        tabWidget->removeTab(0);
        delete widget;
    }
}

void MainWindow::on_new()
{
    CodeEditor *editor = new CodeEditor;

    editor = new CodeEditor(this);
    QFont f;
    f.setPixelSize(20);
    editor->setFont(f);
    //QColor c;
    //c.setRgb(255,0,0);
    //text1->setTextColor(c);
    //this->setCentralWidget(text1);
    tabWidget->addTab(editor, "无标题");
    tabWidget->setCurrentWidget(editor);
}

void MainWindow::on_open()
{   
    QString filename=QFileDialog::getOpenFileName();
    //QMessageBox::information(this, "提示", filename);

    if(filename.isEmpty())
        return;
    on_new();
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
        CodeEditor *editor = currentEditor();
        editor->set_filename(filename);
        tabWidget->addTab(editor,  QFileInfo(filename).fileName());
        editor->setPlainText(content);
    }
}

void MainWindow::on_save_tab(CodeEditor *editor)
{
    QString filename = QFileDialog::getSaveFileName();
    int index = tabWidget->indexOf(editor);

    if(filename.isEmpty())
        return;
    else{
        tabWidget->setTabText(index,  QFileInfo(filename).fileName());
        editor->set_filename(filename);
    }

    FILE *p = fopen(filename.toStdString().data(), "w");
    if(p == NULL)
    {
        QMessageBox::information(this,"错误","打开文件失败");
    }
    else
    {
        fputs(editor->toPlainText().toStdString().data(), p);
        fclose(p);
    }
}

void MainWindow::on_save()
{
    CodeEditor *editor = currentEditor();
    if (editor)
    {
        on_save_tab(editor);
    }
}

void MainWindow::on_save_all()
{
    int count = tabWidget->count();

    for(int i = 0; i < count; i++)
    {
        CodeEditor *editor = qobject_cast<CodeEditor*>(tabWidget->widget(i));
        if(editor)
        {
            on_save_tab(editor);
        }
    }
}

void MainWindow::on_about()
{
    QMessageBox::information(this,"关于","基于C++语言的C语言集成开发环境");
}

void MainWindow::on_exit()
{
    exit(0);
}

void MainWindow::on_cut()
{
    CodeEditor *editor = currentEditor();
    if (editor)
    editor->cut();
}

void MainWindow::on_copy()
{
    CodeEditor *editor = currentEditor();
    if (editor)
    editor->copy();
}

void MainWindow::on_paste()
{
    CodeEditor *editor = currentEditor();
    if (editor)
    editor->paste();
}

void MainWindow::on_selectAll()
{
    CodeEditor *editor = currentEditor();
    if (editor)
    editor->selectAll();
}

void MainWindow::on_undo()
{
    CodeEditor *editor = currentEditor();
    if (editor)
    editor->undo();
}

void MainWindow::on_redo()
{
    CodeEditor *editor = currentEditor();
    if (editor)
    editor->redo();
}

void MainWindow::on_compile()
{
    CodeEditor *editor = currentEditor();
    if (editor)
    {
        QString filename = currentFileName();
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
        QString command = "gcc -o \"" + destname + "\" \"" + filename + "\"" ;
        //QMessageBox::information(this, "编译命令", command);

        int result = system(command.toStdString().c_str());

        if (result == 0) {
            QMessageBox::information(this, "提示", "编译成功！");
        }
        else {
            QMessageBox::information(this, "错误", "编译失败！");
        }
    }
}

void MainWindow::on_run()
{
    QString filename = currentFileName();
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

void MainWindow::on_compile_run()
{
    on_compile();
    on_run();
}

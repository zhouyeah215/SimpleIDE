#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QTabWidget>
#include "codeeditor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //QString filename;
    //CodeEditor *text1;

    QTabWidget *tabWidget;  // 管理多个打开的文件

    QString currentFileName();
    CodeEditor *currentEditor();

    QMenu *file;
    QMenu *edit;
    QMenu *build;
    QMenu *help;

    QAction *file_new;
    QAction *file_open;
    QAction *file_exit;
    QAction *file_close;
    QAction *file_close_all;
    QAction *file_save;
    QAction *file_save_all;

    QAction *edit_undo;
    QAction *edit_redo;
    QAction *edit_cut;
    QAction *edit_copy;
    QAction *edit_paste;
    QAction *edit_selectAll;

    QAction *build_compile;
    QAction *build_run;
    QAction *build_compile_run;

    QAction *help_about;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_close_tab(int index);
    void on_close();
    void on_close_all();
    void on_new();
    void on_open();
    void on_save_tab(CodeEditor *editor);
    void on_save();
    void on_save_all();
    void on_about();
    void on_exit();
    void on_cut();
    void on_copy();
    void on_paste();
    void on_selectAll();
    void on_undo();
    void on_redo();
    void on_compile();
    void on_run();
    void on_compile_run();
};
#endif // MAINWINDOW_H

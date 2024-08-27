#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString filename;
    QTextEdit *text1;
    QMenu *file;
    QMenu *edit;
    QMenu *build;
    QMenu * find;
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

    QAction *find_out;

    QAction *help_about;

    QLineEdit *findEdit;

    QDialog *findDialog;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_new();
    void on_open();
    void on_save();
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
    void findText();
};
#endif // MAINWINDOW_H

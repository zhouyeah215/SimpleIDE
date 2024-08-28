#include "mainwindow.h"
#include "codeeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //CodeEditor *editor = new CodeEditor;
    //w.setCentralWidget(editor);
    //w.setWindowTitle("Code Editor with Line Numbers");
    w.resize(800,600);
    w.show();
    return a.exec();
}

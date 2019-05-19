#include "mainwindow.h"
#include "serialportconnector.h"
#include <QApplication>
#include <QObject>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* Apply style sheet */
    QFile f(":/qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        a.setStyleSheet(f.readAll());
    }

    MainWindow w;

    w.initWindow();
    w.show();

    return a.exec();
}

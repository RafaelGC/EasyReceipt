#include "Mainwindow.hpp"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*QTranslator translator;
    translator.load("prueba");
    app.installTranslator(&translator);*/

    MainWindow w;
    w.show();
    
    return app.exec();
}

#include "mainwindow.h"
#include "Windows.h"
#include "WinUser.h"
//在下面的用于获取分辨率大小的函数需要静态链接到系统的库中
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "gdi32.lib")
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    //添加Qt的对高分屏的支持
   #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
       //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
       //QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
       QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
   #endif

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GUI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}

#include <QApplication>
#include <QDeclarativeView>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QIcon>
#include <QDesktopWidget>
#include "datafilter.h"

QString WindowTitle = "SMF 条码追溯系统";
Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect =desktopWidget->availableGeometry();
    //获取设备屏幕大小
    QRect screenRect =desktopWidget->screenGeometry();

    //qDebug() << screenRect.width() << screenRect.height();
       //g_nActScreenX = deskRect.width();
       //g_nActScreenY = deskRect.height();


    app.setWindowIcon(QIcon("logo.ico"));

    DataFilter dataFilter;
    QDeclarativeView viewer;
    viewer.setWindowFlags(Qt::FramelessWindowHint);
    QDeclarativeEngine *engine=viewer.engine();
    QDeclarativeContext *context=engine->rootContext();
    context->setContextProperty("dataFilter", &dataFilter);
    context->setContextProperty("app", &app);
    context->setContextProperty("main_window", &viewer);
    context->setContextProperty("WIDTH", screenRect.width());
    context->setContextProperty("HEIGHT", screenRect.height());
    viewer.setSource(QUrl("qml/LotNo/main.qml"));
    viewer.show();
    return app.exec();
}


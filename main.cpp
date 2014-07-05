#include <QApplication>
#include <QDeclarativeView>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QIcon>
#include <QDesktopWidget>
#include "datafilter.h"

/*
 * SMF_Product 产品类别
 * SMF_P1: SMF 条码追溯系统
 * SMF_P2: 前工序 SMF 条码追溯系统
 * SMF_P3: 返修品 SMF 条码追溯系统
 */
QString SMF_Product = "SMF_P2";
QString WindowTitle = "";
QString Version = "";

/*
 * argv 1: SMF_Product
 * argv 2: Version eg: v1.0
 */
void InitProduct(int argc, char *argv[])
{
    if(argc >= 2)
        SMF_Product = argv[1];

    if(SMF_Product == "SMF_P1"){
        WindowTitle = "SMF 条码追溯系统";
    }else if(SMF_Product == "SMF_P2"){
        WindowTitle = "前工序 SMF 条码追溯系统";
    }else if(SMF_Product == "SMF_P3"){
        WindowTitle = "返修品 SMF 条码追溯系统";
    }

    if(argc >=3)
        Version = argv[2];
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    InitProduct(argc, argv);
    app.setWindowIcon(QIcon("logo.ico"));
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect =desktopWidget->availableGeometry();
    //获取设备屏幕大小
    //QRect screenRect =desktopWidget->screenGeometry();

    DataFilter dataFilter;
    QDeclarativeView viewer;
    viewer.setWindowFlags(Qt::FramelessWindowHint);
    QDeclarativeEngine *engine=viewer.engine();
    QDeclarativeContext *context=engine->rootContext();
    context->setContextProperty("dataFilter", &dataFilter);
    context->setContextProperty("app", &app);
    context->setContextProperty("main_window", &viewer);
    context->setContextProperty("windowTitle", WindowTitle);
    context->setContextProperty("SMF_Product", SMF_Product);
    context->setContextProperty("WIDTH", deskRect.width());
    context->setContextProperty("HEIGHT", deskRect.height());
    viewer.setSource(QUrl("qml/LotNo/main.qml"));
    viewer.show();
    return app.exec();
}


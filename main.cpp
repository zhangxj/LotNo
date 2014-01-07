#include <QApplication>
#include <QDeclarativeView>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QIcon>
#include "datafilter.h"

QString WindowTitle = "SMF 条码追溯系统";
Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("logo.ico"));

    DataFilter dataFilter;
    QDeclarativeView viewer;
    viewer.setWindowFlags(Qt::FramelessWindowHint);
    QDeclarativeEngine *engine=viewer.engine();
    QDeclarativeContext *context=engine->rootContext();
    context->setContextProperty("dataFilter", &dataFilter);
    context->setContextProperty("app", &app);
    context->setContextProperty("main_window", &viewer);
    viewer.setSource(QUrl("qml/LotNo/main.qml"));
    viewer.show();
    return app.exec();
}


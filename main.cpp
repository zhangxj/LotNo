#include <QApplication>
#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include "datafilter.h"
#include <QSettings>


QString WindowTitle = "SMF 条码追溯系统";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("logo.ico"));
    DataFilter dataFilter;
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("dataFilter", &dataFilter);
    engine.load(QUrl("qml/LotNo/main.qml"));
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    window->setTitle(WindowTitle);
    window->show();
    return app.exec();
}

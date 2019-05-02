#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "gamefield.h"
#include "player.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameField>("GameField",1,0,"GameField");
    qmlRegisterType<Player>("Player",1,0,"Player");

    QQmlApplicationEngine engine;
    QQuickView view(&engine, nullptr);

    Player *plr = new Player();
    view.rootContext()->setContextObject(plr);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
   // view.show();

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

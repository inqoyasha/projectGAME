#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "gamefieldmodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameFieldModel>("GameField", 1,0, "GameFieldModel");

    QQmlApplicationEngine engine;
//    GameFieldModel *model = new GameFieldModel(&engine);

//    engine.rootContext()->setContextProperty("GameFieldModel", model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

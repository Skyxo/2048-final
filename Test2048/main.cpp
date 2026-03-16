#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "game.h"

int main(int argc, char *argv[])
{
    // 1. Création de l'application Qt
    QGuiApplication app(argc, argv);

    // 2. Création du moteur QML
    QQmlApplicationEngine engine;

    // 3. Création d'une instance de Game
    Game game;

    // 4. Exposition de l'objet game au QML sous le nom "game"
    engine.rootContext()->setContextProperty("game", &game);

    // 5. Chargement du fichier QML principal
    const QUrl url(u"qrc:/Test2048/Main.qml"_qs);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
        );

    engine.load(url);

    // 6. Lancement de la boucle événementielle
    return app.exec();
}

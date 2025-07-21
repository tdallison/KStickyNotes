#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "NoteManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setOrganizationName("TylerD");
    QGuiApplication::setApplicationName("KStickyNotes");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    NoteManager noteManager(&engine);
    engine.rootContext()->setContextProperty("noteManager", &noteManager);

    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() {
        noteManager.saveNotes();
    });

    noteManager.loadNotes();

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include "NoteManager.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    NoteManager noteManager(&engine);
    engine.rootContext()->setContextProperty("noteManager", &noteManager);

    noteManager.loadNotes();

    QSystemTrayIcon trayIcon(QIcon::fromTheme("dialog-notes"));
    QMenu trayMenu;
    QAction *newNoteAction = new QAction("New Note");
    QObject::connect(newNoteAction, &QAction::triggered, [&]() {
        noteManager.createNote();
    });
    trayMenu.addAction(newNoteAction);
    trayMenu.addAction("Quit", &app, &QCoreApplication::quit);
    trayIcon.setContextMenu(&trayMenu);
    trayIcon.show();

    return app.exec();
}
#include "NoteManager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QDebug>

NoteManager::NoteManager(QQmlApplicationEngine* engine, QObject *parent)
    : QObject(parent), m_engine(engine) {}

QString NoteManager::getNotePath(const QString &noteId) const {
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/notes";
    QDir().mkpath(basePath);
    return basePath + "/" + noteId + ".json";
}

void NoteManager::createNote(const QString &text, const QPoint &pos, const QString &color, const QString &noteId) {
    QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/Note.qml")));
    QObject *note = component.create();

    QString finalNoteId = noteId.isEmpty() ? QUuid::createUuid().toString(QUuid::WithoutBraces) : noteId;

    if (note) {
        note->setProperty("noteId", finalNoteId);
        note->setProperty("text", text);
        note->setProperty("x", pos.x());
        note->setProperty("y", pos.y());
        note->setProperty("width", 250);
        note->setProperty("height", 180);
        note->setProperty("currentColor", color);
        m_noteWindows.append(note);
    }
}

void NoteManager::closeNote(QObject* window) {
    if (!window) return;

    QString noteId = window->property("noteId").toString();
    QFile::remove(getNotePath(noteId));

    m_noteWindows.removeOne(window);
    window->deleteLater();
}

void NoteManager::loadNotes() {
    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/notes";
    QDir notesDir(dirPath);
    if (!notesDir.exists()) return;

    QStringList files = notesDir.entryList(QStringList() << "*.json", QDir::Files);
    for (const QString &fileName : files) {
        QFile file(notesDir.filePath(fileName));
        if (file.open(QIODevice::ReadOnly)) {
            QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
            QString text = obj["text"].toString();
            QPoint pos(obj["x"].toInt(), obj["y"].toInt());
            QString color = obj["color"].toString();
            QString id = obj["id"].toString();
            createNote(text, pos, color, id);
            file.close();
        }
    }
}

void NoteManager::saveNote(QObject* window) {
    if (!window) return;

    QString noteId = window->property("noteId").toString();
    QString text = window->property("text").toString();
    int x = window->property("x").toInt();
    int y = window->property("y").toInt();
    int width = window->property("width").toInt();
    int height = window->property("height").toInt();
    QString color = window->property("currentColor").toString();

    QJsonObject obj;
    obj["id"] = noteId;
    obj["text"] = text;
    obj["x"] = x;
    obj["y"] = y;
    obj["width"] = width;
    obj["height"] = height;
    obj["color"] = color;

    QFile file(getNotePath(noteId));
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(obj).toJson());
        file.close();
    }
}

void NoteManager::saveNotes() {
    for (QObject* note : m_noteWindows) {
        saveNote(note);
    }
}

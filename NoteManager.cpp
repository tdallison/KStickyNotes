#include "NoteManager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QStandardPaths>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QDebug>
#include <QDir>

NoteManager::NoteManager(QQmlApplicationEngine* engine, QObject *parent)
    : QObject(parent), m_engine(engine) {}

void NoteManager::createNote(const QString &text, const QPoint &pos, const QString &color, const QString &noteId) {
    QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/Note.qml")));
    QObject *note = component.create();

    if (note) {
        note->setProperty("text", text);
        note->setProperty("x", pos.x());
        note->setProperty("y", pos.y());
        note->setProperty("currentColor", color);
        m_noteWindows.append(note);
    }
}

void NoteManager::closeNote(QObject* window) {
    m_noteWindows.removeOne(window);
    window->deleteLater();
    saveNotes();
}

void NoteManager::loadNotes() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile file(path + "/notes.json");
    if (!file.exists()) return;

    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        for (const QJsonValue &val : doc.array()) {
            QJsonObject obj = val.toObject();
            QString text = obj["text"].toString();
            QPoint pos(obj["x"].toInt(), obj["y"].toInt());
            QString color = obj["color"].toString();
            createNote(text, pos, color);
        }
        file.close();
    }
}

void NoteManager::saveNotes() {
    QJsonArray array;
    for (QObject *note : m_noteWindows) {
        QJsonObject obj;
        obj["text"] = note->property("text").toString();
        obj["x"] = note->property("x").toInt();
        obj["y"] = note->property("y").toInt();
        obj["color"] = note->property("currentColor").toString();
        array.append(obj);
    }

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QFile file(path + "/notes.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(array);
        file.write(doc.toJson());
        file.close();
    }
}
#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QVariantList>
#include <QPoint>
#include <QList>
#include <QUuid>

class NoteManager : public QObject {
    Q_OBJECT

public:
    explicit NoteManager(QQmlApplicationEngine* engine, QObject *parent = nullptr);
    Q_INVOKABLE void createNote(const QString &text = "", const QPoint &pos = QPoint(), const QString &color = "#FFDD00", const QString &noteId = "");
    Q_INVOKABLE void closeNote(QObject* window);
    Q_INVOKABLE void saveNote(QObject* window);
    Q_INVOKABLE void saveNotes();
    void loadNotes();

private:
    QString getNotePath(const QString &noteId) const;

    QQmlApplicationEngine* m_engine;
    QList<QObject*> m_noteWindows;
};

#endif // NOTEMANAGER_H

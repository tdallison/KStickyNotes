import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    id: noteWindow
    width: 250
    height: 300
    visible: true
    color: currentColor
    flags: Qt.Tool | Qt.FramelessWindowHint

    property color currentColor: "#FFDD00"
    property alias text: noteArea.text
    property string noteId

    onXChanged: noteManager.saveNote(noteWindow)
    onYChanged: noteManager.saveNote(noteWindow)
    onCurrentColorChanged: noteManager.saveNote(noteWindow)

    Rectangle {
        anchors.fill: parent
        color: "#333"

        Column {
            anchors.fill: parent
            spacing: 0

            Rectangle {
                height: 30
                width: parent.width
                color: currentColor

                Row {
                    anchors.right: parent.right
                    spacing: 10
                    padding: 5

                    Button {
                        text: "+"
                        onClicked: noteManager.createNote()
                    }

                    MenuButton {
                        text: "⋯"
                        Menu {
                            MenuItem { text: "Yellow"; onTriggered: currentColor = "#FFDD00" }
                            MenuItem { text: "Green"; onTriggered: currentColor = "#B4D455" }
                            MenuItem { text: "Blue";  onTriggered: currentColor = "#89CFF0" }
                            MenuItem { text: "Pink";  onTriggered: currentColor = "#FFC0CB" }
                        }
                    }

                    Button {
                        text: "✕"
                        onClicked: noteManager.closeNote(noteWindow)
                    }
                }
            }

            TextArea {
                id: noteArea
                anchors.fill: parent
                wrapMode: Text.Wrap
                placeholderText: "Take a note..."
                background: null
                color: "white"
                font.pointSize: 12
                onTextChanged: noteManager.saveNote(noteWindow)
            }
        }
    }
}
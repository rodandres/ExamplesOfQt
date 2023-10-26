/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.5
import QtQuick.Controls 6.5
import FirstProject

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        text: qsTr("Hello FirstProject")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }

    Button {
        id: button
        x: 565
        y: 482
        text: qsTr("Button")

        Connections {
            target: button
            onClicked: console.log("button.clicked")
        }
    }
}

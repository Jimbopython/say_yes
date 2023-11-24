import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    width: 1280
    height: 720
    visible: true
    title: qsTr("Say yes!")
    color: "black"

    Text {
        anchors.centerIn: parent
        text: "You already chose " + settings.getChoice() + " !"
        font.pixelSize: 100
        color: "white"
    }
}

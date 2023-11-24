import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    width: 1280
    height: 720
    visible: true
    title: qsTr("Say yes!")
    color: "black"

    Text {
        id: questionText
        anchors.horizontalCenter: parent.horizontalCenter
        text: question
        color: "white"
        font.pointSize: 30
    }

    Text {
        id: paragraphText
        anchors.horizontalCenter: parent.horizontalCenter
        y: yesButton.y / 2
        color: "white"
        font.pointSize: 20
    }

    Button {
        id: yesButton
        text: "YES"
        anchors.centerIn: parent
        height: 200
        width: 400
        font.pointSize: 100
        background: Rectangle {
            color: "greenyellow"
            radius: 20
        }

        onClicked:
        {
            settings.setChosen(true)
            yesButton.visible = false
            noButton.visible = false
            particles.running = true
            paragraphText.visible = false
        }
    }
    CheckBox {
        Timer
        {
            id: quitTimer
            interval: 5000
            repeat: false
            onTriggered:
            {
                Qt.quit()
            }
        }

        id: noButton
        text: "<font color=\"white\">No</font>"

        x: (yesButton.x + yesButton.width / 2) - width / 2
        y: yesButton.y + yesButton.height + 20
        property int index: 0
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                let max_x = mainWindow.width - noButton.width
                let max_y = mainWindow.height - noButton.height
                let new_x = 0
                let new_y = 0
                do {
                    new_x = Math.floor(Math.random() * max_x)
                    new_y = questionText.height + Math.floor(Math.random() * (max_y - questionText.height))

                    var in_x_of_yes_button = new_x + noButton.width >= yesButton.x && new_x <= yesButton.x + yesButton.width
                    var in_y_of_yes_button = new_y + noButton.height >= yesButton.y && new_y <= yesButton.y + yesButton.height
                    // todo this kind of switches from left to right
                    var in_x_of_old_no_button = new_x + noButton.width >= noButton.x && new_x <= noButton.x + noButton.width
                    var in_y_of_old_no_button = new_y + noButton.height >= noButton.y && new_y <= noButton.y + noButton.height

                    var in_x_of_paragraph = new_x + noButton.width >= paragraphText.x && new_x <= paragraphText.x + paragraphText.width
                    var in_y_of_paragraph = new_y + noButton.height >= paragraphText.y && new_y <= paragraphText.y + paragraphText.height

                } while (in_x_of_yes_button || in_y_of_yes_button || in_x_of_old_no_button || in_y_of_old_no_button || in_x_of_paragraph || in_y_of_paragraph)

                noButton.x = new_x
                noButton.y = new_y

                paragraphText.text = paragraphs[noButton.index]
                noButton.index += 1

                if (noButton.index >= paragraphs.length)
                {
                    enabled = false
                }
            }
        }
        onClicked:
        {
            settings.setChosen(false)
            yesButton.enabled = false
            noButton.enabled = false
            quitTimer.start()
        }
    }
    Fireworks {
        id: particles
    }
}

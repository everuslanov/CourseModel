import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Ui 1.0
import QtGraphicalEffects 1.0

BasePage {
    id: root

    property alias imgSource: img.source
    property alias description: description.text
    property int id: -1

    background: Qt.darker("#009688", 2)

    Rectangle {
        id: cardContainer

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: Ui.dip(40)
        }

        color: "white"
        height: parent.height - Ui.dip(20) * 2 - Ui.dip(10)
        width: Ui.dip(300)
        radius: Ui.dip(10)

        Flickable {
            id: card

            anchors.fill: parent
            interactive: contentHeight > height

            Column {
                anchors {
                    fill: parent
                    margins: Ui.dip(10)
                }

                spacing: Ui.dip(10)

                Rectangle {
                    id: imgContainer

                    anchors.horizontalCenter: parent.horizontalCenter
                    height: Ui.dip(220)
                    width: parent.width + Ui.dip(20)
                    color: "coral"

                    Rectangle {
                        anchors {
                            bottom: parent.bottom
                            bottomMargin: Ui.dip(3)
                        }
                        width: parent.width
                        height: Ui.dip(1)
                    }

                    Image {
                        id: img

                        anchors {
                            fill: parent
                            margins: Ui.dip(10)
                        }

                        fillMode: Image.Stretch
                    }
                }

                Text {
                    id: description

                    font {
                        family: "Helvetica"
                        pixelSize: Ui.dipFont(7)
                    }
                    wrapMode: Text.WordWrap
                    elide: Text.ElideRight
                    width: parent.width
                    height: card.height - imgContainer.height - Ui.dip(10) - Ui.dip(10) - Ui.dip(30)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                Rectangle {
                    color: "coral"
                    width: card.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: Ui.dip(10)
                    opacity: 0.7
                }
            }
        }

        opacity: 0.0
        state: ""
        states: State {
            name: "opened"

            PropertyChanges {
                target: cardContainer
                anchors.topMargin: Ui.dip(20)
            }

            PropertyChanges {
                target: cardContainer
                opacity: 1.0
            }
        }

        transitions: Transition {
            from: "*"
            to: "*"
            NumberAnimation {
                properties: "anchors.topMargin, opacity"
                easing.type: Easing.InOutQuad
                duration: 1000
            }
        }

        Component.onCompleted: {
            state = "opened";
        }
    }

    Button {
        anchors {
            bottom: parent.bottom
            bottomMargin: Ui.dip(20)
            right: parent.right
            rightMargin: Ui.dip(-10)
        }

        width: Ui.dip(120)
        height: Ui.dip(50)
        text: "Поехали!"
        visible: view.depth == 3

        highlighted: true

        background: Rectangle {
            color: "coral"
            radius: Ui.dip(10)
        }

        onClicked: {
            root.next(4);
        }
    }
}

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Ui 1.0

BasePage {
    id: root

    property int id
    property string title: ""
    property string textQuestion: ""
    property var nextQuestions
    property QtObject responses
    property int checked_id: -1

    background: Qt.darker("#009688", 2)

    Rectangle {
        id: cardContainer

        anchors {
            left: parent.left
            leftMargin: Ui.dip(20)
            top: parent.top
            topMargin: Ui.dip(40)
        }

        color: "white"
        height: parent.height - Ui.dip(20) * 2
        width: Ui.dip(300)
        radius: Ui.dip(10)

        Flickable {
            id: card

            anchors.fill: parent
            clip: true
            contentHeight: contentColumn.implicitHeight + Ui.dip(20)
            interactive: contentHeight > parent.height

            Column {
                id: contentColumn

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

                    SwipeView {
                        id: imgSwipeView

                        anchors.centerIn: parent

                        height: parent.height - Ui.dip(20)
                        width: parent.width - Ui.dip(20)
                        interactive: false
                        currentIndex: 0
                        clip: true

                        Repeater {
                            height: imgSwipeView.height
                            width: imgSwipeView.width
                            model: 3
                            delegate: Image {
                                width: imgSwipeView.width
                                height: imgSwipeView.height
                                source: "qrc:/qml/assets/onboarding_" + (index + 1) + ".png"
                                fillMode: Image.Stretch

                                opacity: index == imgSwipeView.currentIndex
                                Behavior on opacity {
                                    OpacityAnimator { duration: 200 }
                                }
                            }
                        }

                        Timer {
                            running: true
                            repeat: true
                            interval: 1000
                            onTriggered: {
                                if (imgSwipeView.currentIndex < 2) {
                                    imgSwipeView.currentIndex++;
                                } else {
                                    imgSwipeView.currentIndex = 0;
                                }
                            }
                        }
                    }
                }

                Text {
                    text: title
                    color: "black"
                    opacity: 0.8
                    elide: Text.ElideRight
                    wrapMode: Text.WordWrap
                    width: parent.width
                    font {
                        family: "Helvetica"
                        weight: Font.Bold
                        pixelSize: Ui.dipFont(7)
                    }
                }

                Text {
                    text: textQuestion
                    color: "black"
                    opacity: 0.8
                    elide: Text.ElideRight
                    wrapMode: Text.WordWrap
                    width: parent.width
                    font {
                        family: "Helvetica"
                        pixelSize: Ui.dipFont(6)
                    }
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

    Rectangle {
        anchors.fill: questionsView
        color: "white"
        radius: Ui.dip(10)
    }

    ListView {
        id: questionsView

        anchors {
            left: cardContainer.right
            leftMargin: Ui.dip(10)
            right: parent.right
            rightMargin: Ui.dip(10)
            top: parent.top
            topMargin: Ui.dip(20)
        }
        height: contentHeight
        interactive: contentHeight > parent.height
        model: responses
        delegate: RadioButton {
            anchors {
                left: parent.left
                leftMargin: Ui.dip(10)
                right: parent.right
            }
            contentItem: Text {
                anchors.left: parent.indicator.right
                anchors.leftMargin: Ui.dip(5)
                anchors.right: parent.right
                anchors.rightMargin: Ui.dip(5)
                anchors.verticalCenter: parent.indicator.verticalCenter
                width: parent.width
                wrapMode: Text.WordWrap
                elide: Text.ElideRight
                text: parent.text
            }

            text: model.text
            Material.accent: Material.Red
            onCheckedChanged: {
                if (checked) {
                    checked_id = model.id
                }
            }
        }
    }

    Row {
        id: rowButton

        anchors {
            right: parent.right
            rightMargin: Ui.dip(20)
            bottom: cardContainer.bottom
        }

        height: Ui.dip(50)
        spacing: Ui.dip(10)

        Button {
            text: qsTr("Назад")
            width: Ui.dip(120)
            height: parent.height
            highlighted: true

            background: Rectangle {
                color: "coral"
                radius: Ui.dip(10)
            }

            onClicked: root.back();
        }

        Button {
            width: Ui.dip(120)
            height: parent.height
            highlighted: true
            enabled: checked_id !== -1

            background: Rectangle {
                color: "coral"
                radius: Ui.dip(10)
            }

            text: qsTr("Дальше")
            onClicked: root.next(checked_id)
        }
    }

    Component.onCompleted: {
        console.log(root)
    }
}

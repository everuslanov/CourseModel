import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Ui 1.0

BasePage {
    id: root

    property var decision: null
    property bool isReady: !!decision

    background: Qt.darker("#009688", 2)

    Loader {
        anchors.fill: parent
        active: isReady
        sourceComponent: Item {
            Column {
                anchors.centerIn: parent

                spacing: Ui.dip(10)

                Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: resultTextHello.implicitWidth + Ui.dip(20)
                    height: resultTextHello.implicitHeight + Ui.dip(20)
                    radius: Ui.dip(10)

                    Text {
                        id: resultTextHello

                        anchors.centerIn: parent
                        text: qsTr("Мы думаем вам подойдет данный комплект стоимостью в " + decision.summary + " р.")
                        font {
                            family: "Helvetica"
                            pixelSize: Ui.dipFont(5)
                        }
                    }
                }

                Row {
                    spacing: Ui.dip(10)
                    Image {
                        width: Ui.dip(150)
                        height: width
                        source: "qrc:/qml/assets/onboarding_1.png"
                    }
                    Image {
                        width: Ui.dip(150)
                        height: width
                        source: "qrc:/qml/assets/onboarding_2.png"
                    }
                    Image {
                        width: Ui.dip(150)
                        height: width
                        source: "qrc:/qml/assets/onboarding_3.png"
                    }
                }

                Rectangle {
                    id: cardContainer

                    anchors.horizontalCenter: parent.horizontalCenter
                    width: resultText.implicitWidth + Ui.dip(20)
                    height: resultText.implicitHeight + Ui.dip(20)
                    radius: Ui.dip(10)

                    Column {
                        id: resultText
                        anchors {
                            fill: parent
                            margins: Ui.dip(10)
                        }

                        spacing: Ui.dip(5)

                        Text {
                            text: qsTr("Сабвуфер: " + decision.subwoofer)
                            font {
                                family: "Helvetica"
                                pixelSize: Ui.dipFont(5)
                            }
                        }
                        Text {
                            text: qsTr("Головное устройство: " + decision.head)
                            font {
                                family: "Helvetica"
                                pixelSize: Ui.dipFont(5)
                            }
                        }
                        Text {
                            text: qsTr("Фронтальная акустика: " + decision.front)
                            font {
                                family: "Helvetica"
                                pixelSize: Ui.dipFont(5)
                            }
                        }
                        Text {
                            text: qsTr("Усилитель: " + decision.power)
                            font {
                                family: "Helvetica"
                                pixelSize: Ui.dipFont(5)
                            }
                        }
                    }
                }
            }
        }
    }

    Button {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: Ui.dip(10)
        }
        text: qsTr("Начать сначала!")
        Material.accent: Material.DeepOrange
        highlighted: true
        onClicked: {
            next(-666)
        }
    }
}

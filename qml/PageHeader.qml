import QtQuick 2.12
import QtQuick.Controls 2.12
import Ui 1.0

Rectangle {
    id: root

    color: "#009688"

    Row {
        anchors{
            fill: parent
            leftMargin: Ui.dip(20)
        }

        spacing: Ui.dip(20)

        Image {
            id: img
            anchors.verticalCenter: parent.verticalCenter
            height: Ui.dip(50)
            width: Ui.dip(50)
            source: "qrc:/qml/assets/progra_logo.png"
            fillMode: Image.Stretch
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            text: qsTr("Подбор акустической системы для вашего автомобиля!")
            font {
                pixelSize: Ui.dip(15)
                weight: Font.Bold
            }
            wrapMode: Text.NoWrap
            elide: Text.ElideRight
            width: root.width - Ui.dip(20) * 3 - img.width
        }
    }
}

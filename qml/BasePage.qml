import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import Ui 1.0

Item {
    id: root

    property StackView view: StackView {}
    property alias background: background.color

    signal next(var responseIndex)
    signal back()

    width: view.width
    height: view.height

    Rectangle {
        id: background

        anchors.fill: parent

        RadialGradient {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "white" }
                GradientStop { position: 1.0; color: background.color }
            }
        }
    }
}

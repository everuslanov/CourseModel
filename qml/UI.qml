pragma Singleton

import QtQuick 2.12
import QtQuick.Window 2.12

QtObject {
    id: root

    function dip (dp) { return dp * _screenParams.ratio }
    function dipFont (dp) { return dp * _screenParams.ratioFont }
}

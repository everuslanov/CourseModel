import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Ui 1.0
import QtQml.Models 2.12
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: root

    visible: true
    width: Ui.dip(620)
    height: Ui.dip(480)

    minimumWidth: Ui.dip(620)
    minimumHeight: Ui.dip(480)

    title: qsTr("Подбор авто-акустики")

    Material.theme: Material.Light
    Material.accent: Material.Blue

    QtObject {
        id: internal

        property bool onboardingReady: false

        function getOnboardingText(index) {
            switch(index) {
            case 1:
                return "Процессинг звука - очень важно, для этого мы подберем головное устройство!"
            case 2:
                return "Мы поможем подобрать вам качественный сабвуфер под ваши запросы!"
            case 3:
                return "Для раскрытия потенциала акустики, необходимо выбрать мощный усилитель!"
            }
        }

        function getOnboardingImage(index) {
            return "qrc:/qml/assets/onboarding_" + index + ".png"
        }
    }

    Timer {
        interval: 2500
        running: true
        repeat: true
        onTriggered: {
            if (swipeView.depth >= 3) {
                running = false;
                return;
            }

            swipeView.push(onboardingPage, {
                               "imgSource": internal.getOnboardingImage(swipeView.depth + 1),
                               "description": internal.getOnboardingText(swipeView.depth + 1),
                               "view": swipeView,
                               "id": swipeView.depth == 2 ? -666 : -1
                           })
        }
    }

    Component {
        id: onboardingPage

        OnboardingPage {}
    }

    StackView {
        id: swipeView

        property variant responsesArray: []

        anchors.fill: parent
        clip: true

        initialItem: OnboardingPage {
            view: swipeView
            imgSource: internal.getOnboardingImage(1)
            description: internal.getOnboardingText(1)
        }
    }

    Rectangle {
        anchors {
            bottom: parent.bottom
            bottomMargin: Ui.dip(5)
            horizontalCenter: parent.horizontalCenter
        }
        radius: Ui.dip(10)
        width: indicator.width
        height: indicator.height
        visible: swipeView.depth <= 2
        opacity: 0.0

        Behavior on opacity {
            OpacityAnimator { duration: 1000 }
        }

        PageIndicator {
            id: indicator

            anchors.centerIn: parent
            currentIndex: swipeView.depth - 1
            count: 3
            interactive: true
        }

        Component.onCompleted: {
            opacity = 1.0
        }
    }

    Connections {
        property Item rootPage: null

        target: swipeView.currentItem
        onNext: {
            if (responseIndex == 4) {
                swipeView.push(questionPage, {
                                   "view": swipeView,
                                   "title": _pagesModel.rootPage.title,
                                   "textQuestion": _pagesModel.rootPage.textQuestion,
                                   "responses": _pagesModel.rootPage.responses,
                                   "id": _pagesModel.rootPage.id,
                                   "nextQuestions": _pagesModel.rootPage.nextQuestions
                               })
                return;
            }

            if (responseIndex == -666) {
                swipeView.pop(swipeView.find(function(item) {
                    return item.id == responseIndex;
                }));
                return;
            }

            var nextPage = _pagesModel.page(swipeView.currentItem.nextQuestions[responseIndex])

            var responseObject = JSON.parse('{"'+swipeView.currentItem.id+'":'+responseIndex+'}');
            swipeView.responsesArray.push(responseObject)

            if (!nextPage) {
                swipeView.push(resultPage, {
                                   "view": swipeView,
                                   "decision":  _decisionResolver.resolveDecision(swipeView.responsesArray)
                               })
                swipeView.responsesArray = []
                return;
            }

            swipeView.push(questionPage, {
                               "view": swipeView,
                               "title": nextPage.title,
                               "textQuestion": nextPage.textQuestion,
                               "responses": nextPage.responses,
                               "id": nextPage.id,
                               "nextQuestions": nextPage.nextQuestions
                           })
        }

        onBack: {
            swipeView.responsesArray.pop();
            swipeView.pop();
        }
    }

    Component {
        id: questionPage

        QuestionPage {}
    }

    Component {
        id: resultPage

        ResultPage {}
    }

    StateGroup {
        states: [
            State {
                when: internal.onboardingReady
                AnchorChanges {
                    target: swipeView
                    anchors {
                        left: verticalSeparator.right
                        top: headerContainer.bottom
                        bottom: root.bottom
                        right: root.right
                    }
                }
            }
        ]
    }
}

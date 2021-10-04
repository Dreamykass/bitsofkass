import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    SwipeView {
        id: homeSwipeView

        currentIndex: 1
        anchors.fill: parent

        Training {}
        History {}
    }

    PageIndicator {
        id: homeSwipeViewIndicator

        count: homeSwipeView.count
        currentIndex: homeSwipeView.currentIndex

        anchors.bottom: homeSwipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        y: 30
        text: qsTr("home")
    }
}

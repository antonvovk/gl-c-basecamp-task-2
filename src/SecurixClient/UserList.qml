import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.3

import user.list.model 1.0

Page {
    id: root

    header: ChatToolBar {
        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }

        Label {
            text: qsTr("Users list")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 20
        model: SqlUserListModel {}
        delegate: ItemDelegate {
            text: model.display
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: 40
            leftPadding: 72

        }
    }
}

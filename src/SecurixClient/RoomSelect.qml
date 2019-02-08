import QtQuick 2.12
import QtQuick.Controls 2.12


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
            id: pageTitle
            text: "Almost done!"
            font.pixelSize: 20
            anchors.centerIn: parent
        }

    }

    RoundButton {
        id: join
        x: 150
        y: 382
        width: 241
        height: 52
        text: "<font color='#2494f4'>Join</font>"
        font.pointSize: 10
        highlighted: false

        onClicked: {
            back_end.connectToSecureHost();
            back_end.updateCurrentRoom(roomname.text);
            back_end.notifyServerOfNewConnection(roomname.text);
            root.StackView.view.push("qrc:/ConversationPage.qml", { inConversationWith: roomname.text });
        }
    }

    TextField {
        id: roomname
        x: 150
        y: 140
        width: 241
        height: 40
        antialiasing: false
        placeholderText: qsTr("Room name")
        font.pointSize: 10
        smooth: false
    }

    Label {
        id: label4
        x: 96
        y: 93
        text: qsTr("Enter name of room you want to join")
        font.pointSize: 16
    }


}

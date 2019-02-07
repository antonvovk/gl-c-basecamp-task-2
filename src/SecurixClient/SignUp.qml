import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.3

Page {
    id: root

    property string inConversationWith

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
            text: "Registration"
            font.pixelSize: 20
            anchors.centerIn: parent
        }

    }

    TextField {
        id: username
        x: 150
        y: 107
        width: 241
        height: 40
        antialiasing: false
        placeholderText: qsTr("Username")
        font.pointSize: 10
        smooth: false
    }

    TextField {
        id: password
        x: 150
        y: 180
        width: 241
        height: 40
        antialiasing: false
        placeholderText: qsTr("Password")
        font.pointSize: 10
        smooth: false
    }

    TextField {
        id: name
        x: 150
        y: 253
        width: 241
        height: 40
        antialiasing: false
        placeholderText: qsTr("Full name")
        font.pointSize: 10
        smooth: false
    }

    RoundButton {
        id: logIn
        x: 150
        y: 381
        width: 241
        height: 52
        text: "<font color='#2494f4'>Sign Up</font>"
        font.pointSize: 10
        highlighted: false

        onClicked: {
            back_end.addNewUserToDB(username.text, password.text, name.text);
            stackView.pop();
        }
    }


}

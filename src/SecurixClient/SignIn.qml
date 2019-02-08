import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

Page {
    id: element
    smooth: false
    clip: false
    visible: true
    antialiasing: false

    TextField {
        id: username
        x: 150
        y: 117
        width: 241
        height: 40
        placeholderText: qsTr("Username")
        font.pointSize: 10
        antialiasing: false
        smooth: false
    }

    TextField {
        id: password
        x: 150
        y: 179
        width: 241
        height: 40
        placeholderText: qsTr("Password")
        font.pointSize: 10
        smooth: false
        antialiasing: false
    }

    RoundButton {
        id: logIn
        x: 150
        y: 391
        width: 241
        height: 52
        text: "<font color='#2494f4'>Sign In</font>"
        font.pointSize: 10
        highlighted: false

        function checkCredentialsJS() {
            if (back_end.checkCredentialsWithDB(username.text, password.text) === true) {
                back_end.initFirstStage(server.text, port.text, username.text);
                stackView.push(room_select);
                error.text = "";
            }
            else {
                error.text = "The username or password is incorrect";
            }
        }

        onClicked: {
            checkCredentialsJS();
        }
    }

    Switch {
        id: advancedSwitch
        x: 405
        y: 547
        text: qsTr("Advanced")


        function handleState(switch_state) {
            if (switch_state === 1) {
                server.visible = true;
                port.visible = true;
            }
            else {
                server.visible = false;
                port.visible = false;
            }
        }

        onCheckedChanged: {
            handleState(advancedSwitch.position)
        }
    }

    TextField {
        id: server
        x: 150
        y: 245
        width: 241
        height: 40
        placeholderText: qsTr("Server IP")
        font.pointSize: 10
        visible: false
    }

    TextField {
        id: port
        x: 150
        y: 307
        width: 241
        height: 40
        placeholderText: qsTr("Server port")
        font.pointSize: 10
        visible: false
    }

     Label {
         id: label4
         x: 199
         y: 35
         text: qsTr("Welcome back!")
         font.pointSize: 16
     }

     Label {
         id: label
         x: 176
         y: 474
         width: 142
         height: 13
         text: qsTr("Don't have and account yet?")
     }

     Text {
         width: 41
         height: 13
         anchors.centerIn: parent
         text: "<font color=\"#2494f4\"> <a href='http://localhost' style='color:red'>Sign Up</a> </font>"
         anchors.verticalCenterOffset: 1
         anchors.horizontalCenterOffset: 71

         onLinkActivated: {
             stackView.push(sign_up);
         }

         MouseArea {
             anchors.rightMargin: 0
             anchors.bottomMargin: 0
             anchors.leftMargin: 0
             anchors.topMargin: 0
             anchors.fill: parent
             acceptedButtons: Qt.NoButton
             cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
         }
     }

     Label {
         id: error
         x: 176
         y: 226
         color: "#aa0000"
     }
}



















/*##^## Designer {
    D{i:0;autoSize:true;height:960;width:540}
}
 ##^##*/

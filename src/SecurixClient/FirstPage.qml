import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Item {
    id: element
    smooth: false
    clip: false
    visible: true
    antialiasing: false

    TextField {
        id: username
        x: 200
        y: 92
        width: 241
        height: 40
        font.pointSize: 10
        antialiasing: false
        smooth: false
    }

    TextField {
        id: roomname
        x: 200
        y: 154
        width: 241
        height: 40
        font.pointSize: 10
        smooth: false
        antialiasing: false
    }

    Label {
        id: label
        x: 122
        y: 98
        text: qsTr("Username:")
        font.pointSize: 11
    }

    Label {
        id: label1
        x: 114
        y: 160
        text: qsTr("Roomname:")
        font.pointSize: 11
    }

    Button {
        id: startBtn
        x: 271
        y: 328
        text: qsTr("Go")
        font.pointSize: 10
        highlighted: false

        onClicked: {
            back_end.connectToSecureHost(server.text, port.text, username.text, roomname.text);
            stack.push(second_page);
        }

    }

    Switch {
        id: advancedSwitch
        x: 511
        y: 432
        text: qsTr("Advanced")


        function handleState(switch_state) {
            if (switch_state === 1) {
                server.visible = true;
                port.visible = true;
                label2.visible = true;
                label3.visible = true;
            }
            else {
                server.visible = false;
                port.visible = false;
                label2.visible = false;
                label3.visible = false;
            }
        }

        onCheckedChanged: {
            handleState(advancedSwitch.position)
        }
    }

    TextField {
        id: server
        x: 200
        y: 220
        width: 241
        height: 40
        text: "127.0.0.1"
        font.pointSize: 10
        visible: false
    }

    TextField {
        id: port
        x: 200
        y: 282
        width: 241
        height: 40
        text: "4444"
        font.pointSize: 10
        visible: false
    }

    Label {
        id: label2
        x: 148
        y: 222
        text: qsTr("Server:")
        font.pointSize: 11
        visible: false
    }

    Label {
        id: label3
        x: 163
        y: 284
        text: qsTr("Port:")
        font.pointSize: 11
        visible: false
    }

}































































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

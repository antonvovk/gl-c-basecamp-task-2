import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Item {
    smooth: false
    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 439
        height: 380
        color: "#dcdcdc"
        radius: 0
        border.width: 1
        border.color: "#ededed"

        TextEdit {
            id: history
            x: 0
            y: 0
            width: 439
            height: 380
            color: "#ca7a02"
            text: qsTr("")
            font.family: "MS Shell Dlg 2"
            selectionColor: "#2a2323"
            smooth: false
            font.pixelSize: 13
        }
    }

    Rectangle {
        id: rectangle1
        x: 461
        y: 0
        width: 179
        height: 380
        color: "#dcdcdc"
        border.width: 1
        border.color: "#ededed"

        TextEdit {
            id: users
            x: 0
            y: 0
            width: 179
            height: 380
            color: "#ca7c02"
            font.pixelSize: 13
        }
    }

    TextField {
        id: message
        x: 8
        y: 419
        width: 431
        height: 40
        font.pointSize: 12

        onAccepted: {
            back_end.sendMessage(message.text)
            message.clear()
        }

    }

    Button {
        id: send
        x: 461
        y: 419
        width: 79
        height: 40
        text: qsTr("Send")

        onClicked: {
            back_end.sendMessage(message.text)
            message.clear()
        }


    }

    Button {
        id: disconnect
        x: 553
        y: 419
        width: 79
        height: 40
        text: qsTr("Disconnect")

        onClicked: {
            back_end.disconnectFromSecureHost()
            history.clear()
            users.clear()
            stack.push(first_page)
        }


    }

    Connections {
        target: back_end
        function handleDoUiData(historyB, users_listB) {
            if(!(historyB === "")) {
                history.append(historyB)
            }
            users.text = users_listB
        }

        onDoUiData: {
          handleDoUiData(historyB, users_listB)
        }
    }

}







































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

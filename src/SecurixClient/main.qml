import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3


ApplicationWindow {
    Material.theme: Material.White
    Material.accent: Material.Blue

    id: window
    width: 540
    height: 960
    visible: true
    title: qsTr("Securix")

    StackView {
            id: stackView
            anchors.fill: parent
            initialItem: sign_in
    }

    Component {
        id: sign_in
        SignIn {

        }
    }

    Component {
        id: sign_up
        SignUp{

        }
    }

    Component {
        id: room_select
        RoomSelect {

        }
    }

    Component {
        id: conversation_page
        ConversationPage {

        }
    }

    Component {
        id: user_list
        UserList {

        }
    }
}




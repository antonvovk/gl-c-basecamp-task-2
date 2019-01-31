import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    visible: true

    Material.theme: Material.White
    Material.accent: Material.Orange

    width: 640
    height: 480
    title: qsTr("Securix")

    StackView {
        id: stack
        initialItem: first_page
    }

    Component {
        id: first_page
        FirstPage {

        }
    }

    Component {
        id: second_page
        SecondPage {

        }
    }
}


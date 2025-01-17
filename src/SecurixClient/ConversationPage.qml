import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import conversation.model 1.0

Page {
    id: root

    property string inConversationWith

    header: ChatToolBar {
        ToolButton {
            text: qsTr("Disconnect")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                back_end.updateCurrentRoom("");
                back_end.notifyServerOfDisconnect(inConversationWith);
                root.StackView.view.pop();
            }
        }

        Label {
            id: pageTitle
            text: inConversationWith
            font.pixelSize: 20
            anchors.centerIn: parent
        }

        ToolButton {
            text: qsTr("Members list")
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: stackView.push(user_list);
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12
            model: SqlConversationModel {
                recipient: inConversationWith
            }
            delegate: Column {
                anchors.right: sentByMe ? parent.right : undefined
                spacing: 6


                readonly property bool sentByMe: back_end.getAuthor() === model.author

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined


                    Label {
                        id: messageTextf
                        text: sentByMe ? ' ' : model.author + ':'
                        font.pixelSize: 12
                        topPadding: 10
                    }

                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24, listView.width - 40 - messageRow.spacing)
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "#2494f4"

                        Label {
                            id: messageText
                            text: model.message
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }

                Label {
                    id: timestampText
                    text: Qt.formatDateTime(model.timestamp, "d MMM hh:mm")
                    color: "lightgrey"
                    anchors.right: sentByMe ? parent.right : undefined
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            Layout.fillWidth: true

            RowLayout {
                width: parent.width

                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Compose message")
                    wrapMode: TextArea.Wrap
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")
                    enabled: messageField.length > 0
                    onClicked: {
                        listView.model.sendMessage(inConversationWith, messageField.text);
                        back_end.notifyServerOfNewMessage();
                        messageField.text = "";
                    }
                }
            }
        }
    }

    Connections {
        target: back_end

        onDoUiData: {
          listView.model.updateFromDB();
        }
    }
}


import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.3

Item {
    id: content
    
    width: 400
    height: 400
    
    property bool connected: false
    property alias progressBar: progressBar
    property alias hostname: textHostname
    property alias publishingPort: textPublishPort
    property alias messagingPort: textMessagePort
    property alias cancelButton: actionButton
    
    states: [
        State {
            name: "ConnectingState"
            when: !connected
            
            PropertyChanges {
                target: labelConnectionState
                text: qsTr("Connecting...")
            }
            
            PropertyChanges {
                target: gridLayout
                visible: false
            }
            
            PropertyChanges {
                target: actionButton
                visible: true
            }
        },
        
        State {
            name: "ConnectedState"
            when: connected
            
            PropertyChanges {
                target: labelConnectionState
                text: qsTr("Discovery...")
            }
            
            PropertyChanges {
                target: actionButton
                text: "Continue"
                isDefault: true
                visible: true
            }
            
            PropertyChanges {
                target: progressBar
                visible: false
            }
            
            PropertyChanges {
                target: chargerImage
                x: 84
                y: 237
                anchors.bottomMargin: 20
                visible: false
            }
        },
        State {
            name: "GetDevicesState"
            PropertyChanges {
                target: labelConnectionState
                text: qsTr("Connected!")
            }

            PropertyChanges {
                target: actionButton
                text: "Continue"
                visible: true
                isDefault: true
            }

            PropertyChanges {
                target: progressBar
                visible: false
            }

            PropertyChanges {
                target: chargerImage
                x: 84
                y: 237
                visible: true
                anchors.bottomMargin: 20
            }
        }]
    
    Label {
        id: labelConnectionState
        y: 33
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        font.pointSize: 44
        anchors.left: parent.left
        anchors.right: parent.right
        horizontalAlignment: Text.AlignHCenter
    }
    
    ProgressBar {
        id: progressBar
        x: 100
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: labelConnectionState.bottom
        anchors.topMargin: 16
        indeterminate: true
    }
    
    GridLayout {
        id: gridLayout
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: progressBar.bottom
        
        anchors.topMargin: 12
        
        rows: 3
        columns: 2
        rowSpacing: 8
        columnSpacing: 8
        
        // hostname        
        Label {
            id: labelHostname
            text: qsTr("Hostname/Server:")
            anchors.right: textHostname.left
            anchors.rightMargin: 12
            horizontalAlignment: Text.AlignRight
        }
        
        TextField {
            id: textHostname
            readOnly: true
            placeholderText: qsTr("Hostname")
            Layout.fillWidth: true
            Layout.minimumWidth: 220
        }
        
        // publishing
        Label {
            id: labelPublishPort
            text: qsTr("Publisher Port:")
            anchors.right: textPublishPort.left
            anchors.rightMargin: 12
            horizontalAlignment: Text.AlignRight
        }    
        
        TextField {
            id: textPublishPort
            readOnly: true
            placeholderText: qsTr("Publisher Port")
        }
        
        // messaging
        Label {
            id: labelMessage
            text: qsTr("Messaging Port:")
            anchors.right: textMessagePort.left
            anchors.rightMargin: 12
            horizontalAlignment: Text.AlignRight
        }    
        
        TextField {
            id: textMessagePort
            readOnly: true
            placeholderText: qsTr("Messaging Port")
        }
        
    }
    // cancel me...
    Button {
        id: actionButton
        x: 162
        y: 349
        text:  "Cancel"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
    }
    
    Image {
        id: chargerImage
        x: 84
        y: 240
        width: 233
        height: 87
        fillMode: Image.PreserveAspectFit
        visible: false
        anchors.bottom: actionButton.top
        anchors.bottomMargin: 15
        source: "images/icharger_4010_duo.png"
    }
    
}


import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4

Item {
    id: content
    
    width: 400
    height: 400
    
    property bool connected: false
    property alias hostname: textHostname.text
    property alias publishingPort: textPublishPort.text
    property alias messagingPort: textMessagePort.text
    property alias cancelButton: actionButton
    property alias connectionMessage: labelConnectionState.text
    property alias modelView: modelView
    
    states: [
        State {
            name: "ConnectingState"
            when: !connected
            
            PropertyChanges {
                target: labelConnectionState
                text: qsTr("Connecting...")
            }
            
            PropertyChanges {
                target: gridForConnectionDetails
                visible: true
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
                text: qsTr("Choose Device...")
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
                target: gridForConnectionDetails
                visible: false
            }
            
            PropertyChanges {
                target: gridForDeviceSelection
                anchors.bottomMargin: 12
                rows: 1
                columns: 1
                opacity: 1
            }
            
            PropertyChanges {
                target: modelView
                visible: true
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
        id: gridForConnectionDetails
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
    
    GridLayout {
        id: gridForDeviceSelection
        width: 100
        height: 100
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.bottomMargin: 12
        anchors.top: labelConnectionState.bottom
        anchors.right: gridForConnectionDetails.left
        anchors.bottom: actionButton.top
        anchors.left: gridForConnectionDetails.right
        anchors.topMargin: 16
        opacity: 0
        
        ListView {
            id: modelView
            anchors.fill: parent
            visible: false
            delegate: Row {
                Text {
                    text: model.modelData.serialNumber
                    width: parent.width
                    horizontalAlignment: Text.AlignLeft
                }
                Text {
                    text: model.modelData.softwareVersion
                    width: parent.width
                    horizontalAlignment: Text.AlignLeft
                }
                Text {
                    text: model.modelData.hardwareVersion
                    width: parent.width
                    horizontalAlignment: Text.AlignLeft
                }
            }
        }
    }
}


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
    property alias publishingPort: textPubPort
    property alias messagingPort: textMessagingPort
    property alias cancelButton: cancelButton
    
    states: [
        State {
            name: "ConnectingState"
        when: !connected

        PropertyChanges {
            target: labelConnectionState
            text: qsTr("Finding Charger...")
        }
        
        PropertyChanges {
            target: gridLayout
            visible: false
        }
        
        PropertyChanges {
            target: cancelButton
            visible: true
        }
        },
        
    State {
        name: "ConnectedState"
        when: connected

        PropertyChanges {
            target: labelConnectionState
            text: qsTr("Connected")
        }
        
        PropertyChanges {
            target: cancelButton
            visible: false
        }
    }]
    
    Label {
        id: labelConnectionState
        y: 73
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
            id: labelPublisherPort
            text: qsTr("Publisher Port:")
            anchors.right: textPubPort.left
            anchors.rightMargin: 12
            horizontalAlignment: Text.AlignRight
        }    

        TextField {
            id: textPubPort
            readOnly: true
            placeholderText: qsTr("Publisher Port")
        }
        
    // messaging
        Label {
            id: labelMessaging
            text: qsTr("Messaging Port:")
            anchors.right: textMessagingPort.left
            anchors.rightMargin: 12
            horizontalAlignment: Text.AlignRight
        }    
        
        TextField {
            id: textMessagingPort
            readOnly: true
            placeholderText: qsTr("Messaging Port")
        }
        
    }
    // cancel me...
    Button {
        id: cancelButton
        x: 162
        y: 349
        text:  "Cancel"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
    }
    
}


import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4

Item {
    id: content
    
    width: 400
    height: 250
    
    property bool connected: false
    property int device_count: 0
    
    property alias connectionLabel: labelConnectionState
    
    property alias actionButton: actionButton
    property alias connectionMessage: labelConnectionState.text
    
    states: [
        State {
            name: "ConnectingState"
            when: !connected
                        
            PropertyChanges {
                target: explanation
                visible: true
            }
            
            PropertyChanges {
                target: actionButton
                visible: true
            }
            
            PropertyChanges {
                target: content
                height: 300
            }
        },
        
        State {
            name: "FindDevicesState"
            when: connected && device_count == 0
                        
            PropertyChanges {
                target: actionButton
                visible: true
            }
            
            PropertyChanges {
                target: progressBar
                visible: false
            }
        }
    ]
    
    Image {
        id: background
        source: "qrc:/images/looking.png"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        opacity: 0.2
    }
    
    Label {
        id: labelConnectionState
        anchors.top: parent.top
        anchors.topMargin: 18
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        font.pointSize: 44
        anchors.left: parent.left
        anchors.right: parent.right
        horizontalAlignment: Text.AlignHCenter
    }
    
    ProgressBar {
        id: progressBar
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: labelConnectionState.bottom
        anchors.topMargin: 16
        indeterminate: true
    }
    
    GroupBox {
        id: explanation
        
        anchors.top: progressBar.bottom
        anchors.bottom: actionButton.top
        anchors.left: parent.left
        anchors.right: parent.right
        
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 16
        anchors.bottomMargin: 12

        visible: false       
        opacity: 1
        
        Text {
            text: qsTr("The application is trying to find the server that is connected to your battery charger, please make sure its running.  This can take a few moments...")
            anchors.fill: parent
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
        }
    }

    Button {
        id: actionButton
        isDefault: true
        text:  qsTr("Quit")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
    }
    
}


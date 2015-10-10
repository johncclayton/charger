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
    
    property alias cancelButton: actionButton
    property alias connectionMessage: labelConnectionState.text
    property alias modelView: modelView
    
    states: [
        State {
            name: "ConnectingState"
            when: !connected
                        
            PropertyChanges {
                target: actionButton
                visible: true
            }
            
            PropertyChanges {
                target: content
                height: 300
            }
            
            PropertyChanges {
                target: layoutForDeviceSelection
                rowSpacing: 5
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
            
            PropertyChanges {
                target: layoutForDeviceSelection
                visible: false
            }
            
            PropertyChanges {
                target: modelView
                visible: false
            }
        },
        
        State {
            name: "FoundDevicesState"
            when: connected && device_count > 0
            
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
                target: layoutForDeviceSelection
                visible: true
            }
            
            PropertyChanges {
                target: modelView
                visible: true
            }
        }
    ]
    
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
    
    Button {
        id: actionButton
        isDefault: true
        text:  qsTr("Quit")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
    }
    
    GridLayout {
        id: layoutForDeviceSelection
        
        visible: false
        
        anchors.top: labelConnectionState.bottom
        anchors.bottom: actionButton.top
        anchors.left: parent.left
        anchors.right: parent.right
        
        anchors.topMargin: 16
        anchors.bottomMargin: 12
            
        ListView {
            id: modelView
                        
            anchors.top: layoutForDeviceSelection.top
            anchors.left: layoutForDeviceSelection.left 
            anchors.right: layoutForDeviceSelection.right
            anchors.bottom: layoutForDeviceSelection.bottom
            anchors.leftMargin: 30
            anchors.rightMargin: 30
            
            visible: false
            focus: true
            
            highlight: Rectangle { 
                radius: 5
                color: "blue"
                opacity: 0.1
            }
            
            delegate: DeviceDelegate {
                width: modelView.width
                
                product: model.modelData.product
                image.source: model.modelData.imageSource
                manufacturer: model.modelData.manufacturer
                serialNumber: model.modelData.serialNumber
                
                MouseArea {
                    anchors.fill: parent
                    onClicked: modelView.currentIndex = index
                }                                    
            }
        }
        
    }
}


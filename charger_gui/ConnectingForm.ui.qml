import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4

Item {
    id: content
    
    width: 400
    height: 250
    
    property bool connected: false
    property string connectingString: qsTr("Connecting...")
    property string chooseDeviceString: qsTr("Choose Device...")
    property int itemWidth: 50
    property alias cancelButton: actionButton
    property alias connectionMessage: labelConnectionState.text
    property alias modelView: modelView
    
    states: [
        State {
            name: "ConnectingState"
            when: !connected
            
            PropertyChanges {
                target: labelConnectionState
                text: connectingString
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
            name: "ConnectedState"
            when: connected
            
            PropertyChanges {
                target: labelConnectionState
                text: chooseDeviceString
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
                target: gridForDeviceSelection
                opacity: 1
                visible: true
            }
            
            PropertyChanges {
                target: modelView
                keyNavigationWraps: false
                visible: true
            }
            
            PropertyChanges {
                target: content
                height: 380
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
        
        width: 300
        visible: false
        
        anchors.bottom: actionButton.top
        anchors.bottomMargin: 12
        anchors.top: labelConnectionState.bottom
        anchors.topMargin: 16
        anchors.horizontalCenter: parent.horizontalCenter
        
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        
        opacity: 0
        
        ListView {
            id: modelView
            highlightMoveDuration: 200
            keyNavigationWraps: true
            anchors.fill: parent
            visible: false
            
            highlight: Rectangle { 
                color: "lightsteelblue"
                radius: 5
            }
            
            focus: true
            
            delegate: Rectangle {
                anchors.fill: parent
                height: 50
                
                border.color: "black"
                border.width: 12
                radius: 14
                                                
                GridLayout {
                    rows: 3
                    columns: 3
                    rowSpacing: 8
                    columnSpacing: 18
                    
                    Image {
                        source: model.modelData.imageSource
                        
                        sourceSize.width: 90
                        sourceSize.height: 90
                        
                        width: 90
                        height: 90
                        
                        fillMode: Image.PreserveAspectFit        
                        Layout.rowSpan: 3
                    }
                                        
                    // row 2
                    Label {
                        id: labelProduct
                        text: "Product:"
                        anchors.right: textProduct.left
                        anchors.rightMargin: 12
                        horizontalAlignment: Text.AlignRight                        
                    }

                    Text {
                        id: textProduct
                        text: model.modelData.product
                        horizontalAlignment: Text.AlignLeft
                    }
                    
                    // row 3
                    Label {
                        id: labelManufacturer
                        text: "Manufacturer:"
                        anchors.right: textManufacturer.left
                        anchors.rightMargin: 12
                        horizontalAlignment: Text.AlignRight                        
                    }

                    Text {
                        id: textManufacturer
                        text: model.modelData.manufacturer
                        horizontalAlignment: Text.AlignLeft
                    }
                    
                    // row 1 - serial
                    Label {
                        id: labelSerialNumber
                        text: "Serial Number:"
                        anchors.right: textSerialNumber.left
                        anchors.rightMargin: 12
                        horizontalAlignment: Text.AlignRight                        
                    }
                    
                    Text {
                        id: textSerialNumber
                        text: model.modelData.serialNumber
                        horizontalAlignment: Text.AlignLeft
                    }
                    
                }
            }
        }
    }
}


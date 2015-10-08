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
    
    property string connectingString: qsTr("Connecting...")
    property string chooseDeviceString: qsTr("Choose Device...")
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
            
            PropertyChanges {
                target: layoutForDeviceSelection
                rowSpacing: 5
            }
        },
        
        State {
            name: "FindDevicesState"
            when: connected && device_count == 0
            
            PropertyChanges {
                target: labelConnectionState
                text: chooseDeviceString
            }
            
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
            
            PropertyChanges {
                target: content
                height: 380
            }
            
            PropertyChanges {
                target: infoRect
                opacity: 1
            }
        },
        
        State {
            name: "FoundDevicesState"
            when: connected && device_count > 0
            
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
                target: layoutForDeviceSelection
                visible: true
            }
            
            PropertyChanges {
                target: modelView
                visible: true
            }
            
            PropertyChanges {
                target: content
                height: 380
            }
            
            PropertyChanges {
                target: infoRect
                opacity: 0
            }
        }
    ]
    
    Image {
        anchors.fill: parent
        opacity: 0.08
        source: "qrc:/images/icharger_308_duo.png"
        fillMode: Image.PreserveAspectFit
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
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
        x: 100
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: labelConnectionState.bottom
        anchors.topMargin: 16
        indeterminate: true
    }
    
    Button {
        id: actionButton
        x: 162
        y: 349
        isDefault: true
        text:  qsTr("Quit")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
    }
    
    GridLayout {
        id: layoutForDeviceSelection
        
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50
        visible: false
        
        anchors.bottom: actionButton.top
        anchors.bottomMargin: 12
        anchors.top: labelConnectionState.bottom
        anchors.topMargin: 16
        
        ListView {
            id: modelView
            
            anchors.fill: parent
            visible: false
            focus: true
            
            highlight: Rectangle { 
                radius: 5
                color: "blue"
                opacity: 0.1
            }
            
            delegate: Rectangle {
                
                height: 80
                width: modelView.width
                
                color: "transparent"
                Layout.margins: 12
                
                MouseArea {
                    anchors.fill: parent
                    onClicked: modelView.currentIndex = index
                    
                }                
                
                GridLayout {
                    rows: 3
                    columns: 3
                    rowSpacing: 5
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
                    
                    // product
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
                    
                    // manufacturer
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
                    
                    // serial
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
        
        Item {
            id: infoRect
            anchors.fill: parent
            opacity: 0
            
            Text {
                id: textDescription
                text: qsTr("Dilligently looking for devicess to take control of... please wait.")
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 18
            }
        }
    }
}


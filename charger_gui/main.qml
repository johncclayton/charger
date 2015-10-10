import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    
    width: 400
    height: 220
    minimumWidth: 400
    minimumHeight: 120
    
    title: qsTr("Charger")
    
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    
    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            
            Label {
                text: comms.hostname
            }
            
            Label {
                Layout.alignment: Qt.AlignRight
                Binding on text {
                    value: {
                        if(!devicesModel.count)
                            return "Searching for devices..."
                        
                        if(devicesModel.count === 1)
                            devicesModel.count + " device";
                        else 
                            devicesModel.count + " devices";
                    }
                }
            }
        }
    }
    
//    Connecting {
//        id: connectionState
//        anchors.fill: parent
                
//        cancelButton.onClicked: {
//            if(connected) {
//                // TODO: Device Request + Selection
//                // lets ask the system for all the device information, then we move
//                // onto device selection - which is automatic if there's only a single device.
//            } else {
//                Qt.quit()
//            }
//        }
//    }

    RowLayout { 
        id: mycharger
        spacing: 80

        anchors.fill: parent
    
        Channel {
            id: channel1
            panelHeaderTitleLeft.text: "01-Cycle"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: (parent.width/2) - 1
            
        }

        Channel {
            id: channel2
            panelHeaderTitleLeft.text: "02-Balance"
            panelBorderColor: "darkgreen"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: (parent.width/2) - 1
        }
    }
}


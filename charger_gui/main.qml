import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    
    width: 640
    height: 480
    
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

    Connecting {
        anchors.fill: parent
        
        cancelButton.onClicked: {
            if(connected) {
                // TODO: Device Request + Selection
                // lets ask the system for all the device information, then we move
                // onto device selection - which is automatic if there's only a single device.
            } else {
                Qt.quit()
            }
        }
        
    }    
}


import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Charger")

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")
        
        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
    
    Channel {
        id: channelForm1
        x: 0
        y: 10
        width: parent.width / 2
        height: 269
    }
    
    Channel {
        id: channelForm2
        x: parent.width / 2
        y: 10
        width: parent.width / 2
        height: 269
    }
    
    menuBar: MenuBar {
        Menu {
            title: qsTr("Devices")
            MenuItem {
                text: qsTr("&Choose device")
                onTriggered: console.log("Choose device triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    
}


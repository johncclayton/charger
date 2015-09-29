import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")
        
        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
    
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    
    MainForm {
        anchors.fill: parent
        button1.onClicked: messageDialog.show(qsTr("Woot"))
        button2.onClicked: messageDialog.show(qsTr("Button 2 pressed"))
    }
    
}


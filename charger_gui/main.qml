import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    
    width: 640
    height: 380
    
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
    
//    Window {
//        id: splash
//        color: "transparent"
//        title: "Splash Window"
//        modality: Qt.ApplicationModal
//        flags: Qt.SplashScreen
//        x: (Screen.width - splashImage.width) / 2
//        y: (Screen.height - splashImage.height) / 2
//        width: splashImage.width
//        height: splashImage.height
        
//        Image {
//            id: splashImage
//            source: "qrc:/images/icharger_308_duo.png"
//            MouseArea {
//                anchors.fill: parent
//                onClicked: Qt.quit()
//            }
//        }
        
//        visible: true
//    }
    
    Connecting {
        id: connectionState
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


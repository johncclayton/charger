import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4

ApplicationWindow {
    visible: true
    
    width: 530
    height: 300
    
    minimumWidth: 500
    minimumHeight: 240
    
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
    
    Connections {
        target: devicesModel
        onDeviceAddedRemoved: {
            // C++ signal sig: void deviceAddedRemoved(bool added, QString key);
            if(added) {
                // what's the product type? so we can construct an interface
                stack.createChargerInterfaceForKey(key);
            } else {
                // remove a child with this object name...
                stack.removeChargerInterfaceForKey(key);
            }
        }
        
        onDeviceInfoUpdated: {
            console.log("data was updated for key" + key);
        }
    }
    
    
    StackView {
        id: stack
        initialItem: connectServer
        anchors.fill: parent
        
        function createChargerInterfaceForKey(key) {
            var component = Qt.createComponent("ChargerDuo.qml");
            if (component.status === Component.Ready) {
                var new_item = component.createObject(stack, {"objectName": key, "width": parent.width, "height": parent.height});
                stack.push(new_item);
            }
            
            return null;
        }
        
        function removeChargerInterfaceForKey(key) {
            for(var i = 0; i < children.length; i++) {
                var item = children[i];
                if(key === item.objectName) {
                    if(item.Stack.status === Stack.Active)
                        pop(null);
                    item.destroy(1000);
                    return;
                }
            }            
        }
        
        ConnectServer {
            id: connectServer
            anchors.fill: parent
            
            actionButton.onClicked: {
                if(connected) {
                    // nada...
                } else {
                    Qt.quit()
                }
            }
        }
    }
}


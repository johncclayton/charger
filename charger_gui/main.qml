import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQml.StateMachine 1.0 

ApplicationWindow {
    id: app
    
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
    
    Accessible.name: "Charger App"
    
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
    }
    
//    StateMachine {
//        id: connectionStateMachine
        
//        initialState: connectingState
        
//        State {
//            id: connectingState
//        }
        
//        State { 
//            id: connectedState 
//        }
        
//        State {
//            id: notStartedState
//        }
        
//        State { 
//            id: runningState
//        }
        
//        State {
//            id: errorState
//        }
        
//        FinalState {
//            id: quittingState
//        }
//    }
        
    StackView {
        id: stack
        initialItem: connectServer
        anchors.fill: parent
               
        property var component;
        
        function finishedLoading(key) {
            if(component.status === Component.Ready) {
                var new_item = component.createObject(stack, {"modelKey": key, "width": parent.width, "height": parent.height});
                if(new_item) {
                    console.log("iCharger DUO UI activated for key:", key);
                    stack.push(new_item);
                } else {
                    console.log("error creating object");           
                }
            } 
            else if(component.status === Component.Error) {
                console.log("Error loading the component:", component.errorString());       
            }
        }
        
        function createChargerInterfaceForKey(key) {
            console.log("activating charger duo...");
            component = Qt.createComponent("icharger/ChargerDuo.qml");
            if(component.status === Component.Ready) {
                finishedLoading(key);
            } else if(component.status === Component.Loading) {
                component.statusChanged.connect(function() { finishedLoading(key) });
            } else if(component.status === Component.Error) {
                console.log("error creating component:", component.errorString());           
            }
        }
        
        function removeChargerInterfaceForKey(key) {
            for(var i = 0; i < children.length; i++) {
                var item = children[i];
                if(key === item.modelKey) {
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


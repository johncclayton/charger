import QtQuick 2.5

ConnectServerForm {
    connected: comms.messageBus.alive
    device_count: devicesModel.count
    modelView.model: devices
        
    onDevice_countChanged: {
        
        // ensure we have instantiated UIs for each model type we understand.
//        console.log("you clicked number: " + modelView.currentIndex + " which is: " + devices[modelView.currentIndex].product)
        
    }
    
    property variant connect_strings: [
        qsTr("Connecting..."),
        qsTr("Contacting the oracle..."),
        qsTr("Checking under the rug..."),
        qsTr("Juggling gigaflops..."),
        qsTr("Flopping jugaflips..."),
        qsTr("Squeezing clouds..."),
        qsTr("Thinking about it..."),
        qsTr("Where's that server?"),
        qsTr("Looking for stuff..."),
        qsTr("Bouncing stuff..."),
    ]    
    
    property variant choose_strings: [
        qsTr("Choose a device..."),
        qsTr("Choose your weapon!"),
        qsTr("What charger?"),
        qsTr("Go ahead, make my day..."),
        qsTr("Pick a charger, any charger"),
        qsTr("Don't be scared - pick one!"),
        qsTr("To charge, or not to charge..."),
        qsTr("How hard can this be?"),
        qsTr("Pick one already!"),
        qsTr("Come on... pick one!"),
        qsTr("Phone a friend maybe?"),
        qsTr("Or just dont..."),
        qsTr("To choose or not to choose..."),
    ]    
    
    property int animTime: 175
    property string newConnectionLabelString: ""
    
    Behavior on connectionLabel.opacity { NumberAnimation { duration: animTime } }
    
    onNewConnectionLabelStringChanged: {
        connectionLabel.opacity = 0
        fadeTimer.running = true
    }
    
    onStateChanged: {
        stateTimer.stop()
        stateTimer.start()
    }
    
    Timer {
        id: stateTimer
        
        repeat: true
        running: true
        interval: 5500
        triggeredOnStart: true
        
        onTriggered: {
            if(device_count > 0)
                newConnectionLabelString = choose_strings[Math.floor(Math.random() * choose_strings.length)];
            else
                newConnectionLabelString = connect_strings[Math.floor(Math.random() * connect_strings.length)];                
        }
    }
    
    Timer {
        id: fadeTimer

        running: false
        repeat: false
        interval: animTime
        
        onTriggered: {
            connectionLabel.text = newConnectionLabelString
            connectionLabel.opacity = 1
        }
    }
    
}


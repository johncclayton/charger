import QtQuick 2.5

ConnectingForm {
    connected: comms.messageBus.alive
    modelView.model: devices
    
    property variant connect_strings: [
        qsTr("Connecting..."),
        qsTr("Contacting the oracle..."),
        qsTr("Looking under the carpet..."),
        qsTr("Juggling gigaflops..."),
        qsTr("Squeezing clouds..."),
        qsTr("Thinking about it..."),
        qsTr("Where's that server?"),
        qsTr("Bouncing stuff..."),
    ]    
    
    property variant choose_strings: [
        qsTr("Choose a device..."),
        qsTr("Choose your weapon!"),
        qsTr("What charger?"),
        qsTr("Go ahead... make my day, punk"),
        qsTr("Pick a charger, any charger"),
        qsTr("Don't be scared - pick one!"),
        qsTr("To charge, or not to charge..."),
        qsTr("Or just dont..."),
    ]    

    Timer {
        repeat: true
        running: true
        interval: 3500
        
        onTriggered: {
            connectingString = connect_strings[Math.floor(Math.random() * connect_strings.length)];
            chooseDeviceString = choose_strings[Math.floor(Math.random() * choose_strings.length)];
        }
    }
}


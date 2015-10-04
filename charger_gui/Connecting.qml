import QtQuick 2.4

ConnectingForm {
    connected: comms.connected
    hostname.text: comms.hostname
    publishingPort.text: comms.publishPort
    messagingPort.text: comms.messagePort
    
}


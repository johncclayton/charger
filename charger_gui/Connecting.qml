import QtQuick 2.5

ConnectingForm {
    connected: comms.messageBus.alive
    hostname: comms.hostname
    publishingPort: comms.publishPort
    messagingPort: comms.messagePort
       
    modelView.model: devices
}


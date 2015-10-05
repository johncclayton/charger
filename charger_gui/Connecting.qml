import QtQuick 2.4

ConnectingForm {
    connected: comms.messageBus
    hostname: comms.hostname
    publishingPort: comms.publishPort
    messagingPort: comms.messagePort
}


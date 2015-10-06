import QtQuick 2.5

ConnectingForm {
    connected: comms.messageBus.alive
    modelView.model: devices
}


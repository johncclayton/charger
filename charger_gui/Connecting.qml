import QtQuick 2.4

ConnectingForm {
    connected: comms.messageBus
    hostname: comms.hostname
    publishingPort: comms.publishPort
    messagingPort: comms.messagePort

    property alias deviceListModel: listModel
    
    JSONListModel {
        id: listModel
        query: "$..device"
    }
    
    modelView.model: listModel
    modelView.delegate: Item {
        x: 5
        width: 80
        height: 40
        
        Text {
            text: model.sn
            width: parent.width
            horizontalAlignment: Text.AlignLeft
        }
    }
}


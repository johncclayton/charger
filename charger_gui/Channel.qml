import QtQuick 2.4

ChannelForm {
    id: channelForm1
    
    Text {
        id: textInputVoltage
        x: 174
        y: 0
        width: 160
        height: 15
        text: qsTr("")
        anchors.right: parent.right
        anchors.rightMargin: 0
        font.pixelSize: 12
    }
    
    Text {
        id: lblInputVoltage
        x: 0
        y: 0
        width: 160
        height: 15
        text: qsTr("Input voltage")
        anchors.right: parent.right
        font.pixelSize: 12
        anchors.rightMargin: 240
    }
    
    Text {
        id: textOutputVoltage
        x: 240
        y: 21
        width: 160
        height: 15
        text: qsTr("")
        anchors.right: parent.right
        font.pixelSize: 12
        anchors.rightMargin: 0
    }
    
    Text {
        id: lblOutputVoltage
        x: 0
        y: 21
        width: 160
        height: 15
        text: qsTr("Output voltage")
        anchors.right: parent.right
        font.pixelSize: 12
        anchors.rightMargin: 240
    }
}


import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4

Item {
    id: content
    width: 400
    height: 400
    
    property alias channelName: labelChannel.text
    property alias inputVoltage: txtInputVoltage.text
    property alias outputVoltage: txtOutputVoltage.text
    
    GridLayout {
        id: gridLayout1
        
        anchors.top: labelChannel.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 8
        rows: 3
        columns: 2
        
        Label {
            id: labelInputVoltage
            text: qsTr("Input Voltage")
        }
        
        TextField {
            id: txtInputVoltage
            readOnly: true
            placeholderText: qsTr("Input Voltage")
        }
        
        Label {
            id: labelOutputVoltage
            text: qsTr("Output Voltage")
        }

        TextField {
            id: txtOutputVoltage
            readOnly: true
            placeholderText: qsTr("Output Voltage")
        }
        
        Item {
            Layout.fillHeight: true
        }
    }
    
    Label {
        id: labelChannel
        text: qsTr("")
        font.pointSize: 17
        anchors.horizontalCenter: parent.horizontalCenter
    }
}


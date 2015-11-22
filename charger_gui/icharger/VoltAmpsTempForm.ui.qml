import QtQuick 2.4
import QtQuick.Layouts 1.1

Rectangle {
    width: 400
    height: 30
    
    color: "black"
        
    property alias label: dclabel
    property alias layoutFields: layoutFields
    
    RowLayout {
        id: layoutFields
        anchors.fill: parent
        spacing: 8
        
        Layout.preferredHeight: preferredHeight
        
        RowLayout {
            Text {
                id: dclabel
                text: 'DC '
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft            
                anchors.left: parent.left
                anchors.top: parent.top
                color: "green"
            }
            
            Text {
                id: dcvalue
                text: voltage + 'V'
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft            
                anchors.left: dclabel.right
                anchors.top: parent.top
                color: textColor
            }
        }
        
        Item {
            id: filler1
            width: 10
        }
        
        Text {
            id: ch1amplabel
            text: ch1amps + 'A'
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft            
            anchors.left: filler1.right
            anchors.top: parent.top
            color: textColor
        }
        
        Item {
            id: filler2
            width: 10
        }
        
        Text {
            id: ch2amplabel
            text: ch2amps + 'A'
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft            
            anchors.left: filler2.right
            anchors.top: parent.top
            color: textColor
        }
        
        Text {
            id: templabel
            text: temperature + (tempIsCentigrade ? 'C' : 'F')
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft            
            anchors.right: parent.right
            anchors.top: parent.top
            color: textColor
        }
    }
}


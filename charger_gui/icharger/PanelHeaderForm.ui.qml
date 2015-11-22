import QtQuick 2.4
import QtQuick.Layouts 1.1

Rectangle {
    width: 400
    height: 250
    
    id: content
    
    property alias headerTitleLeft: titleLeft
    property alias headerTitleRight: titleRight
    
    default property alias contents: contentAreaContainer.children
    
    property alias contentArea: contentAreaContainer
    property alias headerArea: headerCurvedBit
    
    radius: panelRadius
    border.color: panelBorderColor    
    border.width: panelBorderWidth
    color: panelBackgroundColor
    
    RowLayout {
        id: layout
        anchors.fill: parent
        
        Rectangle {
            id: headerCurvedBit
            
            color: panelBorderColor
            
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: titleLeft.bottom
            
            radius: panelRadius
        }
        
        Rectangle {
            id: headerSquareBit
            
            color: panelBorderColor
            anchors.right: parent.right
            anchors.left: parent.left
            
            y: headerCurvedBit.y + headerCurvedBit.height / 2            
            height: headerCurvedBit.height / 2
        }
        
        Text {
            id: titleLeft
            color: panelHeaderTextColor
            text: qsTr("Panel Header")
            font.pixelSize: 20
            horizontalAlignment: Text.AlignLeft
            
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            
            anchors.leftMargin: panelRadius / 2
        }
        
        Text {
            id: titleRight
            color: panelHeaderTextColor
            text: qsTr("<info>")
            font.pixelSize: 20
            horizontalAlignment: Text.AlignRight
            
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            
            anchors.rightMargin: panelRadius / 2
        }
        
        Item {
            id: contentAreaContainer
            
            anchors.top: headerSquareBit.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}


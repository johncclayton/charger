import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Item {
    id: content
    width: 400
    height: 151

    property alias image: deviceImage
    property alias name: labelName.text
    property alias hardwareVersion: labelHwVersion.text
    property alias softwareVersion: labelSwVersion.text
    property alias serialNumber: labelSerialNumber.text
    
    Grid {
        id: grid1
        spacing: 5
        rows: 1
        columns: 2
        anchors.fill: parent
        
        Image {
            id: deviceImage
            width: (parent.width - 10) / 2
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            source: "images/icharger_4010_duo.png"
        }
        
        Column {
            id: detailsColumn
            width: 200
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            spacing: 5
            
            Label {
                id: labelName
                text: qsTr("Name of Device")
                font.pointSize: 17
                font.bold: true
            }
            
            Label {
                id: labelHwVersion
                text: qsTr("h/w")
            }
            
            Label {
                id: labelSwVersion
                text: qsTr("s/w")
            }
            
            Label {
                id: labelSerialNumber
                text: qsTr("serial #")
            }
        }
    }
}


import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4

Item {
    id: item1
    width: 400
    height: 400
    
    Column {
        id: columnLayout
        antialiasing: false
        anchors.rightMargin: 8
        anchors.leftMargin: 8
        anchors.topMargin: 8
        anchors.bottomMargin: 8
        anchors.fill: parent
        spacing: 12
        
        Label {
            id: labelIntro
            text: qsTr("Choose how you would like the application to connect with your charger.")
            horizontalAlignment: Text.AlignLeft
            wrapMode: Text.WrapAnywhere
        }
        
        GroupBox {
            id: groupbox
            height: 300
            anchors.top: parent.top
            anchors.topMargin: 28
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            flat: false
            checked: true
            title: qsTr("Network Mode")
            
            RadioButton {
                id: netOptAuto
                x: 0
                y: 0
                text: qsTr("Automatically")
                checked: true
            }
            
            RadioButton {
                id: netOptManual
                x: 0
                y: 32
                text: qsTr("Manually")
            }
        }
    }
    
    Grid {
        id: grid2
        x: 36
        y: 333
        width: 281
        height: 51
        spacing: 12
        rows: 3
        columns: 2
        
        Text {
            id: text1
            width: 339
            height: 15
            text: qsTr("Text")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
        }
        
        StatusIndicator {
            id: statusIndicator1
            color: "#409d07"
            anchors.verticalCenter: parent.verticalCenter
            active: true
        }
        
    }
    
    
}


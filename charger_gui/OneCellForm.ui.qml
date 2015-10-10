import QtQuick 2.4
import QtQuick.Layouts 1.1

Item {
    width: preferredWidth
    height: preferredHeight
    
    id: content
    
    property string cellNumber: ""
    property string cellValue: "3.75"
    property string cellUnits: 'v'
    
    property int preferredWidth: 0
    property int preferredHeight: 0
    
    property alias label: thelabel
    property alias value: thevalue
    property alias layoutFields: layoutFields
    
    RowLayout {
        id: layoutFields
        
        spacing: 8
        anchors.fill: parent
        anchors.margins: 2
        
        Layout.preferredWidth: preferredWidth
        Layout.preferredHeight: preferredHeight
        Layout.maximumWidth: preferredWidth
        Layout.maximumHeight:  preferredHeight
        
        Item {
            id: thecell
            anchors.fill: parent
                                    
            Text {
                id: thelabel
                text: cellNumber
                width: 20
                horizontalAlignment: Text.AlignLeft            
                anchors.left: parent.left
                anchors.top: parent.top
                color: panelCellNumberColor
            }
            
            Text {
                id: thevalue
                horizontalAlignment: Text.AlignLeft
                text: cellValue + cellUnits
                anchors.left: thelabel.right
                anchors.leftMargin: 0
                color: panelTextColor
            }
        }
    }    
}


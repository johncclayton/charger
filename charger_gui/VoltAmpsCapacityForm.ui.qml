import QtQuick 2.4
import QtQuick.Layouts 1.1

Item {
    id: content 
    
    width: 200
    height: 100
    
    property double voltage: 23.010
    property double amps: 26.84
    property double capacity: 0
    
    property alias textVolts: textVolts
    property alias textAmps:textAmps
    property alias textCapacity: textCapacity
    
    property int minimumLayoutWidth: 0
    property int preferredLayoutHeight: 0
    property alias columnLayout: columnLayout
        
    Rectangle {
        id: rectangle1
        color: "black"
                
        anchors.fill: parent
        radius: panelSmallRadius
        border.color: panelBorderColor
        border.width: 1
        
        ColumnLayout {
            id: columnLayout
            
            anchors.fill: parent
            anchors.margins: 3

            Layout.minimumWidth: minimumLayoutWidth
            Layout.preferredHeight: preferredLayoutHeight
            
            spacing: 4
            
            Text {
                id: textVolts
                text: voltage + ' V'
                anchors.right: parent.right
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                color: panelTextColor
                font.pointSize: voltsFontPixelSize
                font.family: voltsFontFamily
                font.bold: true
            }
            
            Text {
                id: textAmps
                text: amps + ' A'
                anchors.right: parent.right
                horizontalAlignment: Text.AlignVCenter | Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                color: panelTextColor
                font.pointSize: voltsFontPixelSize
                font.family: voltsFontFamily
                font.bold: true
            }
            
            RowLayout {
                id: rowLayout1
                
                anchors.right: parent.right
                anchors.rightMargin: 0
                
                Text {
                    id: textCapacity
                    text: capacity
                    anchors.right: textMAh.left
                    anchors.rightMargin: 5
                    horizontalAlignment: Text.AlignVCenter | Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    color: panelTextColor
                    font.pointSize: voltsFontPixelSize
                    font.family: voltsFontFamily
                    font.bold: true
                }
                
                Text {
                    id: textMAh
                    text: 'mAh'
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignVCenter | Text.AlignRight
                    verticalAlignment: Text.AlignBottom
                    color: panelTextColor
                    font.pointSize: voltsFontPixelSize / 2
                    font.family: voltsFontFamily
                }
            }            
        }
    }
}


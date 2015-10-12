import QtQuick 2.4
import QtQuick.Layouts 1.1

Item {
    id: content
    
    width: 100
    height: 100
        
    property string batteryType: "LiPo6S"
    property string chargeMode: "DISCHARGE" 
    property string timeSpent: "01:12"
    
    property alias content: content    
    property alias textBattery: textBattType
    property alias textCharge: textChargeMode
    property alias textTime: textTime1
    property alias textFiller: filler
    
    property alias layoutFields: layoutFields
    property int preferredLayoutWidth: 0
    property int preferredLayoutHeight: 0
    
    ColumnLayout {
        id: layoutFields
        
        anchors.fill: parent 
        anchors.margins: 2
        Layout.preferredHeight:  preferredLayoutHeight
        Layout.preferredWidth: preferredLayoutWidth
        
        Text {
            id: textBattType
            text: batteryType
            
            horizontalAlignment: Text.AlignLeft
            font.pointSize: batteryFontPixelSize
            font.family: batteryFontFamily
            font.bold: true
            color: panelTextColor
        }
        
        Text {
            id: textChargeMode
            text: chargeMode
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            font.pointSize: batteryFontPixelSize
            font.family: batteryFontFamily
            color: panelTextColor
        }
        
        Item {
            id: filler
            Layout.fillHeight: true
        }
        
        Text {
            id: textTime1
            text: 'm' + timeSpent
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            font.pointSize: batteryFontPixelSize
            font.family: batteryFontFamily
            color: panelTextColor
        }
        
    }
}


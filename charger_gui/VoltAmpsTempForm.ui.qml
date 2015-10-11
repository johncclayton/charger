import QtQuick 2.4
import QtQuick.Layouts 1.1

Item {
    width: 400
    height: 30
    
    property double voltage: 24.3
    property double ch1amps: 3.2
    property double ch2amps: 0
    property double temp: 23
    property bool tempIsCentigrade: true
    
    property alias label: dclabel
    property alias layoutFields: layoutFields
    
    property int preferredHeight: 30
    
    RowLayout {
        id: layoutFields
        anchors.fill: parent
        spacing: 8
        
        Layout.preferredHeight: preferredHeight
        
        Text {
            id: dclabel
            text: 'DC' + voltage + ' V'
            horizontalAlignment: Text.AlignLeft            
            anchors.left: parent.left
            anchors.top: parent.top
            color: panelTextColor
        }
                
    }
}


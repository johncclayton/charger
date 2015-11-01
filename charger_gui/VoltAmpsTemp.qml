import QtQuick 2.4

VoltAmpsTempForm {
    FontMetrics {
        id: fontMetrics
        font.family: label.font.family
        font.pointSize: label.font.pointSize
    }
        
    property double voltage: 24.3
    property double ch1amps: 3.2
    property double ch2amps: 0
    property double temperature: 23
    property bool tempIsCentigrade: true
    property color textColor: "white"
    
    property int preferredHeight: fontMetrics.height + (2 * layoutFields.anchors.margins) 
}


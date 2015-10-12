import QtQuick 2.4

VoltAmpsTempForm {
    FontMetrics {
        id: fontMetrics
        font.family: label.font.family
        font.pointSize: label.font.pointSize
    }
        
    preferredHeight: fontMetrics.height + (2 * layoutFields.anchors.margins) 
}


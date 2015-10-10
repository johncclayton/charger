import QtQuick 2.4

OneCellForm {
    FontMetrics {
        id: cellFontMetrics
        font.family: label.font.family
        font.pointSize: label.font.pointSize
    }
    
    visible: cellNumber !== 0
    
    preferredWidth:  cellFontMetrics.boundingRect(cellNumber).width + 
                     cellFontMetrics.boundingRect(cellUnits).width +            
                     Math.max(value.width, label.width) + 
                     (2 * layoutFields.anchors.margins)
    preferredHeight: cellFontMetrics.height + (2 * layoutFields.anchors.margins)    
}


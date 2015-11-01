import QtQuick 2.4

OneCellForm {
    FontMetrics {
        id: cellFontMetrics
        font.family: label.font.family
        font.pointSize: label.font.pointSize
    }
    
    property string cellNumber: ""
    property string cellValue: "3.75"
    property string cellUnits: 'v'
        
    property int preferredWidth:  cellFontMetrics.boundingRect(cellNumber).width + 
                     cellFontMetrics.boundingRect(cellUnits).width +            
                     value.width + label.width + 
                     (2 * layoutFields.anchors.margins)
    
    property int preferredHeight: cellFontMetrics.height + (2 * layoutFields.anchors.margins) 
}


import QtQuick 2.4
import QtQuick.Layouts 1.1

BattModeTimeForm {
    FontMetrics {
        id: bmf
        font.family: textCharge.font.family
        font.pointSize: textCharge.font.pointSize
    }
    
    preferredLayoutWidth: Math.max(bmf.boundingRect(textBattery.text).width, 
                                   bmf.boundingRect(textCharge.text).width, 
                                   bmf.boundingRect("DISCHARGE").width, 
                                   bmf.boundingRect("BALANCE").width, 
                                   bmf.boundingRect("CYCLE").width, 
                                   bmf.boundingRect("STORAGE").width, 
                                   bmf.boundingRect(textCharge.text).width, 
                                   bmf.boundingRect(textTime.text).width) + layoutFields.anchors.margins
    
    preferredLayoutHeight: bmf.boundingRect(textBattery.text).height * 4
}


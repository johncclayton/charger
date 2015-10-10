import QtQuick 2.4
import QtQuick.Layouts 1.1

VoltAmpsCapacityForm {
    minimumLayoutWidth: Math.max(textVolts.width, 
                                 textAmps.width, 
                                 textCapacity.width) + 2 * columnLayout.anchors.margins
    
    preferredLayoutHeight: textVolts.height * 3.5
}


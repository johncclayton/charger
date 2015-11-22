import QtQuick 2.4
import QtQuick.Layouts 1.1

VoltAmpsCapacityForm {
    property double voltage: 23.010
    property double amps: 26.84
    property double capacity: 0
        
    property int minimumLayoutWidth: Math.max(120, 
                                 textVolts.width, 
                                 textAmps.width, 
                                 textCapacity.width) + 2 * columnLayout.anchors.margins
    
    property int preferredLayoutHeight: textVolts.height * 3.5
}


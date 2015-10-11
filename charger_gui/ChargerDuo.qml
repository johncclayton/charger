import QtQuick 2.5
import com.coderage.messaging 1.0 

ChargerDuoForm {
    id: thing
    
    iCharger_Channel1Background: Qt.darker(iCharger_Channel1PanelColor, 8)
    iCharger_Channel2Background: Qt.darker(iCharger_Channel2PanelColor, 8)
    
    property string modelKey: ""
    property DeviceInfo info: devicesModel.getDeviceInfo(modelKey)

    onInfoChanged: {
        console.log("info is now:" + info.ch1.inputVoltage)
    }

    Component.onCompleted: {
        console.log("getting device info for model key:" + thing.objectName)
        modelKey = thing.objectName
    }

    Component.onDestruction: {
        console.log("iChargerDUO UI being destroyed");
    }
}


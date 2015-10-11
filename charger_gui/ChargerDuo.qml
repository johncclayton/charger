import QtQuick 2.5

ChargerDuoForm {
    id: thing
    
    iCharger_Channel1Background: Qt.darker(iCharger_Channel1PanelColor, 8)
    iCharger_Channel2Background: Qt.darker(iCharger_Channel2PanelColor, 8)
    
    Component.onCompleted: {
        console.log("woot - I was created:" + thing.objectName)
    }

    Component.onDestruction: {
        console.log("iChargerDUO UI being destroyed");
    }
    
       
}


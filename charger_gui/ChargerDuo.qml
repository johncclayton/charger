import QtQuick 2.5

ChargerDuoForm {
    iCharger_Channel1Background: Qt.darker(iCharger_Channel1PanelColor, 8)
    iCharger_Channel2Background: Qt.darker(iCharger_Channel2PanelColor, 8)
    
    Component.onDestruction: {
        console.log("iChargerDUO UI being destroyed");
    }
}


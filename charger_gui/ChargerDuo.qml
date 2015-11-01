import QtQuick 2.5
import com.coderage.messaging 1.0 

ChargerDuoForm {   
    property string modelKey: ""

    property color iCharger_Channel1PanelColor: "#0F77F7"
    property color iCharger_Channel1Background: Qt.darker(iCharger_Channel1PanelColor, 8)
    property color iCharger_Channel2PanelColor: "#009900"
    property color iCharger_Channel2Background: Qt.darker(iCharger_Channel2PanelColor, 8)
    
    property string voltageStr: Format.valueStr(info.ch1.inputVoltage / 1000.0)
    property string ch1ampsStr: Format.valueStr(info_ch1.outputCurrent)
    property string ch2ampsStr: Format.valueStr(info_ch2.outputCurrent)
    property string tempInternalStr: Format.valueStr(info_ch1.tempInternal  / 10.0)

    property DeviceInfo info: DeviceInfo {}
    property ChannelStatus info_ch1: ChannelStatus {}
    property ChannelStatus info_ch2: ChannelStatus {}
    
    Connections {
        target: devicesModel
        onDeviceInfoUpdated: {
            info = devicesModel.getDeviceInfo(modelKey);
            info_ch1 = info.ch1;
            info_ch2 = info.ch2;
        }        
    }
        
    Component.onCompleted: {
        console.log("assigned to show info for model key:" + modelKey)
    }

    Component.onDestruction: {
        console.log("iChargerDUO UI being destroyed");
    }
}


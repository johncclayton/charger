import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQml 2.2
import com.coderage.messaging 1.0

Rectangle {
    width: 400
    height: 400
    
    property string key: ""
    property color iCharger_Channel1PanelColor: "#0F77F7"
    property color iCharger_Channel1Background: "black"
    property color iCharger_Channel2PanelColor: "#009900"
    property color iCharger_Channel2Background: "black"

    property alias channel1: channel1
    property alias channel2: channel2
    property alias volt_amps_temp: volt_amps_temp
    
    property ChannelStatus info_ch1: ChannelStatus {}
    property ChannelStatus info_ch2: ChannelStatus {}
    
    color: "black"
    
    ColumnLayout {
        anchors.fill: parent
        
        RowLayout { 
            anchors.fill: parent
            spacing: 2
            
            Channel {
                id: channel1

                dataSource: info_ch1
                
                panelHeaderTitleLeft.text: "01-Cycle"
                panelBorderColor: iCharger_Channel1PanelColor
                panelBackgroundColor: iCharger_Channel1Background
                
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: volt_amps_temp.height
                
                Layout.preferredWidth: (parent.width / 2) - 1
            }
            
            Channel {
                id: channel2
                
                dataSource: info_ch2
                
                panelHeaderTitleLeft.text: "02-Balance"
                panelBorderColor: iCharger_Channel2PanelColor
                panelBackgroundColor: iCharger_Channel2Background
                
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: volt_amps_temp.height
                Layout.preferredWidth: (parent.width / 2) - 1
            }
        }
        
        VoltAmpsTemp {
            id: volt_amps_temp   
                        
            voltage: info_ch1.outputVoltage
            ch1amps: info_ch1.outputCurrent
            ch2amps: info_ch2.outputCurrent
            temperature: info_ch1.tempInternal
            
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            
            anchors.leftMargin: 2
            anchors.rightMargin: 2
        }
    }
}


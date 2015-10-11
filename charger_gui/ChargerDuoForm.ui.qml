import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQml 2.2

Item {
    width: 400
    height: 400

    property string key: ""
    property color iCharger_Channel1PanelColor: "lightblue"
    property color iCharger_Channel1Background: "black"
    property color iCharger_Channel2PanelColor: "#009900"
    property color iCharger_Channel2Background: "black"
    
    RowLayout { 
        id: myicharger
        
        anchors.fill: parent
        
        Channel {
            id: channel1
            panelHeaderTitleLeft.text: "01-Cycle"
            panelBorderColor: iCharger_Channel1PanelColor
            panelBackgroundColor: iCharger_Channel1Background
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: (parent.width/2) - 1
        }
        
        Channel {
            id: channel2
            panelHeaderTitleLeft.text: "02-Balance"
            panelBorderColor: iCharger_Channel2PanelColor
            panelBackgroundColor: iCharger_Channel2Background
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: (parent.width/2) - 1
        }
    }
}


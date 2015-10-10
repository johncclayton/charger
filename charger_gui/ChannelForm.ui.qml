import QtQuick 2.4
import QtQuick.Layouts 1.1

Item {
    id: content
    
    // bit of a trick: these are *required* everywhere inside PanelHeader component
    // but use of QML Component scope rules means I can define/declare them here and
    // make use of them deep inside the PanelHeader parts - which is cool because then
    // I don't need to redefine them 6 times in each subcomponent.
    
    property color panelTextColor: "white"
    property color panelHeaderTextColor: "black"
    property color panelBorderColor: "#9CDCFC"
    property color panelBackgroundColor: "#171B6C"
    property int panelBorderWidth: 2
    
    property string batteryFontFamily: "Courier"
    property int batteryFontPixelSize: 18
    property string voltsFontFamily: "Verdana"
    property int voltsFontPixelSize: 18
    property double panelBackgroundOpacity: 0.2
    property color panelCellNumberColor: "lightblue"
    
    property int panelRadius: 10
    property int panelSmallRadius: 5
    
    width: 300
    height: 220
    
    PanelHeader {
        id: panel
        
        color: panelBackgroundColor
        border.color: panelBorderColor
        
        anchors.fill: parent
        
        headerTitleLeft.text: qsTr("00-Charge")
        headerTitleRight.text: qsTr("70A")
        
        ColumnLayout {
            id: main_column
            
            spacing: 5
            anchors.fill: parent
            
            RowLayout {
                id: row1layout
                height: 92
                
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                
                spacing: 0
                Layout.fillHeight: true
                
                BattModeTime {
                    id: batterymode
                    anchors.left: parent.left
                    anchors.leftMargin: 3
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 3
                    anchors.top: parent.top
                    anchors.topMargin: 3
                    
                }
                
                VoltAmpsCapacity {
                    id: voltamps
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 3
                    anchors.top: parent.top
                    anchors.topMargin: 3
                    
                    anchors.left: batterymode.right
                    anchors.leftMargin: 3
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    
                }
            }
            
            
            ColumnLayout {
                id: lower_column
                anchors.bottomMargin: 3
                anchors.top: row1layout.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.topMargin: 3
                spacing: 8
                
                GridLayout {
                    id: allcells
                    
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: horizLine.top
                    anchors.bottomMargin: 3
                    
                    flow: GridLayout.TopToBottom    
                    
                    rows: 10
                    columnSpacing: 8
                    
                    columns: 1
                    
                    OneCell {
                        id: cell1
                        cellNumber: "1"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "2"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "3"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "4"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "5"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "6"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "7"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "8"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "9"
                        cellValue: "3.75"
                    }
                    
                    OneCell {
                        cellNumber: "10"
                        cellValue: "3.75"
                    }
                }
                
                Rectangle {
                    id: horizLine
                    height: 1
                    color: panelBorderColor
                    anchors.bottom: irlayout.top
                    anchors.bottomMargin: 4
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
                
                RowLayout {
                    id: irlayout
                    
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 3
                                        
                    OneCell {
                        id: resistance1
                        cellNumber: "Sr"
                        cellValue: "12.9"
                        cellUnits: "mO"
                    }
                    
                    OneCell {
                        id: resistance2
                        cellNumber: "Lr"
                        cellValue: "22.4"
                        cellUnits: "mO"
                    }                        
                }
            }
        }
    }
}


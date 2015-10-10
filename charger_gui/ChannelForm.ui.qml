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
    property color panelBorderColor: "#3399FF"
    property color panelBackgroundColor: panelBorderColor
    property alias panelHeaderTitleLeft: panel.headerTitleLeft
    property alias panelHeaderTitleRight: panel.headerTitleRight
    property int panelBorderWidth: 2
    
    property string batteryFontFamily: "Courier"
    property int batteryFontPixelSize: 18
    property string voltsFontFamily: "Verdana"
    property int voltsFontPixelSize: 18
    property color panelCellNumberColor: panelBorderColor
    
    property int panelRadius: 10
    property int panelSmallRadius: 5
    property int panelNumberOfRows: 10
    
    property alias panel: panel
    property alias horizline: horizLine
    property alias cells: allcells
    property alias cell1: cell1
    
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
                
                Layout.fillHeight: true
                spacing: 0
                
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

                anchors.top: row1layout.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                
                GridLayout {
                    id: allcells
                    
                    flow: GridLayout.TopToBottom    
                    rows: panelNumberOfRows
                                        
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: horizLine.top
                                        
                    Layout.preferredHeight: panelNumberOfRows * cell1.height
                    
                    // used to ensure the columns don't come too close / merge 
                    columnSpacing: 12
                    rowSpacing: 0
                    
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
                    
                    Item {
                        Layout.fillHeight: true
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
                        cellNumber: "Sʀ"
                        cellValue: "12.9"
                        cellUnits: "mΩ"
                    }
                    
                    OneCell {
                        id: resistance2
                        cellNumber: "Lʀ"
                        cellValue: "22.4"
                        cellUnits: "mΩ"
                    }                        
                }
            }
        }
    }
}


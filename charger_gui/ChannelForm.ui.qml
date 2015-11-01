import QtQuick 2.4
import QtQuick.Layouts 1.1
import com.coderage.messaging 1.0 

Item {
    id: content
    
    // bit of a trick: these are *required* everywhere inside PanelHeader component
    // but use of QML Component scope rules means I can define/declare them here and
    // make use of them deep inside the PanelHeader parts - which is cool because then
    // I don't need to redefine them 6 times in each subcomponent.
    
    property alias panelHeaderTitleLeft: panel.headerTitleLeft
    property alias panelHeaderTitleRight: panel.headerTitleRight
        
    property alias cell1: cell1
    property alias panel: panel
    property alias horizline: horizLine
    property alias irlayout: irlayout
    property alias cells: allcells
    property alias cells_column: cells_column
    
    property alias header_cells: header_cells
    property alias header_ir: header_ir
    property alias header_info: header_info
    property alias header_wrapper_ir_info: header_wrapper_ir_info
    
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
            
            spacing: 2
            anchors.fill: parent
            Layout.fillHeight: true
            
            /** battery info / time and the volts/amps used */
            RowLayout {
                id: row1layout
                
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                
                Layout.fillHeight: false
                Layout.preferredHeight: 92
                
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
                    
                    voltage: dataSource.outputPower
                    amps: dataSource.outputCurrent
                    capacity: dataSource.outputCapacity
                    
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
            
            /** header panel for cells/IR/info selection */
            Rectangle {
                id: header
                
                anchors.margins: 3
                
                anchors.top: row1layout.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                
                Layout.preferredHeight: header_cells.preferredLayoutHeight
                
                color: "transparent"
                
                ColumnLayout {
                    anchors.fill: parent
                    
                    RowLayout {
                        id: header_layout
                        anchors.fill: parent
                        
                        SelectableTab {
                            id: header_cells
                            selected: viewModel.cellState == ChannelViewModel.CELLS
                            title: " Cells "
                        }

                        /** 
                            exists only as a container that makes it easier to switch off all the splitter elements         
                            and IR / info tabs while charging is NOT taking place 
                          */
                        Item {
                            id: header_wrapper_ir_info
                            
                            Rectangle { 
                                id: split1
                                width: 1
                                height: 10
                                color: "transparent"
                                border.width: 1
                                border.color: panelBorderColor
                            }                            
                            
                            SelectableTab {
                                id: header_ir
                                title: " IR "
                                selected: viewModel.cellState == ChannelViewModel.RESISTANCE
                            }
                            
                            Rectangle { 
                                id: split2
                                width: 1
                                height: 10
                                color: "transparent"
                                border.width: 1
                                border.color: panelBorderColor
                            }                            
                            
                            SelectableTab {
                                id: header_info
                                title: " Info "
                                selected: viewModel.cellState == ChannelViewModel.INFO
                            }
                            
                            Rectangle { 
                                id: split13
                                width: 1
                                height: 10
                                color: "transparent"
                                border.width: 1
                                border.color: panelBorderColor
                            }     
                        }
                        
                        Item { 
                            Layout.fillWidth: true
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        color: "transparent"
                        border.width: 1
                        border.color: panelBorderColor
                        height: 1
                    }
                }
            }
            
            /** actual cell area - shared with cells themselves and the summary of volts/resistance */            
            ColumnLayout {
                id: cells_column
                
                Layout.margins: 0  
                Layout.fillWidth: true
                
                anchors.top: header.bottom
                anchors.topMargin: 5
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                
                GridLayout {
                    id: allcells
                    
                    flow: GridLayout.TopToBottom    
                    rows: panelNumberOfRows
                    columnSpacing: 12
                    rowSpacing: 0
                    
                    Layout.preferredHeight: cellsPreferredHeight
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    
                    anchors.bottom: horizLine.top
                    anchors.top: header.bottom
                    anchors.left: cells_column.left
                    anchors.right: cells_column.right
                    
                    OneCell {
                        id: cell1
                        cellNumber: "1"
                        cellValue: cell1Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell2
                        cellNumber: "2"
                        cellValue: cell2Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell3
                        cellNumber: "3"
                        cellValue: cell3Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell4
                        cellNumber: "4"
                        cellValue: cell4Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell5
                        cellNumber: "5"
                        cellValue: cell5Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell6
                        cellNumber: "6"
                        cellValue: cell6Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell7
                        cellNumber: "7"
                        cellValue: cell7Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell8
                        cellNumber: "8"
                        cellValue: cell8Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell9
                        cellNumber: "9"
                        cellValue: cell9Value
                        cellUnits: myCellUnits
                    }
                    
                    OneCell {
                        id: cell10
                        cellNumber: "10"
                        cellValue: cell10Value
                        cellUnits: myCellUnits
                    }
                }
                
                Rectangle {
                    id: horizLine
                    
                    color: "transparent"
                    border.color: panelBorderColor
                    
                    anchors.bottom: irlayout.top
                    anchors.bottomMargin: 4
                    
                    Layout.fillWidth: true                    
                    Layout.preferredHeight: 1
                }
                
                RowLayout {
                    id: irlayout
                    
                    anchors.left: cells_column.left
                    anchors.leftMargin: 5
                    
                    anchors.right: cells_column.right
                    anchors.rightMargin: 5
                    
                    anchors.bottom: cells_column.bottom
                    anchors.bottomMargin: 3
                    
                    Layout.preferredHeight: summary1.preferredHeight
                    
                    OneCell {
                        id: summary1
                        cellNumber: summary1number
                        cellValue: summary1value
                        cellUnits: summary1units
                    }
                    
                    OneCell {
                        id: summary2
                        cellNumber: summary2number
                        cellValue: summary2value
                        cellUnits: summary2units
                    }                        
                }
                
            }                
            
        }
    }
    
}




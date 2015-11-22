import QtQuick 2.4
import com.coderage.messaging 1.0 

ChannelForm {
    property color panelTextColor: "white"
    property color panelHeaderTextColor: "black"
    property color panelBorderColor: "#3399FF"
    property color panelBackgroundColor: panelBorderColor
    property int panelBorderWidth: 2
    
    property color selectableTabBackgroundNotSelectedColor: "transparent"
    property color selectableTabBackgroundSelectedColor: panelBorderColor
    
    property color selectableTabNotSelectedTextColor: panelBorderColor
    property color selectableTabSelectedTextColor: panelTextColor
    
    property string batteryFontFamily: "Courier"
    property int batteryFontPixelSize: 18
    property string voltsFontFamily: "Verdana"
    property int voltsFontPixelSize: 18
    property color panelCellNumberColor: panelBorderColor
    
    property int panelRadius: 10
    property int panelSmallRadius: 5
    property int panelNumberOfRows: 10
    
    property ChannelStatus dataSource: ChannelStatus {}
    property ChannelViewModel viewModel: ChannelViewModel {}
    
    property string myCellUnits: viewModel.cellState == ChannelViewModel.CELLS ? 'v' : 'r'
    property string cell1Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell1.voltage : dataSource.cell1.resistance
    property string cell2Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell2.voltage : dataSource.cell2.resistance
    property string cell3Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell3.voltage : dataSource.cell3.resistance
    property string cell4Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell4.voltage : dataSource.cell4.resistance
    property string cell5Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell5.voltage : dataSource.cell5.resistance
    property string cell6Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell6.voltage : dataSource.cell6.resistance
    property string cell7Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell7.voltage : dataSource.cell7.resistance
    property string cell8Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell8.voltage : dataSource.cell8.resistance
    property string cell9Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell9.voltage : dataSource.cell9.resistance
    property string cell10Value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.cell10.voltage : dataSource.cell10.resistance
    
    property string summary1number: viewModel.cellState == ChannelViewModel.CELLS ? "Sv" : "Sʀ"
    property string summary1value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.totalVoltsAllCells : dataSource.totalResistance
    property string summary1units: viewModel.cellState == ChannelViewModel.CELLS ? "mV" : "mΩ"
    
    property string summary2number: viewModel.cellState == ChannelViewModel.CELLS ? "ΔV" : "Lʀ"
    property string summary2value: viewModel.cellState == ChannelViewModel.CELLS ? dataSource.totalVoltsDeltaAllCells : dataSource.lineInternalResistance
    property string summary2units: viewModel.cellState == ChannelViewModel.CELLS ? "mV" : "mΩ"

    // doing the number of rows like this (higher level javascript func) 
    // stops the infinite recursion that happens when this code is attached
    // directly to the height property of the allcells item.  
    panel.onHeightChanged: {
        panelNumberOfRows = Math.floor((horizline.y - cells.y - 8 /* margins */) / cell1.height);
    }  

    property int cellsPreferredHeight: cells_column.height - (horizline.height + irlayout.height + (2 * cells.parent.anchors.margins));
    
    header_wrapper_ir_info.visible: false
    
    Connections {
        target: header_ir.mouseArea
        onClicked: {
            viewModel.cellState = ChannelViewModel.RESISTANCE
        }
    }
    
    Connections { 
        target: header_cells.mouseArea
        onClicked: {
            viewModel.cellState = ChannelViewModel.CELLS
        }
    }

    Connections { 
        target: header_info.mouseArea
        onClicked: {
            viewModel.cellState = ChannelViewModel.INFO
        }
    }
}


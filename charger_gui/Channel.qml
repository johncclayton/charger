import QtQuick 2.4
import com.coderage.messaging 1.0 

ChannelForm {
    // doing the number of rows like this (higher level javascript func) 
    // stops the infinite recursion that happens when this code is attached
    // directly to the height property of the allcells item.  
    panel.onHeightChanged: {
        panelNumberOfRows = Math.floor((horizline.y - cells.y) / cell1.height)
    }  
    
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


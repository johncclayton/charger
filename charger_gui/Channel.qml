import QtQuick 2.4

ChannelForm {
    // doing the number of rows like this (higher level javascript func) 
    // stops the infinite recursion that happens when this code is attached
    // directly to the height property of the allcells item.  
    panel.onHeightChanged: {
        panelNumberOfRows = Math.floor((horizline.y - cells.y) / cell1.height)
    }  
}


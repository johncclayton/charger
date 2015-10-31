import QtQuick 2.4
import QtQuick.Layouts 1.2

Item {
    width: minimumLayoutWidth
    height: preferredLayoutHeight
    
    property int preferredLayoutHeight: 0
    property int minimumLayoutWidth: 0
    property bool selected: false
    
    property alias text: text
    property alias title: text.text
    property alias columnLayout: layout
    property alias mouseArea: mouse
    
    Rectangle {
        anchors.fill: parent 
        
        color: selected ? selectableTabBackgroundSelectedColor : selectableTabBackgroundNotSelectedColor
        
        ColumnLayout {
            id: layout
            
            spacing: 2
            
            Layout.minimumWidth: minimumLayoutWidth
            
            Text { 
                id: text
                
                text: "Cells"
                color: selected ? selectableTabSelectedTextColor : selectableTabNotSelectedTextColor
                
                anchors.fill: parent
            }
        }
        
        MouseArea { 
            id: mouse
            anchors.fill: parent
        }
    }
    
    
}


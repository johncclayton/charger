import QtQuick 2.4

SelectableTabForm {
    property bool selected: false
    
    property int minimumLayoutWidth: text.width + (columnLayout.spacing * 2)
    property int preferredLayoutHeight: text.height
}


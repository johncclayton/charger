import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Item {
    id: content
    
    width: 800
    height: 400
    
    property int textFieldWidth: 50
    property alias tabView: tabView
    
    ColumnLayout {
        id: columnlayout
        spacing: 8
        
        anchors.fill: parent
        anchors.margins: 12
        
        GroupBox {
            id: chargeModeGroupBox
            
            title: "Charge Mode"
            
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            
            ExclusiveGroup { 
                id: chargeType
            }
            
            GridLayout {
                flow: GridLayout.LeftToRight
                
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 8
                
                Item {
                    Layout.fillWidth: true
                }
                
                RadioButton {
                    id: rbCharge
                    text: qsTr("Charge")
                    exclusiveGroup: chargeType
                }
                
                RadioButton {
                    id: rbFastCharge
                    text: qsTr("Fast Charge")
                    exclusiveGroup: chargeType
                }
                
                RadioButton {
                    id: rbDischarge
                    text: qsTr("Discharge")
                    exclusiveGroup: chargeType
                }
                
                RadioButton {
                    id: rbCycle
                    text: qsTr("Cycle")
                    exclusiveGroup: chargeType
                }
                
                RadioButton {
                    id: rbBalance
                    text: qsTr("Balance")
                    exclusiveGroup: chargeType
                }
                
                Item {
                    Layout.fillWidth: true
                }
            }
        }
        
        TabView {
            id: tabView 
            
            anchors.top: chargeModeGroupBox.bottom
            
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: toggle.top
            anchors.bottomMargin: 12
                        
            Tab {
                id: tabWizard
                title: "Wizard"
                
                anchors.margins: 12
                
                GridLayout { 
                    id: wizardColumnLayout
                    
                    columns: 2
                    columnSpacing: 8
                    
                    Label {
                        text: "How many cells do each of the batteries have:"
                        Layout.fillWidth: true
                    }
                    
                    SpinBox { 
                        value: numberOfCells
                        minimumValue: 1
                        maximumValue: 10
                        Layout.preferredWidth: textFieldWidth
                    }
                    
                    Label {
                        text: "Whats the maximum C rating you wish to charge with:"
                        Layout.fillWidth: true
                    }
                    
                    SpinBox { 
                        value: cRating
                        minimumValue: 1
                        maximumValue: 5
                        Layout.preferredWidth: textFieldWidth
                    }
                    
                    Label {
                        text: "How many batteries have you got plugged in to the balance board:"
                        Layout.fillWidth: true
                    }
                    
                    SpinBox {
                        value: numberOfBatteries
                        minimumValue: 1
                        maximumValue: 6
                        Layout.preferredWidth: textFieldWidth
                    }
                    
                    Item { 
                        Layout.fillHeight: true
                    }
                }
            }
            
            Tab { 
                title: "Custom"
                
                anchors.margins: 12
                
                RowLayout {
                    Item { 
                        Layout.fillWidth: true
                    }
                    
                    Tumbler {
                        anchors.fill: parent
                        TumblerColumn {
                            model: 71
                        }
                    }
                    
                    Item { 
                        Layout.fillWidth: true
                    }
                }
            }
        }
        
        ToggleButton {
            id: toggle
            width: 90
            height: 90
            text: checked ? "Stop" : "Start"
            
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            
            Layout.alignment: Qt.AlignHCenter
        }
    }
}




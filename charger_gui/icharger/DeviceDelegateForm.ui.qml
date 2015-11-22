import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Item {
    id: content
    
    width: 400
    height: 151
    
    property alias image: deviceImage
    property alias product: labelProduct.text
    property alias manufacturer: txtManufacturer.text
    property alias serialNumber: txtSerialNumber.text
    
    GridLayout {
        id: grid1
        anchors.bottomMargin: 12
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        anchors.topMargin: 12
        anchors.fill: parent
        
        rows: 1
        columns: 2
        columnSpacing: 15
        
        Image {
            id: deviceImage
            width: content.width / 3
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
//            horizontalAlignment: Image.AlignRight
            sourceSize.width: 95
            fillMode: Image.PreserveAspectFit
            source: "images/icharger_4010_duo.png"
        }
        
        RowLayout {
            Item {
                id: filler1
                Layout.fillWidth: true
            }
            
            ColumnLayout {
                id: detailsColumn
                
                spacing: 5
                
                Item {
                    id: filler2
                    Layout.fillHeight: true
                }
                
                Label {
                    id: labelProduct
                    text: qsTr("Product String")
                    font.pointSize: 17
                    font.bold: true
                }
                
                GridLayout {
                    columns: 2
                    rows: 1
                    
                    Label {
                        id: lblManufacturer
                        text: qsTr("Manufacturer:")
                    }
                    
                    Label {
                        id: txtManufacturer
                        text: qsTr("------------")
                    }
                    
                    Label {
                        id: lblSerial
                        text: qsTr("Serial #:")
                    }
                    
                    Label {
                        id: txtSerialNumber
                        text: qsTr("------------")
                    }
                }
                
                Item {
                    id: filler3
                    Layout.fillHeight: true
                }
            }
            
            Item {
                id: filler4
                Layout.fillWidth: true
            }
            
        }
    }
}

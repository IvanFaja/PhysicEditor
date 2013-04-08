import QtQuick 2.0
import GEdit 1.0
Rectangle {
    width: 400
    height: 400
    Column{
        y:0
        x:0
        width: 360
        height: 360
        Row{

            Rectangle{
                width: 200
                height: 30
                border.color: "black"
                TextInput{
                    anchors.fill: parent
                    id: path
                    autoScroll: true
                    selectionColor: "grey"
                    text: "source file"
                }
            }
        }
        Row{
            Rectangle{
                width: 150
                height: 30
                color: "green"
                border.color: "black"
                Text {
                    text: qsTr("load image")
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        image.source = path.text;
                        drawer.path = path.text;
                    }


                }
            }
        }
        Row{
            Rectangle{
                width: 100
                height: 30
                color: "green"
                border.color: "black"
                Text {
                    text: qsTr("Save")
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: drawer.save()
                }
            }
            Rectangle{
                width: 100
                height: 30
                color: "green"
                border.color: "black"
                Text {
                    text: qsTr("Erase")
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: drawer.clear()
                }
            }
        }
        Rectangle {
            width: 200
            height: 200
            color: "grey"
            Image {
                id: image
                FreeDrawer{
                    id: drawer
                    anchors.fill: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        drawer.addVertice(mouse.x,mouse.y)
                    }
                }
            }
        }
    }
}

import QtQuick 2.2

Rectangle {
    width: 200
    height: 700
    color: "#b1d2e4"

    ListView {
        id: listView1
        x: 8
        y: 8
        width: 184
        height: 684
        snapMode: ListView.NoSnap
        orientation: ListView.Vertical
        layoutDirection: Qt.LeftToRight
        clip: false
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                spacing: 10
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
    }
}

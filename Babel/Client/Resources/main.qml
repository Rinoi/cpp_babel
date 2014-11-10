import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow
{
    visible: true
    width: 600
    height: 700
    title: qsTr("babel-2017-mart_q")

Rectangle
{
    id: drawingZone
    color: "#2e9afe"
    objectName : "drawingZone"
    anchors.fill: parent

        Rectangle
        {
            id: backgroundInfo
            objectName : "backgroundInfo"
            width: 300
            height: 168
            color: "#ffffff"
            radius: 10
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Text
            {
                id: infoText
                height: 94
                objectName : "infoText"
                text: qsTr("connection au serveur en cours...")
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.left: parent.left
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12

                function onConnectionFailed() {
                    console.log("la connection au serveur a fail");
                    infoText.text = "la connection au serveur a fail";
                    rectangle3.visible = false;
                    rectangle1.visible = true;
                    rectangle2.visible = true;
                }


                function onConnectionSuccess() {
                    console.log("connection done !");
                    infoText.text = "Connection done !";
                    infoText.anchors.fill = infoText.parent;
                    rectangle3.visible = false;
                    animation.start();
                }

                ParallelAnimation {
                    id: animation
                    PropertyAnimation {target: backgroundInfo; easing.type: "OutCubic" ; property : "width"; to:500; duration:500}
                    PropertyAnimation {target: backgroundInfo; easing.type: "OutCubic" ; property : "height"; to:600; duration: 500}
                    onRunningChanged: {
                        if (animation.running == false){
                            applicationAnchor.loadConnectionPlugin();
                        }
                    }
                }
            }

            Rectangle {
                id: rectangle1
                visible: false

                y: 100

                width: 100
                height: 50

                color: "#b1d9fb"
                radius: 10
                anchors.horizontalCenterOffset: -66
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    id: text1
                    text: qsTr("Exit")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    font.pixelSize: 12
                }

                MouseArea {
                    id: mouseArea1
                    hoverEnabled : true

                    onExited:{rectangle1.color = "#b1d9fb";}

                    onEntered:{rectangle1.color = "#cbe5fd";}
                    anchors.fill: parent
                    onClicked: {
                        Qt.quit();
                    }
                }
            }

            Rectangle {
                id: rectangle2
                visible: false

                x: 4
                y: 100

                width: 100
                height: 50
                color: "#b1d9fb"
                radius: 10
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text2
                    text: qsTr("Reconnection")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea
                {
                    id: mouseArea2
                    hoverEnabled : true

                    anchors.fill: parent

                    onExited:{rectangle2.color = "#b1d9fb";}

                    onEntered:{rectangle2.color = "#cbe5fd";}

                    onClicked: {
                        infoText.text = "connection au serveur en cours...";
                        rectangle1.visible = false;
                        rectangle2.visible = false;
                        rectangle3.visible = true;
                        applicationAnchor.reconnectToServer();
                    }
                }
                anchors.horizontalCenterOffset: 73
            }

            Rectangle
            {
                id: rectangle3

                y: 100
                width: 100
                height: 50
                color: "#b1d9fb"
                radius: 10
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text3
                    text: qsTr("Exit")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea3
                    anchors.fill: parent

                    hoverEnabled : true

                    onExited:{rectangle3.color = "#b1d9fb";}

                    onEntered:{rectangle3.color = "#cbe5fd";}


                    onClicked: {
                        Qt.quit();
                    }
                }
                visible: true
            }
        }
    }
}

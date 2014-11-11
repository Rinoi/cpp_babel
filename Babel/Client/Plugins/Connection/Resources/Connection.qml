import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle
{
    id: connectionPlugin
    objectName : "connectionPlugin"

    width: 600
    height: 700

    anchors.fill: parent

    color: "#2e9afe"

    Rectangle
    {
	id: background

	width: parent.width - 100
	height: parent.height - 100

	radius: 10
	color: "#ffffff"

	anchors.horizontalCenter: parent.horizontalCenter
	anchors.verticalCenter: parent.verticalCenter

	Rectangle
	{
	    id : contentItem
	    objectName : "contentItem"

	    width : parent.width - 100
	    height : parent.height - 100
	    
	    anchors.horizontalCenter: parent.horizontalCenter
	    anchors.verticalCenter: parent.verticalCenter

	    Rectangle
	    {
		id : subscribeItems
		
		opacity : 1.0
		anchors.fill: parent
		
		Rectangle
		{
		    id: subscribeMenu

		    
            y: parent.height * 0.20
		    
		    width: parent.width
		    height: parent.height * 0.10
		    
		    color: "#ffffff"

		    anchors.horizontalCenter: parent.horizontalCenter
		    
		    Rectangle
		    {
			id: backToConnection
			width: parent.width
			height: parent.height
			color: "#ffffff"
			
			Text
			{
			    id: backToConnectionText
			    text: qsTr("retour a l'écran de login")
			    anchors.fill: parent
			    font.underline: true
			    verticalAlignment: Text.AlignVCenter
			    horizontalAlignment: Text.AlignHCenter
			    font.pixelSize: 12
			}
			
			MouseArea {
			    id: backToConnectionMouseArea
			    anchors.fill: parent
			    onClicked : {
				subscribeItems.visible = false;
				connectionItems.visible = true;
			    }
			}
		    }
		}
		
        Rectangle
        {
            id: firstName


            y : parent.height * 0.30

            width: parent.width;height: parent.height * 0.10

            radius: 10
            color: "#ffffff";border.color: "#b1d9fb"
            anchors.horizontalCenter: parent.horizontalCenter

            Image
            {
            id: firstNameImage

            width: 40;height: 40
            anchors.left: parent.left;anchors.leftMargin: 10;anchors.verticalCenter: parent.verticalCenter
            sourceSize.height: 40;sourceSize.width: 40
            source: "firstname.svg"
            }

            TextField
            {
            id: firstNameInput

            text: qsTr("Louis");inputMask: qsTr("");placeholderText: qsTr("LastName")
            anchors.rightMargin: 5;anchors.leftMargin: 55;anchors.bottomMargin: 5;anchors.topMargin: 5;anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;verticalAlignment: Text.AlignVCenter

            font.pixelSize: 13
            style : TextFieldStyle{background : Rectangle{border.width: 0}}
            }
        }

        Rectangle
        {
            id: lastName

            y : parent.height * 0.41

            width: parent.width;height: parent.height * 0.10

            radius: 10
            color: "#ffffff";border.color: "#b1d9fb"
            anchors.horizontalCenter: parent.horizontalCenter

            Image
            {
            id: lastNameImage

            width: 40;height: 40
            anchors.left: parent.left;anchors.leftMargin: 10;anchors.verticalCenter: parent.verticalCenter
            sourceSize.height: 40;sourceSize.width: 40
            source: "lastname.svg"
            }

            TextField
            {
            id: lastNameInput

            text: qsTr("Martin-Pierrat"); placeholderText: "LastName";inputMask: qsTr("");            anchors.rightMargin: 5;anchors.leftMargin: 55;anchors.bottomMargin: 5;anchors.topMargin: 5;anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;verticalAlignment: Text.AlignVCenter

            font.pixelSize: 13
            style : TextFieldStyle{background : Rectangle{border.width: 0}}
            }
        }


		Rectangle
		{
            id: subscribeEmailBackground
		    
            y : parent.height * 0.52
		    
            width: parent.width;height: parent.height * 0.10
		    
            radius: 10
            color: "#ffffff";border.color: "#b1d9fb"
		    anchors.horizontalCenter: parent.horizontalCenter
		    
		    Image
		    {
            id: subscribeEmailImage
			
            width: 40;height: 40
            anchors.left: parent.left;anchors.leftMargin: 10;anchors.verticalCenter: parent.verticalCenter
            sourceSize.height: 40;sourceSize.width: 40
			source: "email.svg"
		    }
		    
		    TextField
		    {
            id: subscribeEmailInput

            text: qsTr("louis.martin-pierrat@epitech.eu"); placeholderText: "Email"; inputMask: qsTr("");            anchors.rightMargin: 5;anchors.leftMargin: 55;anchors.bottomMargin: 5;anchors.topMargin: 5;anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;verticalAlignment: Text.AlignVCenter
			
			font.pixelSize: 13
            style : TextFieldStyle{background : Rectangle{border.width: 0}}
            }
		}
		

        Rectangle
        {
            id: passwordBack

            y : parent.height * 0.63

            width: parent.width;height: parent.height * 0.10

            radius: 10
            color: "#ffffff";border.color: "#b1d9fb"
            anchors.horizontalCenter: parent.horizontalCenter

            Image
            {
            id: passImage

            width: 40;height: 40
            anchors.left: parent.left;anchors.leftMargin: 10;anchors.verticalCenter: parent.verticalCenter
            sourceSize.height: 40;sourceSize.width: 40
            source: "lock.svg"
            }

            TextField
            {
            id: passInput

            text: qsTr("p_password"); echoMode: 2;inputMask: qsTr("");placeholderText: qsTr("password")
            anchors.rightMargin: 5;anchors.leftMargin: 55;anchors.bottomMargin: 5;anchors.topMargin: 5;anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;verticalAlignment: Text.AlignVCenter

            font.pixelSize: 13
            style : TextFieldStyle{background : Rectangle{border.width: 0}}
            }
        }


        Rectangle
        {
            id: verifPassBack

            y : parent.height * 0.74

            width: parent.width;height: parent.height * 0.10

            radius: 10
            color: "#ffffff";border.color: "#b1d9fb"
            anchors.horizontalCenter: parent.horizontalCenter

            Image
            {
            id: verifPassImage

            width: 40;height: 40
            anchors.left: parent.left;anchors.leftMargin: 10;anchors.verticalCenter: parent.verticalCenter
            sourceSize.height: 40;sourceSize.width: 40
            source: "lock.svg"
            }

            TextField
            {
            id: verifPassInput

            text: qsTr("p_password"); echoMode: 2;inputMask: qsTr("");placeholderText: qsTr("verification Password")
            anchors.rightMargin: 5;anchors.leftMargin: 55;anchors.bottomMargin: 5;anchors.topMargin: 5;anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter;verticalAlignment: Text.AlignVCenter

            font.pixelSize: 13
            style : TextFieldStyle{background : Rectangle{border.width: 0}}
            }
        }


        Rectangle
        {
            id: subscribeButton

            y: parent.height * 0.87

            width: parent.width;height: 50
            color: "#b1d9fb"
            radius: 10

            anchors.horizontalCenter: parent.horizontalCenter

            MouseArea
            {
            id: subscribeButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onExited:{subscribeButton.color = "#b1d9fb";}

            onEntered:{subscribeButton.color = "#cbe5fd";}

            onClicked:{
                if (firstNameInput.text == ""
                    || lastNameInput.text == ""
                    || subscribeEmailInput.text == ""
                    || passInput.text == ""
                    || verifPassInput.text == ""
                    || passInput.text != verifPassInput.text)
                {

                if (firstNameInput.text == "")
                    firstName.border.color = "#ed0415";
                else
                    firstName.border.color = "#b1d9fb";
                if (lastNameInput.text == "")
                    lastName.border.color = "#ed0415";
                else
                    lastName.border.color = "#b1d9fb";
                if (subscribeEmailInput.text == "")
                    subscribeEmailBackground.border.color = "#ed0415";
                else
                    subscribeEmailBackground.border.color = "#b1d9fb";
                if (passInput.text == "" || passInput.text != verifPassInput.text)
                    passwordBack.border.color = "#ed0415";
                else {
                    passwordBack.border.color = "#b1d9fb";
                }
                if (verifPassInput.text == "" || passInput.text != verifPassInput.text)
                    verifPassBack.border.color = "#ed0415";
                else {
                    verifPassBack.border.color = "#b1d9fb";
                }
                if (verifPassInput.text != passInput.text)
                    errorReport1.text = "password don't match with verification password."
                else
                    errorReport1.text = "Obligatory field missing.";
                console.log("subscribe fail !");
                } else {
                    console.log("subscribe ok !");
                    firstName.border.color = "#b1d9fb";
                    lastName.border.color = "#b1d9fb";
                    subscribeEmailBackground.border.color = "#b1d9fb";
                    passwordBack.border.color = "#b1d9fb";
                    verifPassBack.border.color = "#b1d9fb";
                errorReport1.text = ""; connectionAnchor.onSubscribeClicked(firstNameInput.text, lastNameInput.text, subscribeEmailInput.text, passInput.text);
                }
            }
            }

            Text
            {
            id: subscribeButtonText

            text: qsTr("S'inscrire")

            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
            }
        }



        Text
		{
		    id: errorReport1
		    
            y: parent.height * 0.20 - height
		    
		    width: parent.width
		    height: 25
		    color: "#ed0000"
		    text: qsTr("")
		    anchors.horizontalCenter: parent.horizontalCenter
		    horizontalAlignment: Text.AlignHCenter
		    font.pixelSize: 12
		    anchors.horizontalCenterOffset: 0
		    verticalAlignment: Text.AlignVCenter
		}	
	    }

	    Rectangle
	    {
		id: connectionItems
		anchors.fill:  parent
		
		visible: true
		Text
		{
		    id: errorReport
		    y: parent.height * 0.25 - height
		    
		    width: parent.width
		    height: 25
		    
		    text: qsTr("")
		    
		    color: "#ed0000"
		    anchors.horizontalCenterOffset: 0
		    anchors.horizontalCenter: parent.horizontalCenter
		    verticalAlignment: Text.AlignVCenter
		    horizontalAlignment: Text.AlignHCenter
		    font.pixelSize: 12
		}
		
		Rectangle
		{
		    id: connectionMenu
		    
		    y: parent.height * 0.30
		    
		    width: parent.width
		    height: parent.height * 0.10
		    
		    color: "#ffffff"
		    
		    anchors.horizontalCenter: parent.horizontalCenter
		    
		    Rectangle
		    {
			id: subscribeBackground
			width: parent.width / 2
			height: parent.height
			color: "#ffffff"
			
			Text
			{
			    id: subscribeText
			    text: qsTr("s'enregistrer")
			    anchors.fill: parent
			    font.underline: true
			    verticalAlignment: Text.AlignVCenter
			    horizontalAlignment: Text.AlignHCenter
			    font.pixelSize: 12
			}
			
			MouseArea {
                id: subscribeMouseArea
                anchors.fill: parent
                onClicked : {
                    subscribeItems.visible = true;
                    connectionItems.visible = false
                }
			}
		    }
		    
		    Rectangle
		    {
			id: forgetPasswordBackground
			x : parent.width / 2
			width: parent.width / 2
			height: parent.height
			color: "#ffffff"
			
			Text
			{
			    id: forgetPasswordText
			    text: qsTr("mot de passe oublié")
			    anchors.fill: parent
			    verticalAlignment: Text.AlignVCenter
			    horizontalAlignment: Text.AlignHCenter
			    font.underline: true
			    font.pixelSize: 12
			}
			
			MouseArea
			{
			    id: forgetPasswordMouseArea
			    anchors.fill: parent
			}
		    }

		}
		
		Rectangle
		{
            id: emailBackground
		    
		    y : parent.height * 0.45
		    
		    width: parent.width
		    height: parent.height * 0.10
		    
		    color: "#ffffff"
		    radius: 10
		    border.color: "#b1d9fb"
		    anchors.horizontalCenter: parent.horizontalCenter
		    
		    Image
		    {
            id: emailImage
			
			width: 40
			height: 40
			
			anchors.left: parent.left
			anchors.leftMargin: 10
			anchors.verticalCenter: parent.verticalCenter
			sourceSize.height: 40
			sourceSize.width: 40
			
			source: "email.svg"
		    }
		    
		    TextField
            {
                id: emailInput
                text: "louis.martin-pierrat@epitech.eu"

            inputMask: qsTr("")
			placeholderText: qsTr("Email")
			
			anchors.rightMargin: 5
			anchors.leftMargin: 55
			anchors.bottomMargin: 5
			anchors.topMargin: 5
			anchors.fill: parent
			
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			
			font.pixelSize: 13
			style : TextFieldStyle
			{
			    background : Rectangle
			    {
				border.width: 0
			    }
			    placeholderTextColor: "green"
			}
		    }
		}
		
		Rectangle
		{
		    id: passwordBackground
		    
		    y: parent.height * 0.60
		    
		    width: parent.width
		    height: parent.height * 0.10

		    color: "#ffffff"
		    radius: 10
		    
		    border.color: "#b1d9fb"
		    
		    anchors.horizontalCenter: parent.horizontalCenter
		    
		    Image
		    {
			id: passwordImage
			
			width: 40
			height: 40
			
			anchors.left: parent.left
			anchors.leftMargin: 10
			anchors.verticalCenter: parent.verticalCenter
			sourceSize.height: 40
			sourceSize.width: 40
			source: "lock.svg"
		    }
		    
		    TextField
		    {
			id: passwordInput

            text : "p_password"

			echoMode: 2
			placeholderText: qsTr("Password")
			
			anchors.rightMargin: 5
			anchors.leftMargin: 55
			anchors.bottomMargin: 5
			anchors.topMargin: 5
			anchors.fill: parent
			
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			
			font.pixelSize: 13
			style : TextFieldStyle {background : Rectangle {border.width: 0}}
		    }
		}

		Rectangle
		{
		    id: connectionButton
		    
		    y: parent.height * 0.85 - 25
		    
            width: parent.width;height: 50
		    color: "#b1d9fb"
		    radius: 10

		    anchors.horizontalCenter: parent.horizontalCenter

		    MouseArea
		    {
			id: connectionButtonMouseArea
			anchors.fill: parent
			hoverEnabled: true
            onExited:{connectionButton.color = "#b1d9fb";}
			
            onEntered:{connectionButton.color = "#cbe5fd";}

            onClicked:{
                if (emailInput.text == "" && passwordInput.text == ""){
				errorReport.text = "Email and Password must be filled.";
                } else if (emailInput.text == ""){
				errorReport.text = "email must be filled.";
                } else if (passwordInput.text == ""){
				errorReport.text = "password must be filled.";
                } else {
				errorReport.text = "";
                connectionAnchor.onConnectionClicked(emailInput.text, passwordInput.text);
                    onConnectionAnim.visible = true;
			    }
			}
		    }
		    
		    Text
		    {
			id: connectionButtonText
			
			text: qsTr("Connection")
			
			anchors.fill: parent
            verticalAlignment: Text.AlignVCenter;horizontalAlignment: Text.AlignHCenter
			font.pixelSize: 12
		    }
		}

        Rectangle {
            id: onConnectionAnim
            x: 110
            y: 150
            width: 200
            height: 100

            color: "#ffffff"

            radius: 10
            border.color: "#2e9afe"

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            visible : false

            onVisibleChanged: {
                if (visible == true){
                    animationWaitingConnection.start();
                } else {
                    animationWaitingConnection.stop();
                }
            }

            Rectangle {
                id: topRect
                x: 1
                y: 1

                radius : 10

                width: parent.width - 2
                height: parent.height / 2 - 2
                color: "#ffffff"

                Text {
                    id: text1
                    text: "Identification en cours..."
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    font.pixelSize: 12
                }
            }

            Rectangle
            {
                id: botRect
                x: 1
                y: parent.height / 2 + 1
                width: parent.width - 2
                height: parent.height / 2 - 2
                radius : 10
                color: "#ffffff"

                SequentialAnimation
                {
                    id : animationWaitingConnection
                    loops : Animation.Infinite

                    running : true

                    ParallelAnimation
                    {
                        ColorAnimation { target : circle5 ; property: "color"; from: "#000000"; to: "#999999"; duration: 100 }
                        ColorAnimation { target : circle4 ; property: "color"; from: "#999999"; to: "#b3b3b3"; duration: 100 }
                        ColorAnimation { target : circle3 ; property: "color"; from: "#b3b3b3"; to: "#cccccc"; duration: 100 }
                        ColorAnimation { target : circle2 ; property: "color"; from: "#cccccc"; to: "#e6e6e6"; duration: 100 }
                        ColorAnimation { target : circle1 ; property: "color"; from: "#e6e6e6"; to: "#000000"; duration: 100 }
                    }

                    ParallelAnimation
                    {
                        ColorAnimation { target : circle5 ; property: "color"; from: "#999999"; to: "#b3b3b3"; duration: 100 }
                        ColorAnimation { target : circle4 ; property: "color"; from: "#b3b3b3"; to: "#cccccc"; duration: 100 }
                        ColorAnimation { target : circle3 ; property: "color"; from: "#cccccc"; to: "#e6e6e6"; duration: 100 }
                        ColorAnimation { target : circle2 ; property: "color"; from: "#e6e6e6"; to: "#000000"; duration: 100 }
                        ColorAnimation { target : circle1 ; property: "color"; from: "#000000"; to: "#999999"; duration: 100 }
                    }

                    ParallelAnimation
                    {
                        ColorAnimation { target : circle5 ; property: "color"; from: "#b3b3b3"; to: "#cccccc"; duration: 100 }
                        ColorAnimation { target : circle4 ; property: "color"; from: "#cccccc"; to: "#e6e6e6"; duration: 100 }
                        ColorAnimation { target : circle3 ; property: "color"; from: "#e6e6e6"; to: "#000000"; duration: 100 }
                        ColorAnimation { target : circle2 ; property: "color"; from: "#000000"; to: "#999999"; duration: 100 }
                        ColorAnimation { target : circle1 ; property: "color"; from: "#999999"; to: "#b3b3b3"; duration: 100 }
                    }

                    ParallelAnimation
                    {
                        ColorAnimation { target : circle5 ; property: "color"; from: "#cccccc"; to: "#e6e6e6"; duration: 100 }
                        ColorAnimation { target : circle4 ; property: "color"; from: "#e6e6e6"; to: "#000000"; duration: 100 }
                        ColorAnimation { target : circle3 ; property: "color"; from: "#000000"; to: "#999999"; duration: 100 }
                        ColorAnimation { target : circle2 ; property: "color"; from: "#999999"; to: "#b3b3b3"; duration: 100 }
                        ColorAnimation { target : circle1 ; property: "color"; from: "#b3b3b3"; to: "#cccccc"; duration: 100 }
                    }

                    ParallelAnimation
                    {
                        ColorAnimation { target : circle5 ; property: "color"; from: "#e6e6e6"; to: "#000000"; duration: 100 }
                        ColorAnimation { target : circle4 ; property: "color"; from: "#000000"; to: "#999999"; duration: 100 }
                        ColorAnimation { target : circle3 ; property: "color"; from: "#999999"; to: "#b3b3b3"; duration: 100 }
                        ColorAnimation { target : circle2 ; property: "color"; from: "#b3b3b3"; to: "#cccccc"; duration: 100 }
                        ColorAnimation { target : circle1 ; property: "color"; from: "#cccccc"; to: "#e6e6e6"; duration: 100 }
                    }
                }

Rectangle {
    id: circle5
    x: 142
    y: -1
    width: 20
    height: 20
    color: "#000000"
    radius: width * 0.5
    anchors.horizontalCenterOffset: 50
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
}

Rectangle {
    id: circle4
    x: 116
    y: -1
    width: 20
    height: 20
    color: "#999999"
    radius: width * 0.5
    anchors.horizontalCenterOffset: 25
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
}

Rectangle {
    id: circle3
    x: 90
    y: -1
    width: 20
    height: 20
    color: "#b3b3b3"
    radius: width * 0.5
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
}

Rectangle {
    id: circle2
    x: 64
    y: -1
    width: 20
    height: 20
    color: "#cccccc"
    radius: width * 0.5
    anchors.horizontalCenterOffset: -25
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter

}

Rectangle {
    id: circle1
    x: 38
    y: -1
    width: 20
    height: 20
    radius : width * 0.5
    anchors.horizontalCenterOffset: -50
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    color: "#e6e6e6"
}




            }

        }
    }
	}
	
	Text
	{
	    id: title
	    x: 50
	    y: 50
	    
	    width : parent.width
	    height: errorReport.y

        text: "Babel Connection Plugin"
	    opacity: 1
	    clip: true
	    
	    font.underline: true
	    font.bold: true
	    font.pointSize: 9
	    
	    anchors.horizontalCenter: parent.horizontalCenter
	    
	    verticalAlignment: Text.AlignVCenter
	    horizontalAlignment: Text.AlignHCenter
	}
    }
}

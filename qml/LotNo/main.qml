import QtQuick 1.1
import "func.js" as Func

Rectangle {
    id: form
    width: WIDTH; height: HEIGHT
    border.width: 3;
    border.color:"#cacaca";
    radius: 4

    Image {
        id:title
        z: 1
        height:50
        anchors.top: form.top
        anchors.left: form.left
        anchors.right: form.right
        source:Func.get_image_path("index_top.png")

        Text {
            anchors.left:title.left
            anchors.leftMargin: 20
            anchors.verticalCenter: title.verticalCenter
            text: windowTitle
            color:"#ffffff"
            font.pixelSize:14
            font.bold: true
        }
        MouseArea {
            anchors.fill:parent;
            property variant clickPos: "0, 0"
            onPressed:{
                clickPos = Qt.point(mouse.x, mouse.y);
            }
            onReleased: {
                var dx = mouse.x-clickPos.x
                var dy = mouse.y-clickPos.y;
                main_window.pos = Qt.point(main_window.pos.x + dx, main_window.pos.y + dy);
            }
        }

        WindowButton{
            id : win_btn
            anchors.top:parent.top;
            anchors.topMargin: 1
            anchors.right : parent.right
            model_data: ["minimum", "close"]
        }
    }

    LeftMenu {
        id:leftMenu
        width:160
        anchors.leftMargin:1;
        anchors.left:form.left
        anchors.top:title.bottom
        anchors.bottom:form.bottom;
        anchors.bottomMargin:1;
        model: Func.getMenuModel(SMF_Product);
        onSelected:{
            if(value == "about"){
                dataFilter.OnAbout();
            }else if(value == "quit"){
                dataFilter.quit();
            }else{
                dataFilter.clearData();
                pageLoader.source = Func.getPage(SMF_Product, value);
            }
        }
    }

    Loader {
        id: pageLoader
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.left: leftMenu.right
        anchors.right: parent.right
        anchors.rightMargin: 5
        focus: true
        source: Func.getDefaultPage(SMF_Product);
    }

    Connections{
        target: dataFilter
        onCheckCodeOk:{
            timerFirstCheck.running = false
            register.visible = false
            dataFilter.CheckDB();
        }
        onCheckCodeError:{
            timerFirstCheck.running = false
            register.visible = true
        }
    }

    Register{
        id: register
        width: parent.width; height: parent.height - 80
        z: 1
        visible: false
        anchors.centerIn: parent
    }

    Timer {
        id: timerFirstCheck
        interval: 1; running: true; repeat: false
        onTriggered: {
            dataFilter.FirstCheck();
        }
    }

}






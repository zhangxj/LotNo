import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import "func.js" as Func

ApplicationWindow {
    //title: qsTr("条码录入系统")
    width: 1024; height: 600
    menuBar: MenuBar {
        Menu {
            title: qsTr("系统")
            MenuItem {
                text: qsTr("退出")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("操作")
            MenuItem {
                id: luru
                text: qsTr("录入")
                onTriggered: {
                    dataFilter.clearData()
                    iconSource = Func.get_image_path("star-512.png")
                    search.iconSource = ""
                    pageLoader.source = "LuRu.qml"
                }
            }
            MenuSeparator {}
            MenuItem {
                id: search
                text: qsTr("查询")
                onTriggered:{
                    dataFilter.clearData()
                    luru.iconSource = ""
                    search.iconSource = Func.get_image_path("star-512.png")
                    pageLoader.source = "Search.qml"
                }
            }
        }
        Menu{
            title: qsTr("帮助")
            MenuItem{
                text: qsTr("关于")
                onTriggered: dataFilter.OnAbout();
            }
        }
    }

    Connections{
        target: dataFilter
        onCheckCodeOk:{
            timerFirstCheck.running = false
            register.visible = false
        }
        onCheckCodeError:{
            timerFirstCheck.running = false
            register.visible = true
        }
    }
    Register{
        id: register
        z: 1
        visible: false
        width: parent.width; height: parent.height
    }

    Loader {
        id: pageLoader
        focus: true
        width: parent.width; height: parent.height
        source: "LuRu.qml"
    }


    Timer {
        id: timerFirstCheck
        interval: 1; running: true; repeat: true
        onTriggered: dataFilter.FirstCheck();
    }


}

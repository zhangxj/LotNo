import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    title: qsTr("")
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
                text: qsTr("录入")
                onTriggered: {
                    dataFilter.clearData()
                    pageLoader.source = "LuRu.qml"
                }
            }
            MenuSeparator {}
            MenuItem {
                text: qsTr("查询")
                onTriggered:{
                    dataFilter.clearData()
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

    Loader {
        id: pageLoader
        focus: true
        width: parent.width; height: parent.height
        source: "LuRu.qml"
    }


/*

    LuRu{
        id: luru
        width: parent.width; height: parent.height
        visible: true
    }

    Search{
        id: search
        width: parent.width; height: parent.height
        visible: false
    }
*/
}

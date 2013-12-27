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
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("操作")
            MenuItem {
                text: qsTr("录入")
                onTriggered: {
                    luru.visible=true;
                    search.visible = false
                    dataFilter.clearData()
                }
            }
            MenuItem {
                text: qsTr("查询")
                onTriggered:{
                    luru.visible=false;
                    search.visible = true;
                    dataFilter.clearData()
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

    LuRu{
        id: luru
        width: parent.width; height: parent.height
        visible: false
    }

    Search{
        id: search
        width: parent.width; height: parent.height
        visible: true
    }

}

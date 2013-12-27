import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow{
    menuBar: MenuBar {
        Menu {
            title: qsTr("系统")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

    }
}

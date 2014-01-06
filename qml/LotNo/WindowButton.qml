import QtQuick 1.1
import "func.js" as Func

Item{
    id : win_button
    property alias model_data:rpt.model
    property bool msg_unread: false
    signal clicked(string value);
    width : 30 * model_data.length
    height:25;
    Row{
        spacing : 7
        Repeater{
            id : rpt
            Rectangle {
                width: 23;height: 25
                color: "transparent"
                Image {
                    width: 1;height: 25;
                    source: Func.get_image_path("line_one.png")
                    visible:index != 0 || model_data.length != 0;
                }
                Image {
                    x: 8;y : 5;
                    width: 15;height: 15
                    source: Func.get_image(modelData)
                }
                MouseArea {
                    anchors.fill : parent
                    onClicked : {
                        if (modelData == "minimum"){
                            main_window.showMinimized()
                        }else if(modelData == "close"){
                            app.quit();
                        }else{
                            win_button.clicked(modelData);
                        }
                    }
                }
            }
        }
    }
}

import QtQuick 1.1
import "func.js" as Func

Rectangle {
    id: form
    color: "transparent"

    Column{
        id: row_text
        spacing: 30
        anchors.centerIn: parent

        Row{
            spacing: 10
            Text{
                text: '数据库IP:'
                font.pixelSize: 20
                anchors.verticalCenter: ip.verticalCenter
            }
            TextInput_1{
                id: ip
                focus: true
                text: dataFilter.getIp()
                width: 300; height: 50
                onFinished: {
                    username.focus = true
                }
            }
        }

        Row{
            spacing: 10
            Text{
                text: '用 户 名:'
                font.pixelSize: 20
                anchors.verticalCenter: username.verticalCenter
            }
            TextInput_1{
                id: username
                text: dataFilter.getUser()
                width: 300; height: 50
                onFinished: {
                    pwd.focus = true
                }
            }
        }

        Row{
            spacing: 10
            Text{
                text: '密    码:'
                font.pixelSize: 20
                anchors.verticalCenter: pwd.verticalCenter
            }
            TextInput_1{
                id: pwd
                text: dataFilter.getPwd()
                width: 300; height: 50
                onFinished: {
                }
            }
        }



        Button{
            width: 160; height: 60
            anchors.horizontalCenter: row_text.horizontalCenter
            text: "检测并保存"
            onClicked: {
                dataFilter.setDBConfig(ip.text, username.text, pwd.text,mss_ip.text, mss_username.text,mss_pwd.text, mss_db.text);
            }
        }
    }

    Text{
        id: label
        text: ""
        anchors.horizontalCenter: form.horizontalCenter
        anchors.bottom: row_text.top
        anchors.bottomMargin: 20
        font.pixelSize: 25
        color: 'red'
    }

    Connections
    {
        target: dataFilter
        onStringChanged: {
            label.text = dataFilter.getString()
        }
    }
}

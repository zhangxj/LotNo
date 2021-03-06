

function get_image(name){
    var mapping = {
        "minimum" : "small_icon.png",
        "maximum" : "big_icon.png",
        "close" : "shut_icon.png",
    };
    return get_image_path(mapping[name]);
}

function get_image_path(file_name){
    return "../LotNo/images/" + file_name;
}

/*[{'id': 'system', 'value': '系统', 'items': [
                {'id': 'config', 'value': '数据库配置', 'page': 'Config.qml'},
                {'id': 'quit', 'value': '退出'}
            ]
        },
        {'id': 'op', 'value': '操作', 'items': [
                {'id': 'record', 'value': '录入系统', 'page': 'record.qml'},
                {'id': 'record_6ADKN', 'value': '6ADKN 录入', 'page': 'record_6ADKN.qml'},
                {'id': 'record_5FDKN', 'value': '5FDKN 录入', 'page': 'record_5FDKN.qml'},
                {'id': 'search', 'value': '查询', 'page': 'Search.qml'}
            ]
        },
        {'id': 'help', 'value': '帮助', 'items': [
                {'id': 'about', 'value': '关于'}
            ]
        }
    ]*/
function getMenuModel(p){
    if(p === "SMF_P1"){
        return [{'id': 'system', 'value': '系统', 'items': [
                        {'id': 'config', 'value': '数据库配置', 'page': 'Config.qml'},
                        //{'id': 'badmark_config', 'value': 'BadMark数据库配置', 'page': 'BadMarkConfig.qml'},
                        {'id': 'record_Save', 'value': '文件路径配置', 'page': 'record_Save.qml'},
                        {'id': 'quit', 'value': '退出'}
                    ]
                },
                {'id': 'op', 'value': '操作', 'items': [
                        {'id': 'record_6ADKN', 'value': '6ADKN 录入', 'page': 'record_6ADKN.qml', 'checked': '1'},
                        {'id': 'record_5FDKN', 'value': '5FDKN 录入', 'page': 'record_5FDKN.qml'},
                        {'id': 'record_32FGRX_12', 'value': '32FGRX_12 录入', 'page': '32FGRX_12.qml'},
                        {'id': 'record_32FGRX_16', 'value': '32FGRX_16 录入', 'page': 'record_32FGRX_8AGRX.qml'},
                        {'id': 'record_8AGRX', 'value': '8AGRX 录入', 'page': 'record_8AGRX.qml'},
                        {'id': 'record_6FDKN', 'value': '6FDKN 录入', 'page': 'record_6FDKN.qml'},
                        {'id': 'record_7ADKN', 'value': '7ADKN 录入', 'page': 'record_7ADKN.qml'},
                        {'id': 'record_6FDKN_P2', 'value': '6FDKN-P2 录入', 'page': 'record_6FDKN_P2.qml'},
                        {'id': 'record_7ADKN_EVT', 'value': '7ADKN EVT 录入', 'page': 'record_7ADKN_EVT.qml'},
                        {'id': 'record_54ZLCD', 'value': '54ZLCD 录入', 'page': 'record_54ZLCD.qml'},
                        {'id': 'record_64ZLCD', 'value': '64ZLCD 录入', 'page': 'record_64ZLCD.qml'},
                        {'id': 'search', 'value': '查询', 'page': 'Search.qml'}
                    ]
                },
                {'id': 'help', 'value': '帮助', 'items': [
                        {'id': 'about', 'value': '关于'}
                    ]
                }
            ]
    }else if(p === "SMF_P2"){
        return [{'id': 'system', 'value': '系统', 'items': [
                        {'id': 'config', 'value': '数据库配置', 'page': 'Config_P2.qml'},
                        {'id': 'record_Save', 'value': '文件路径配置', 'page': 'record_Save.qml'},
//                        {'id': 'settings', 'value': '设置', 'page': 'settings.qml'},
                        {'id': 'quit', 'value': '退出'}
                    ]
                },
                {'id': 'op', 'value': '操作', 'items': [
                        {'id': 'record', 'value': '录入系统', 'page': 'record.qml', 'checked': '1'},
                        {'id': 'record_re', 'value': '补录系统', 'page': 'record_re.qml'},
                        {'id': 'record_search', 'value': '查询系统', 'page': 'record_Search.qml'}
                    ]
                },
                {'id': 'help', 'value': '帮助', 'items': [
                        {'id': 'about', 'value': '关于'}
                    ]
                }
            ]
    }else if(p === "SMF_P3"){
        return [{'id': 'system', 'value': '系统', 'items': [
                        {'id': 'config', 'value': '数据库配置', 'page': 'Config.qml'},
                        {'id': 'quit', 'value': '退出'}
                    ]
                },
                {'id': 'op', 'value': '操作', 'items': [
                        {'id': 'record_fanxiu', 'value': '返修品录入', 'page': 'record_FanXiu.qml', 'checked': '1'},
                        {'id': 'search_fanxiu', 'value': '返修品查询', 'page': 'SearchFanXiu.qml'}
                    ]
                },
                {'id': 'help', 'value': '帮助', 'items': [
                        {'id': 'about', 'value': '关于'}
                    ]
                }
            ]
    }
}

function getDefaultPage(p){
    var menu = getMenuModel(p);
    for(var i = 0; i < menu.length; i++){
        var items = menu[i].items;
        for(var j = 0; j < items.length; j++){
            if(items[j].checked === "1"){
                return items[j].page
            }
        }
    }
}

function getPage(p, id){
    var menu = getMenuModel(p);
    for(var i = 0; i < menu.length; i++){
        var items = menu[i].items;
        for(var j = 0; j < items.length; j++){
            if(items[j].id === id){
                return items[j].page
            }
        }
    }
}

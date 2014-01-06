

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

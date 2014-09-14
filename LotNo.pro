# Add more folders to ship with the application, here
folder_01.source = qml/LotNo
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += sql network
# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    datafilter.cpp \
    database.cpp \
    about.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    database.h \
    about.h \
    datafilter.h

RC_FILE = LotNo.rc

OTHER_FILES += \
    qml/LotNo/generate_code.qml \
    qml/LotNo/record_6ADKN.qml \
    qml/LotNo/record_6ADKN.qml \
    qml/LotNo/MyTableView.qml \
    qml/LotNo/BadMarkConfig.qml \
    qml/LotNo/record_6FDKN.qml

#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T20:13:14
#
#-------------------------------------------------

QT       -= gui

QT      += qml quick

TARGET = Encode
TEMPLATE = lib

DEFINES += ENCODE_LIBRARY

SOURCES += kernel.cpp \              
                src/Audio/Opus/Encode.cpp \
../../../Common/Network/Packet.cpp

HEADERS += kernel.h \
                inc/Babel/Audio/IEncode.hh \

HEADERS +=      ../../Common/IPluginView.h          \
                ../../Common/IClientPlugin.h        \
                ../../Common/INetworkManager.h      \
                ../../Common/QPacket.h

HEADERS +=      ../../../Common/IPlugin.h           \
                ../../../Common/Network/Packet.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix {
    LIBS += -L/usr/local/lib -lopus
    LIBS += -L/usr/local/lib -lportaudio
    INCLUDEPATH += /usr/local/include/
}ß

INCLUDEPATH += ./inc
#INCLUDEPATH += $$quote(C:\\Program Files (x86)\\opus-1.1\\include)
#INCLUDEPATH += $$quote(C:\\Users\\louis\\Downloads\\opus-1.1.tar\\opus-1.1\\win32)


#LIBS += C:\Users\louis\Downloads\opus-1.1.tar\opus-1.1\win32\VS2010\x64\Debug\opus.lib
#LIBS += C:\Users\louis\Downloads\opus-1.1.tar\opus-1.1\win32\VS2010\x64\Debug\celt.lib
#LIBS += C:\Users\louis\Downloads\opus-1.1.tar\opus-1.1\win32\VS2010\x64\Debug\silk_common.lib
#LIBS += C:\Users\louis\Downloads\opus-1.1.tar\opus-1.1\win32\VS2010\x64\Debug\silk_float.lib
#LIBS += C:\Users\louis\Downloads\opus-1.1.tar\opus-1.1\win32\VS2010\x64\Debug\silk_fixed.lib

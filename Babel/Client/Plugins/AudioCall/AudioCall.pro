#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T18:58:33
#
#-------------------------------------------------

QT       -= gui

QT      +=  qml quick

TARGET = AudioCall

TEMPLATE = lib

DEFINES += AUDIOCALL_LIBRARY

SOURCES += Kernel.cpp \
                            ../../../Common/Network/Packet.cpp  \

HEADERS += Kernel.h
HEADERS += IEncode.hpp
HEADERS += IStream.hpp

HEADERS +=      ../../Common/IPluginView.h          \
                ../../Common/IClientPlugin.h        \
                ../../Common/INetworkManager.h      \
                ../../Common/QPacket.h              \

HEADERS +=      ../../../Common/IPlugin.h           \
                ../../../Common/Network/Packet.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

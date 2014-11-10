#-------------------------------------------------
#
# Project created by QtCreator 2014-11-01T22:26:14
#
#-------------------------------------------------

QT       -= gui

TARGET = ContactClient
TEMPLATE = lib

DEFINES += CONTACTCLIENT_LIBRARY

SOURCES += ContactClient.cpp \
    ../../../../Common/Network/Packet.cpp \
    ../../../../Common/Network/PacketManager.cpp

HEADERS += ContactClient.h\
        contactclient_global.h \
    ../../../../Common/Network/Packet.hpp \
    ../../../../Common/Network/PacketManager.hpp \
    ../../../../Common/IPlugin.h \
    ../../../Common/IClientPlugin.h \
    ../../../Common/inetworkmanager.h \
    ../../../Common/IPluginView.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

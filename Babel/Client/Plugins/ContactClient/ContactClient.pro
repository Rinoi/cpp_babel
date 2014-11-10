#-------------------------------------------------
#
# Project created by QtCreator 2014-11-01T23:06:38
#
#-------------------------------------------------

QT              -=      gui

QT              +=      qml quick

TARGET          =       connection
TEMPLATE        =       lib

DEFINES         +=      CONNECTION_LIBRARY

SOURCES         +=      Kernel.cpp                      \
                        ../../../Common/Network/Packet.cpp \
    ContactClientanchor.cpp

HEADERS         +=      Kernel.h                        \
                        ConnectionAnchor.h \
    ContactClientanchor.h

HEADERS         +=      ../../Common/IPluginView.h     \
                        ../../Common/IClientPlugin.h   \
                        ../../Common/INetworkManager.h

HEADERS         +=      ../../../Common/IPlugin.h       \
                        ../../../Common/Network/Packet.hpp

unix
{
  target.path   =       /usr/lib
  INSTALLS      +=      target
}

RESOURCES += \
    ContactClient.qrc


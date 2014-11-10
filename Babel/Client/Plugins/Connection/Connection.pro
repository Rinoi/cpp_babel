#-------------------------------------------------
#
# Project created by QtCreator 2014-10-28T11:31:13
#
#-------------------------------------------------

QT              -=      gui

QT              +=      qml quick

TARGET          =       connection
TEMPLATE        =       lib

DEFINES         +=      CONNECTION_LIBRARY

SOURCES         +=      Kernel.cpp                          \
                        ConnectionAnchor.cpp                \
                        ../../Common/QPacket.cpp            \
                        ../../../Common/Network/Packet.cpp  \

HEADERS         +=      Kernel.h                        \
                        ConnectionAnchor.h

HEADERS         +=      ../../Common/IPluginView.h     \
                        ../../Common/IClientPlugin.h   \
                        ../../Common/INetworkManager.h \
                        ../../Common/QPacket.h

HEADERS         +=      ../../../Common/IPlugin.h       \
                        ../../../Common/Network/Packet.hpp

unix
{
  target.path   =       /usr/lib
  INSTALLS      +=      target
}

RESOURCES += Connection.qrc

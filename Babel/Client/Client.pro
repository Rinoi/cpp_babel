TEMPLATE        =       app

QT              +=      qml quick widgets

SOURCES         +=      main.cpp                        \
                        Application.cpp                 \
                        PluginLoader.cpp \
    Network/networkmanager.cpp \
    Network/networktcp.cpp \
    Network/networkudp.cpp \
    ../Common/Network/Packet.cpp \
    Common/QPacket.cpp \
    ApplicationAnchor.cpp \

HEADERS         +=      Application.h                   \
                        PluginLoader.h                  \
                        PluginView.h \
                        Network/inetwork.h \
                        Network/networkmanager.h \
                        Network/networktcp.h \
                        Network/networkudp.h \
                        Common/INetworkManager.h \
                        ../Common/Network/Packet.hpp \
                        Common/QPacket.h \
                        ApplicationAnchor.h \

HEADERS         +=      ./Common/IClientPlugin.h       \
                        ./Common/IPluginView.h

HEADERS         +=      ../Common/Packet.hpp           \
                        ../Common/IPlugin.h

RESOURCES       +=      ./Resources/qml.qrc

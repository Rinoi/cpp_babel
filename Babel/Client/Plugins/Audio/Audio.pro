#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T16:40:04
#
#-------------------------------------------------

QT       -= gui

QT      += qml quick

TARGET = Audio

TEMPLATE = lib

DEFINES += AUDIO_LIBRARY

SOURCES += Kernel.cpp \
            ./src/UserPeriph.cpp \
            ./src/Audio/Input/PortAudio/InputPeriph.cpp \
            ./src/Audio/Output/PortAudio/Periph.cpp \
            ./src/Audio/PortAudio/Stream.cpp \
            ../../../Common/Network/Packet.cpp \



HEADERS += Kernel.h \
            ./inc/Babel/IPeriph.hpp \
            ./inc/Babel/IStream.hpp \
            ./inc/Babel/UserPeriph.hh \
            ./inc/Babel/Audio/IEncode.hpp \
            ./inc/Babel/Audio/IPeriph.hpp \
            ./inc/Babel/Audio/IStream.hpp \
            ./inc/Babel/Audio/Input/APeriph.hpp \
            ./inc/Babel/Audio/Input/PortAudio/Periph.hh \
            ./inc/Babel/Audio/Output/APeriph.hpp \
            ./inc/Babel/Audio/Output/PortAudio/Periph.hh \
            ./inc/Babel/Audio/PortAudio/Stream.hh \



HEADERS +=      ../../Common/IPluginView.h          \
                ../../Common/IClientPlugin.h        \
                ../../Common/INetworkManager.h      \
                ../../Common/QPacket.h

HEADERS +=      ../../../Common/IPlugin.h           \
                ../../../Common/Network/Packet.hpp

unix {
    INCLUDEPATH += /usr/local/include/
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./inc




INCLUDEPATH += $$quote(C:\\Program Files (x86)\\portaudio\\include\\)

LIBS += C:\Users\louis\Downloads\precompiled-portaudio-windows-master\portaudio-r1891-build\lib\x64\Debug\portaudio_x64.lib


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
                src/UserPeriph.cpp \
                src/Audio/Input/PortAudio/Periph.cpp \
                src/Audio/Output/PortAudio/Periph.cpp \
                src/Audio/PortAudio/Stream.cpp \
                src/Audio/Opus/Encode.cpp \
                src/Audio/AudioPacket.cpp \



HEADERS += kernel.h \
                inc/UserPeriph.cpp \
                inc/Audio/Input/PortAudio/Periph.cpp \
                inc/Audio/Output/PortAudio/Periph.cpp \
                inc/Audio/PortAudio/Stream.cpp \
                inc/Audio/Opus/Encode.cpp \
                inc/Audio/AudioPacket.cpp \

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../lib/opusfile/ -llibopusfile
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../lib/opusfile/ -llibopusfiled
else:unix: LIBS += -L$$PWD/../../../../../../../../lib/opusfile/ -llibopusfile

INCLUDEPATH += $$PWD/../../../../../../../../lib/opusfile
DEPENDPATH += $$PWD/../../../../../../../../lib/opusfile

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    pcps_sigthread/pcps_sigthread.c \
    pcps_threadinit/pcps_threadinit.c

LIBS += -pthread

HEADERS += \
    pcps.h \
    pcps_sigthread/pcps_sigthread.h \
    pcps_threadinit/pcps_threadinit.h

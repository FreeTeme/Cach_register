QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add.cpp \
    cart.cpp \
    carts.cpp \
    dialog.cpp \
    dialog_admin.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    product.cpp \
    productmanager.cpp \
    registretion.cpp

HEADERS += \
    add.h \
    cart.h \
    carts.h \
    dialog.h \
    dialog_admin.h \
    mainwindow.h \
    menu.h \
    product.h \
    productmanager.h \
    registretion.h

FORMS += \
    add.ui \
    cart.ui \
    carts.ui \
    dialog.ui \
    dialog_admin.ui \
    mainwindow.ui \
    menu.ui \
    registretion.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

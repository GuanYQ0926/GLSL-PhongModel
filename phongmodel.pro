TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    glutils.cpp \
    glslprogram.cpp \
    sceneads.cpp \
    vbotorus.cpp \
    drawable.cpp

HEADERS += \
    scene.h \
    defines.h \
    glutils.h \
    gllib.h \
    glslprogram.h \
    sceneads.h \
    vbotorus.h \
    drawable.h

INCLUDEPATH += /usr/include/GL \
/usr/include/glm \
/usr/include/glfw

LIBS += /usr/lib/x86_64-linux-gnu/libGLEW.so \
/usr/lib/x86_64-linux-gnu/libglfw.so \
/usr/lib/x86_64-linux-gnu/libGL.so \
/usr/lib/x86_64-linux-gnu/libGLU.so \
/usr/lib/x86_64-linux-gnu/libglut.so \

DISTFILES += \
    shader/phong.frag \
    shader/phong.vert \

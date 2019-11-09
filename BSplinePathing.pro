QT          += core gui widgets

TEMPLATE    = app
CONFIG      += c++17

TARGET      = BSplinePathing

INCLUDEPATH +=  ./GSL

HEADERS += \
    GSL/gsl_math.h \
    GSL/math_constants.h \
    GSL/matrix2x2.h \
    GSL/matrix3x3.h \
    GSL/matrix4x4.h \
    GSL/vector2d.h \
    GSL/vector3d.h \
    GSL/vector4d.h \
    LAS/lasloader.h \
    bsplinecurve.h \
    camera.h \
    gltypes.h \
    input.h \
    mainwindow.h \
    npc.h \
    octahedronball.h \
    renderwindow.h \
    shader.h \
    texture.h \
    triangle.h \
    trianglesurface.h \
    trophy.h \
    vertex.h \
    visualobject.h \
    xyz.h

SOURCES += \
    GSL/gsl_math.cpp \
    GSL/matrix2x2.cpp \
    GSL/matrix3x3.cpp \
    GSL/matrix4x4.cpp \
    GSL/vector2d.cpp \
    GSL/vector3d.cpp \
    GSL/vector4d.cpp \
    bsplinecurve.cpp \
    camera.cpp \
    input.cpp \
    main.cpp \
    mainwindow.cpp \
    npc.cpp \
    octahedronball.cpp \
    renderwindow.cpp \
    shader.cpp \
    texture.cpp \
    triangle.cpp \
    trianglesurface.cpp \
    trophy.cpp \
    vertex.cpp \
    visualobject.cpp \
    xyz.cpp

FORMS += \
    mainwindow.ui

DISTFILES += \
    .gitattributes \
    .gitignore \
    .gitmodules \
    1.las \
    Assets/ball.txt \
    Assets/hund.bmp \
    LAS/.gitattributes \
    LAS/.gitignore \
    LAS/README.md \
    Mountain.las \
    plainfragment.frag \
    plainvertex.vert \
    texturefragmet.frag \
    texturevertex.vert

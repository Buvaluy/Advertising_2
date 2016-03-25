#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T19:16:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += webkitwidgets testlib
TARGET = Slavik_ne_vk_0_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    func.cpp

HEADERS  += mainwindow.h \
    func.h

FORMS    += mainwindow.ui


INCLUDEPATH += D:\Program_Files\opencv\openCvBinari2\install\include
LIBS += -L"D:/Program_Files/opencv/openCvBinari2/install/x64/mingw/bin"
LIBS += -LD:/Program_Files/opencv/openCvBinari2/install/x64/mingw/lib \
        -llibopencv_calib3d2411     \
        -llibopencv_contrib2411     \
        -llibopencv_core2411        \
        -llibopencv_features2d2411  \
        -llibopencv_flann2411       \
        -llibopencv_gpu2411         \
        -llibopencv_highgui2411     \
        -llibopencv_imgproc2411     \
        -llibopencv_legacy2411      \
        -llibopencv_ml2411          \
        -llibopencv_nonfree2411     \
        -llibopencv_objdetect2411   \
        -llibopencv_ocl2411         \
        -llibopencv_photo2411       \
        -llibopencv_stitching2411   \
        -llibopencv_superres2411    \
        -llibopencv_video2411       \
        -llibopencv_videostab2411
INCLUDEPATH += LIBS += -lopencv_core2411 -lopencv_highgui2411 -lopencv_imgproc2411

RESOURCES += \
    res.qrc
RC_FILE = resIco.rc

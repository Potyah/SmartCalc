QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17 app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    QCUSTOMPLOT/qcustomplot.cpp \
    VIEW/calculatorView.cpp \
    VIEW/creditView.cpp \
    VIEW/depositView.cpp \
    VIEW/graphView.cpp \
    CONTROLLER/calculatorController.cpp \
    MODEL/calculatorModel.cpp \
    MODEL/creditModel.cpp \
    MODEL/depositModel.cpp \
    MODEL/graphModel.cpp \

HEADERS += \
    QCUSTOMPLOT/qcustomplot.h \
    VIEW/calculatorView.h \
    VIEW/creditView.h \
    VIEW/depositView.h \
    VIEW/graphView.h \
    CONTROLLER/calculatorController.h \
    MODEL/calculatorModel.h \
    MODEL/creditModel.h \
    MODEL/depositModel.h \
    MODEL/graphModel.h \

FORMS += \
    VIEW/UI/calculatorView.ui \
    VIEW/UI/creditView.ui \
    VIEW/UI/depositView.ui \
    VIEW/UI/graphView.ui

ICON = img/jmadie_calc.png

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

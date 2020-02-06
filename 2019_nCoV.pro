QT += core
QT -= gui

TARGET = 2019_nCoV
CONFIG += console
CONFIG -= app_bundle
CONFIG += C++14

INCLUDEPATH += vendor/

#DEFINES += MX_USING_ARRAY_2
DEFINES += USE_RND_MT19937_64
DEFINES += USE_RND_BUFF_1
DEFINES += USE_RND_F_BUFF_1
DEFINES += USE_RND_PROB_0


TEMPLATE = app

SOURCES += main.cpp \
    vendor/MRndCPP/init_chaos.cpp \
    vendor/MRndCPP/rnd_add_rot.cpp \
    vendor/MRndCPP/rnd_base.cpp \
    vendor/MRndCPP/rnd_buff0.cpp \
    vendor/MRndCPP/rnd_buff1.cpp \
    vendor/MRndCPP/rnd_comp_fib.cpp \
    vendor/MRndCPP/rnd_comp.cpp \
    vendor/MRndCPP/rnd_f_buff0.cpp \
    vendor/MRndCPP/rnd_f_buff1.cpp \
    vendor/MRndCPP/rnd_fib.cpp \
    vendor/MRndCPP/rnd_float.cpp \
    vendor/MRndCPP/rnd_knuthb.cpp \
    vendor/MRndCPP/rnd_lin.cpp \
    vendor/MRndCPP/rnd_mlin.cpp \
    vendor/MRndCPP/rnd_mt1993764.cpp \
    vendor/MRndCPP/rnd_prob.cpp \
    vendor/MRndCPP/rnd_ranlux48.cpp \
    vendor/MRndCPP/rnd_wyhash64.cpp \
    vendor/MRndCPP/rnd_wyhash64m.cpp \
    vendor/MRndCPP/rnd_xor2.cpp \
    vendor/MRndCPP/sandbox00.cpp \
    vendor/MRndCPP/sandbox01.cpp \
    vendor/MRndCPP/sandbox02.cpp \
    vendor/MRndCPP/test00.cpp \
    vendor/MRndCPP/test01.cpp \
    vendor/MRndCPP/test02.cpp \
    vendor/MRndCPP/test03.cpp \
    vendor/MRndCPP/test04.cpp \
    vendor/MiscCPP/m_limits.cpp \
    vendor/MxCPP/mx_array.cpp

DISTFILES +=

HEADERS += \
    vendor/MRndCPP/buffs.h \
    vendor/MRndCPP/defs.h \
    vendor/MRndCPP/init_chaos.h \
    vendor/MRndCPP/prob.h \
    vendor/MRndCPP/rnd_add_rot.h \
    vendor/MRndCPP/rnd_base.h \
    vendor/MRndCPP/rnd_buff0.h \
    vendor/MRndCPP/rnd_buff1.h \
    vendor/MRndCPP/rnd_comp.h \
    vendor/MRndCPP/rnd_f_buff0.h \
    vendor/MRndCPP/rnd_f_buff1.h \
    vendor/MRndCPP/rnd_fib.h \
    vendor/MRndCPP/rnd_knuthb.h \
    vendor/MRndCPP/rnd_lin.h \
    vendor/MRndCPP/rnd_mlin.h \
    vendor/MRndCPP/rnd_mt1993764.h \
    vendor/MRndCPP/rnd_prob.h \
    vendor/MRndCPP/rnd_ranlux48.h \
    vendor/MRndCPP/rnd_wyhash64.h \
    vendor/MRndCPP/rnd_wyhash64m.h \
    vendor/MRndCPP/rnd_xor2.h \
    vendor/MRndCPP/rnd.h \
    vendor/MRndCPP/use_rnd_add_rot_1.h \
    vendor/MRndCPP/use_rnd_add_rot_2.h \
    vendor/MRndCPP/use_rnd_add_rot_3.h \
    vendor/MRndCPP/use_rnd_add_rot_4.h \
    vendor/MRndCPP/use_rnd_add_rot_5.h \
    vendor/MRndCPP/use_rnd_add_rot_6.h \
    vendor/MRndCPP/use_rnd_buff_0.h \
    vendor/MRndCPP/use_rnd_buff_1.h \
    vendor/MRndCPP/use_rnd_comp_1.h \
    vendor/MRndCPP/use_rnd_comp_2.h \
    vendor/MRndCPP/use_rnd_comp_3.h \
    vendor/MRndCPP/use_rnd_comp_4.h \
    vendor/MRndCPP/use_rnd_f_buff_0.h \
    vendor/MRndCPP/use_rnd_f_buff_1.h \
    vendor/MRndCPP/use_rnd_fib_1.h \
    vendor/MRndCPP/use_rnd_fib_2.h \
    vendor/MRndCPP/use_rnd_fib_3.h \
    vendor/MRndCPP/use_rnd_fib_4.h \
    vendor/MRndCPP/use_rnd_fib_5.h \
    vendor/MRndCPP/use_rnd_fib_6.h \
    vendor/MRndCPP/use_rnd_knuth_b.h \
    vendor/MRndCPP/use_rnd_lin_1.h \
    vendor/MRndCPP/use_rnd_lin_2.h \
    vendor/MRndCPP/use_rnd_lin_3.h \
    vendor/MRndCPP/use_rnd_lin_4.h \
    vendor/MRndCPP/use_rnd_lin_5.h \
    vendor/MRndCPP/use_rnd_lin_6.h \
    vendor/MRndCPP/use_rnd_mlin_0.h \
    vendor/MRndCPP/use_rnd_mt19937_64.h \
    vendor/MRndCPP/use_rnd_prob_0.h \
    vendor/MRndCPP/use_rnd_ranlux_48.h \
    vendor/MRndCPP/use_rnd_wyhash64_0.h \
    vendor/MRndCPP/use_rnd_wyhash64m_0.h \
    vendor/MRndCPP/use_rnd_xor2_0.h \
    vendor/MiscCPP/m_limits.h \
    vendor/MxCPP/mx_array.h


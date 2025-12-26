# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(cons_audiodevices LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Multimedia)


add_executable(cons5_audiodevices
     cons5_audiodevices.cpp
)


target_link_libraries(cons5_audiodevices PUBLIC
    Qt5::Core
    Qt5::Multimedia
)

##qt_add_ios_ffmpeg_libraries(cons5_audiodevices)


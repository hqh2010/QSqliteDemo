set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_definitions("-DQT_MESSAGELOGCONTEXT")
# 规范要求代码中include带上模块名
# include_directories(util UTIL_INCLUDE)

aux_source_directory(util UTIL_SRC)


find_package(PkgConfig REQUIRED)
find_package(Qt5Core REQUIRED)
#加入QT sqlite支持
find_package(Qt5Sql REQUIRED)

set(MAIN_SOURCES
        main.cpp
        resource/resource.qrc
        ${UTIL_SRC}
        ${UTIL_INCLUDE}
        )

#set(DTK_LIBS dtkcore)
set(LINK_LIBS
    stdc++
    Qt5::Core
    Qt5::Sql
    )

add_executable(repohelper
        ${MAIN_SOURCES})

#foreach(_var ${OSTREE1_INCLUDE_DIRS})
#  MESSAGE(STATUS "ostree lib dir: ${_var}")
#endforeach()

target_link_libraries(repohelper PRIVATE ${LINK_LIBS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
install(TARGETS repohelper RUNTIME DESTINATION bin)
# Qt6 Library
find_package(Qt6 6.2 COMPONENTS Core Quick Gui REQUIRED)
# Jsoncpp for persistent storage
find_package(jsoncpp REQUIRED)

set(SOURCES
    keyboard.cc
    cycle_list.cc
    cycle.cc
)

qt_add_executable(keycycler
    main.cc
    ${SOURCES}
)

target_link_libraries(keycycler PRIVATE Qt6::Gui Qt6::Quick jsoncpp_lib)

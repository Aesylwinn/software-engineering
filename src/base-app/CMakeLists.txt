set(
    BASE_APP_SRC_FILES
    application.cpp
)

add_library(if-base-app STATIC ${BASE_APP_SRC_FILES})
target_link_libraries(if-base-app Qt5::Widgets)


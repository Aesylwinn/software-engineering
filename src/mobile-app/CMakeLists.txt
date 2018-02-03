set(MOBILE_APP_SRC_FILES
    application.cpp
    main.cpp
)

# Mobile App Executable
# TODO: setup for android dev
add_executable(if-mobile-app ${MOBILE_APP_SRC_FILES})
target_link_libraries(if-mobile-app if-base-app)
add_custom_command(
    TARGET if-mobile-app
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:if-mobile-app> ${CMAKE_BINARY_DIR}/bin/if-mobile-app
)


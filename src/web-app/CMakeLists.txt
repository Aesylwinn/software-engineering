set(WEB_APP_SRC_FILES
    application.cpp
    main.cpp
    main-page.cpp
)

# Web App Executable
add_executable(if-web-app ${WEB_APP_SRC_FILES})
target_link_libraries(if-web-app if-base-app)
add_custom_command(
    TARGET if-web-app
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:if-web-app> ${CMAKE_BINARY_DIR}/bin/if-web-app
)


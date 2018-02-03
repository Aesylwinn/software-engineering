set(
    SERVER_SRC_FILES
    main.cpp
)

add_executable(if-server ${SERVER_SRC_FILES})
add_custom_command(
    TARGET if-server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:if-server> ${CMAKE_BINARY_DIR}/bin/if-server
)


SET(SOURCE_GROUP ${SOURCE_GROUP}\\azurertos)

ua_add_architecture("azurertos")

if ("${UA_ARCHITECTURE}" STREQUAL "azurertos")

    ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_clock.c)
    ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_architecture_functions.c)

    ua_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

endif()

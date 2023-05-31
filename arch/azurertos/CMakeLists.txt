SET(SOURCE_GROUP ${SOURCE_GROUP}\\azurertos)

ua_add_architecture("azurertos")

if ("${UA_ARCHITECTURE}" STREQUAL "azurertos")

    ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_clock.c)
    ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_architecture_functions.c)

    ua_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    #ua_architecture_append_to_library(netxduo)

    get_target_property(THREADX_INCLUDES azrtos::threadx INCLUDE_DIRECTORIES)
    ua_include_directories(${THREADX_INCLUDES})

    get_target_property(NETXDUO_INCLUDES azrtos::netxduo INCLUDE_DIRECTORIES)
    ua_include_directories(${NETXDUO_INCLUDES})

    #foreach(dir ${THREADX_INCLUDES} ${NETXDUO_INCLUDES})
    #    ua_include_directories(${dir})
    #endforeach()

    ua_architecture_add_definitions(-DTX_INCLUDE_USER_DEFINE_FILE -DNX_INCLUDE_USER_DEFINE_FILE)
endif()

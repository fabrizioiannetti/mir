include_directories(${WLCS_INCLUDE_DIRS})

add_library(
  miral_wlcs_integration MODULE

  miral_integration.cpp
)

target_link_libraries(
  miral_wlcs_integration

  miral-test-framework
  mir-test-doubles-platform-static
  ${WAYLAND_CLIENT_LDFLAGS} ${WAYLAND_CLIENT_LIBRARIES}
)

set(SYMBOL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/symbol.map)

set_target_properties(
  miral_wlcs_integration PROPERTIES

  PREFIX ""
  LINK_FLAGS "-Wl,--version-script,${SYMBOL_FILE}"
  LINK_DEPENDS ${SYMBOL_FILE}
)

pkg_get_variable(WLCS_BINARY wlcs test_runner)

mir_discover_external_gtests(
  NAME wlcs
  COMMAND ${WLCS_BINARY} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/miral_wlcs_integration.so
)

install(TARGETS miral_wlcs_integration LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/mir)

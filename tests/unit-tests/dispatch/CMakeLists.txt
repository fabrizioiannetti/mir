list(APPEND UNIT_TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/test_action_queue.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_dispatch_utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_multiplexing_dispatchable.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_readable_fd.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_threaded_dispatcher.cpp
)

set(UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES} PARENT_SCOPE)

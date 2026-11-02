cmake_minimum_required(VERSION 3.16)
project(shore-backend-mfc VERSION 0.1.0 LANGUAGES CXX)

if(NOT WIN32 OR NOT MSVC)
  message(FATAL_ERROR "The MFC backend requires a Windows MSVC toolchain")
endif()
if(NOT CMAKE_GENERATOR MATCHES "Visual Studio")
  message(FATAL_ERROR "The MFC backend requires a Visual Studio CMake generator")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MFC_FLAG 2)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(shore CONFIG REQUIRED)

add_library(shore_backend_mfc SHARED src/mfc.cpp)
add_library(shore-backend-mfc::shore-backend-mfc ALIAS shore_backend_mfc)
set_target_properties(shore_backend_mfc PROPERTIES
  MFC_FLAG 2
  WINDOWS_EXPORT_ALL_SYMBOLS ON
  EXPORT_NAME shore-backend-mfc
)
target_compile_definitions(shore_backend_mfc PUBLIC _AFXDLL UNICODE _UNICODE)
target_include_directories(shore_backend_mfc
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE src
)
target_link_libraries(shore_backend_mfc PUBLIC shore::shore comctl32)

install(TARGETS shore_backend_mfc EXPORT shoreBackendMfcTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT shoreBackendMfcTargets
  FILE shoreBackendMfcTargets.cmake
  NAMESPACE shore-backend-mfc::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shore-backend-mfc
)

configure_package_config_file(
  cmake/shore-backend-mfcConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/shore-backend-mfcConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shore-backend-mfc
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/shore-backend-mfcConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/shore-backend-mfcConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/shore-backend-mfcConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shore-backend-mfc
)

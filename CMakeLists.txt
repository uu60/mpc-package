cmake_minimum_required(VERSION 3.26)
project(mpc_package)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/ArithmeticShare.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/ArithmeticShare.h")

# install libxx.so to ${CMAKE_INSTALL_PREFIX}/lib
install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        PUBLIC_HEADER DESTINATION include
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

# generate xxTargets.cmake
install(
        EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION lib/cmake/${PROJECT_NAME}
)

# parameters used in xxConfig.cmake
set(INCLUDE_DIRS include)
set(LIBRARIES ${PROJECT_NAME})
set(LIB_DIR lib)

# provided by cmake
include(CMakePackageConfigHelpers)

# generate xxConfigVersion.cmake
write_basic_package_version_file(
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION 0.0.1
        COMPATIBILITY SameMajorVersion
)

# generate xxConfig.cmake
configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
        PATH_VARS INCLUDE_DIRS LIBRARIES LIB_DIR
        INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
)

#[[add_executable(${PROJECT_NAME} main.cpp
        src/ArithmeticShare.cpp
        include/ArithmeticShare.h)]]

install(
        FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION lib/cmake/${PROJECT_NAME}
)

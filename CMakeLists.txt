cmake_minimum_required(VERSION 3.22)
project(mpc_package)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(${PROJECT_NAME} SHARED
        src/utils/MathUtils.cpp
        include/utils/MathUtils.h
        src/executor/Executor.cpp
        include/executor/Executor.h
        src/executor/share/arithmetic/addition/PartialAddShareExecutor.cpp
        include/executor/share/arithmetic/addition/PartialAddShareExecutor.h
        src/utils/Log.cpp
        include/utils/Log.h
        src/executor/share/arithmetic/multiplication/MulShareExecutor.cpp
        include/executor/share/arithmetic/multiplication/MulShareExecutor.h
        src/executor/share/arithmetic/addition/AddShareExecutor.cpp
        include/executor/share/arithmetic/addition/AddShareExecutor.h
        src/executor/ot/RsaOtExecutor.cpp
        include/executor/ot/RsaOtExecutor.h
        src/utils/MpiUtils.cpp
        include/utils/MpiUtils.h
        src/utils/CryptUtils.cpp
        include/utils/CryptUtils.h
        src/utils/System.cpp
        include/utils/System.h
        src/executor/share/arithmetic/multiplication/RsaOtMulShareExecutor.cpp
        include/executor/share/arithmetic/multiplication/RsaOtMulShareExecutor.h
        include/executor/share/arithmetic/multiplication/FixedMulShareExecutor.h
        src/executor/share/arithmetic/multiplication/FixedMulShareExecutor.cpp
        src/executor/share/boolean/xor/XorBoolShareExecutor.cpp
        include/executor/share/boolean/xor/XorBoolShareExecutor.h
        src/executor/share/boolean/and/AndBoolShareExecutor.cpp
        include/executor/share/boolean/and/AndBoolShareExecutor.h
        src/executor/bmt/MulTripleExecutor.cpp
        include/executor/bmt/MulTripleExecutor.h
)
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/executor/arithmetic/AbstractAdditionShareExecutor.h;include/executor/Executor.h")

# install libxx.so to ${CMAKE_INSTALL_PREFIX}/lib
install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)
# headers path
install(DIRECTORY include/
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h")

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

install(
        FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION lib/cmake/${PROJECT_NAME}
)

target_link_libraries(
        ${PROJECT_NAME} PUBLIC MPI::MPI_CXX OpenSSL::SSL OpenSSL::Crypto
)

cmake_minimum_required(VERSION 3.22)
project(mpc_package)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(${PROJECT_NAME} SHARED
        src/utils/Math.cpp
        include/utils/Math.h
        src/Executor.cpp
        include/Executor.h
        src/utils/Log.cpp
        include/utils/Log.h
        src/arithmetic/multiplication/AbstractMultiplicationShareExecutor.cpp
        include/arithmetic/multiplication/AbstractMultiplicationShareExecutor.h
        src/arithmetic/addition/AdditionShareExecutor.cpp
        include/arithmetic/addition/AdditionShareExecutor.h
        src/ot/RsaOtExecutor.cpp
        include/ot/RsaOtExecutor.h
        src/utils/Mpi.cpp
        include/utils/Mpi.h
        src/utils/Crypto.cpp
        include/utils/Crypto.h
        src/utils/System.cpp
        include/utils/System.h
        src/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.cpp
        include/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h
        include/arithmetic/multiplication/FixedMultiplicationShareExecutor.h
        src/arithmetic/multiplication/FixedMultiplicationShareExecutor.cpp
        src/boolean/xor/XorShareExecutor.cpp
        include/boolean/xor/XorShareExecutor.h
        src/boolean/and/AbstractAndShareExecutor.cpp
        include/boolean/and/AbstractAndShareExecutor.h
        src/bmt/RsaOtTripleGenerator.cpp
        include/bmt/RsaOtTripleGenerator.h
        src/bmt/AbstractMultiplicationTripleGenerator.cpp
        include/bmt/AbstractMultiplicationTripleGenerator.h
        src/bmt/FixedTripleGenerator.cpp
        include/bmt/FixedTripleGenerator.h
        src/boolean/and/RsaOtAndShareExecutor.cpp
        include/boolean/and/RsaOtAndShareExecutor.h
        src/boolean/and/FixedAndShareExecutor.cpp
        include/boolean/and/FixedAndShareExecutor.h
        src/comparison/ComparisonExecutor.cpp
        include/comparison/ComparisonExecutor.h
        src/arithmetic/IntShareExecutor.cpp
        include/arithmetic/IntShareExecutor.h
        src/boolean/BoolShareExecutor.cpp
        include/boolean/BoolShareExecutor.h
        src/api/Secret.cpp
        include/api/Secret.h
        src/api/IntSecret.cpp
        include/api/IntSecret.h
        src/api/BoolSecret.cpp
        include/api/BoolSecret.h
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

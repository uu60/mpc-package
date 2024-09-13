cmake_minimum_required(VERSION 3.22)
project(mpc_package)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(${PROJECT_NAME} SHARED
        src/utils/Math.cpp
        include/utils/Math.h
        src/executor/AbstractExecutor.cpp
        include/executor/AbstractExecutor.h
        src/utils/Log.cpp
        include/utils/Log.h
        src/executor/share/arithmetic/multiplication/AbstractMultiplicationShareExecutor.cpp
        include/executor/share/arithmetic/multiplication/AbstractMultiplicationShareExecutor.h
        src/executor/share/arithmetic/addition/AdditionShareExecutor.cpp
        include/executor/share/arithmetic/addition/AdditionShareExecutor.h
        src/executor/ot/RsaOtExecutor.cpp
        include/executor/ot/RsaOtExecutor.h
        src/utils/Mpi.cpp
        include/utils/Mpi.h
        src/utils/Crypto.cpp
        include/utils/Crypto.h
        src/utils/System.cpp
        include/utils/System.h
        src/executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.cpp
        include/executor/share/arithmetic/multiplication/RsaOtMultiplicationShareExecutor.h
        include/executor/share/arithmetic/multiplication/FixedMultiplicationShareExecutor.h
        src/executor/share/arithmetic/multiplication/FixedMultiplicationShareExecutor.cpp
        src/executor/share/boolean/xor/XorShareExecutor.cpp
        include/executor/share/boolean/xor/XorShareExecutor.h
        src/executor/share/boolean/and/AbstractAndShareExecutor.cpp
        include/executor/share/boolean/and/AbstractAndShareExecutor.h
        src/executor/bmt/RsaOtTripleGenerator.cpp
        include/executor/bmt/RsaOtTripleGenerator.h
        src/executor/bmt/AbstractMultiplicationTripleGenerator.cpp
        include/executor/bmt/AbstractMultiplicationTripleGenerator.h
        src/executor/bmt/FixedTripleGenerator.cpp
        include/executor/bmt/FixedTripleGenerator.h
        src/executor/share/boolean/and/RsaOtAndShareExecutor.cpp
        include/executor/share/boolean/and/RsaOtAndShareExecutor.h
        src/executor/share/boolean/and/FixedAndShareExecutor.cpp
        include/executor/share/boolean/and/FixedAndShareExecutor.h
        src/executor/share/comparison/ComparisonExecutor.cpp
        include/executor/share/comparison/ComparisonExecutor.h
        src/executor/share/IntShareExecutor.cpp
        include/executor/share/IntShareExecutor.h
        src/executor/share/AbstractBoolShareExecutor.cpp
        include/executor/share/AbstractBoolShareExecutor.h
        src/data/Secret.cpp
        include/data/Secret.h
        src/data/IntSecret.cpp
        include/data/IntSecret.h
)
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/executor/arithmetic/AbstractAdditionShareExecutor.h;include/executor/AbstractExecutor.h")

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

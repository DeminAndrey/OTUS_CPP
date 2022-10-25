cmake_minimum_required(VERSION 3.14)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

configure_file(version.h.in version.h)

find_package(Boost)

set(AUX_TARGET auxiliary)
set(TEST_TARGET tests)

add_executable(${PROJECT_NAME}
  main.cxx
  filter.h
  ip.h
)

add_executable(${TEST_TARGET}
  input.h
  output.h
  tests.cxx
)

add_library(${AUX_TARGET}
  auxiliary.h
  auxiliary.cxx
)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(${TEST_TARGET}
  ${AUX_TARGET}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})

target_include_directories(${PROJECT_NAME}
  PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${AUX_TARGET}
)

target_include_directories(${AUX_TARGET}
  PRIVATE ${Boost_INCLUDE_DIR}
)

target_link_libraries(${AUX_TARGET}
  PRIVATE ${Boost_LIBRARY_DIR}
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(${TEST_TARGET} PRIVATE
        /W4
    )
    target_compile_options(${AUX_TARGET} PRIVATE
        /W4
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Werror -Wall -Wimplicit-fallthrough -pedantic-errors
    )
    target_compile_options(${TEST_TARGET} PRIVATE
        -Werror -Wall -Wimplicit-fallthrough -pedantic-errors
    )
    target_compile_options(${AUX_TARGET} PRIVATE
        -Werror -Wall -Wimplicit-fallthrough -pedantic-errors
    )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()
add_test(main_test ${TEST_TARGET})

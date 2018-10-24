cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
   project(kkmeans VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
   project(kkmeans VERSION 0.0.1)
endif()

# find_package(dlib REQUIRED)

add_executable(generate_clusters generate_clusters.cpp)
add_executable(generate_sky generate_sky.cpp)
add_executable(kkmeans main.cpp)

set_target_properties(kkmeans PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set_target_properties(kkmeans generate_clusters generate_sky PROPERTIES COMPILE_OPTIONS -W3)
	target_link_libraries(generate_sky dlib::dlib)
	target_link_libraries(generate_clusters dlib::dlib)
	target_link_libraries(kkmeans dlib::dlib)
else()
	find_package(BLAS REQUIRED )

	set_target_properties(kkmeans generate_clusters generate_sky PROPERTIES COMPILE_OPTIONS -Wpedantic -Wall -Wextra)
	target_link_libraries(generate_sky openblas)
	target_link_libraries(generate_clusters openblas)
	target_link_libraries(kkmeans pthread openblas)
endif()

install(TARGETS kkmeans RUNTIME DESTINATION bin)
install(FILES kkmeans_ex.txt DESTINATION bin)
install(FILES kkmeans_sky.txt DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT a@a.a)

include (CPack)


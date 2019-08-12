cmake_minimum_required(VERSION 3.5.0)
project(GeneticAlgorithm)
SET(CMAKE_CXX_STANDARD 14)


SET(PROJECT_SOURCE_DIR src)
SET(TEST_FILES_DIR tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

SET(SOURCE_FILES
  #${PROJECT_SOURCE_DIR}/Color.cpp
  #${PROJECT_SOURCE_DIR}/Grade.cpp
  #${PROJECT_SOURCE_DIR}/Individual.cpp
  #${PROJECT_SOURCE_DIR}/Population.cpp
)

SET(TESTS_FILES
  ${TEST_FILES_DIR}/main_test.cpp
  #${TEST_FILES_DIR}/FileReaderTest.cpp
  #${TEST_FILES_DIR}/HexGridTest.cpp
)

SET(TEST_SOURCES
  ${SOURCE_FILES}
  ${TESTS_FILES}
)

SET(PROGRAM_SOURCES
  ${SOURCE_FILES}
  main.cpp
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --std=c++14")

add_executable(${PROJECT_NAME} ${PROGRAM_SOURCES})
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})


target_link_libraries(${PROJECT_NAME}_tests gtest pthread)

add_custom_target(run
  COMMAND ${PROJECT_NAME}_tests
  DEPENDS ${PROJECT_NAME}_tests
)

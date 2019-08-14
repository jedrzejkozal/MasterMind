cmake_minimum_required(VERSION 3.5.0)
project(GeneticAlgorithm)
SET(CMAKE_CXX_STANDARD 14)


SET(PROJECT_SOURCE_DIR src)
SET(TESTS_DIR tests/src)
SET(STUBS_DIR tests/stubs)
SET(MOCKS_DIR tests/mocks)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})

SET(PROJECT_SOURCES
  #${PROJECT_SOURCE_DIR}/Color.cpp
  #${PROJECT_SOURCE_DIR}/Grade.cpp
  #${PROJECT_SOURCE_DIR}/Individual.cpp
  #${PROJECT_SOURCE_DIR}/Population.cpp
  ${PROJECT_SOURCE_DIR}/Probabilistic.cpp
  ${PROJECT_SOURCE_DIR}/IAlleles.cpp
  ${PROJECT_SOURCE_DIR}/DefaultMutation.cpp
)

SET(TESTS_SOURCES
  tests/main_test.cpp
  ${TESTS_DIR}/ProbabilisticTest.cpp
  ${TESTS_DIR}/DefaultMutationTest.cpp
  ${TESTS_DIR}/IndividualTest.cpp
)

SET(MOCKS_SOURCES
  #${MOCKS_DIR}/ProbabilisticMock.cpp
)

SET(TEST_FILES
  ${PROJECT_SOURCES}
  ${TESTS_SOURCES}
  ${STUBS_SOURCES}
  ${MOCKS_SOURCES}
)

SET(PROGRAM_SOURCES
  ${PROJECT_SOURCES}
  main.cpp
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --std=c++14")

add_executable(${PROJECT_NAME} ${PROGRAM_SOURCES})
add_executable(${PROJECT_NAME}_tests ${TEST_FILES})


target_link_libraries(${PROJECT_NAME}_tests gtest gmock pthread)
#target_link_libraries(${PROJECT_NAME}_tests ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})

add_custom_target(run
  COMMAND ${PROJECT_NAME}_tests
  DEPENDS ${PROJECT_NAME}_tests
)

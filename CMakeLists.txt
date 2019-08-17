cmake_minimum_required(VERSION 3.5.0)
project(GeneticAlgorithm)
SET(CMAKE_CXX_STANDARD 14)


SET(PROJECT_SOURCE_DIR src)
SET(TESTS_DIR tests/src)
SET(UTILS_DIR tests/utils)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})

SET(PROJECT_SOURCES
  ${PROJECT_SOURCE_DIR}/alleles/DefaultAlleles.cpp
  ${PROJECT_SOURCE_DIR}/mutation/DefaultMutation.cpp
  ${PROJECT_SOURCE_DIR}/individual/Individual.cpp
  ${PROJECT_SOURCE_DIR}/individual/IndividualTwoAlleles.cpp
  ${PROJECT_SOURCE_DIR}/individual/IndividualBase.cpp
  ${PROJECT_SOURCE_DIR}/Probabilistic.cpp
)

SET(TESTS_SOURCES
  tests/main_test.cpp
  ${TESTS_DIR}/crossover/DefaultCrossoverTest.cpp
  ${TESTS_DIR}/mutation/DefaultMutationTest.cpp
  ${TESTS_DIR}/selection/DefaultSelectionTest.cpp
  ${TESTS_DIR}/individual/IndividualTest.cpp
  ${TESTS_DIR}/ProbabilisticTest.cpp
  ${TESTS_DIR}/GeneticAlgorithmTest.cpp
  ${TESTS_DIR}/FitnessCalculatorTest.cpp
)

SET(TEST_PROBLEMS
  ${TESTS_DIR}/problems/QuadraticFunction1DTest.cpp
  ${TESTS_DIR}/problems/QuadraticFunction2DTest.cpp
  ${TESTS_DIR}/problems/LocalMaxTest.cpp
  ${TESTS_DIR}/problems/TwoEqualMaxTest.cpp
)

SET(TEST_UTILS
  ${UTILS_DIR}/FitnessFunctions.cpp
  ${UTILS_DIR}/Individuals.cpp
  ${UTILS_DIR}/DecodeFromBinary.cpp
  ${UTILS_DIR}/PrintAlleles.cpp
)

SET(TEST_FILES
  ${PROJECT_SOURCES}
  ${TESTS_SOURCES}
  ${TEST_PROBLEMS}
  ${TEST_UTILS}
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

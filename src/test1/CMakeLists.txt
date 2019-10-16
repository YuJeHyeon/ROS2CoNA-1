cmake_minimum_required(VERSION 2.8.3)

######## Change here! #######
project(test1)	
#############################

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME} 
  CATKIN_DEPENDS roscpp std_msgs 
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/
#  ${PROJECT_SOURCE_DIR}/../../devel/include/
)

 add_executable(${PROJECT_NAME} src/${PROJECT_NAME}.cpp)
 add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

 target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
 )

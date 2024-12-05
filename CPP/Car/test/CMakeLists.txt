add_executable(test_car test_car.cpp)
target_link_libraries(test_car car_lib)
add_test(NAME TestCar COMMAND test_car)
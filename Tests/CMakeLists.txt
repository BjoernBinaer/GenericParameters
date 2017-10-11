add_executable(	ParameterTest 
				ParameterTest.cpp
				TestParameterObject.h
				TestParameterObject.cpp

				CMakeLists.txt
			)

add_dependencies(ParameterTest GenericParameters)
set_target_properties(ParameterTest PROPERTIES FOLDER "Tests")

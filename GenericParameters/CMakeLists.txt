add_library(GenericParameters    	
	Parameter.h
	BoolParameter.h
	NumericParameter.h
	ParameterObject.h

	CMakeLists.txt	
)

set_target_properties(GenericParameters PROPERTIES LINKER_LANGUAGE CXX)
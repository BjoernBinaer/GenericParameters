add_library(GenericParameters    	
	Parameter.h
	EnumParameter.h
	NumericParameter.h
	ParameterObject.h

	CMakeLists.txt	
)

set_target_properties(GenericParameters PROPERTIES LINKER_LANGUAGE CXX)
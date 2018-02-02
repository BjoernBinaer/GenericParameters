# GenericParameters

**GenericParameters** is a C++ library to define generic parameters. A generic parameter can be defined by a pointer to a variable or by set/get-functions. Moreover, a generic parameter stores additional information like the parameter type, max/min limits, a description, etc. Such parameters are very useful, e.g., for an automatic generation of GUI elements. 

The library is used in [SPlisHSPlasH] (https://github.com/InteractiveComputerGraphics/SPlisHSPlasH) to handle all parameters of the implemented fluid simulation methods. 

**Author**: [Jan Bender](http://www.interactive-graphics.de), **License**: MIT

## Libraries using GenericParameters
* [SPlisHSPlasH] (https://github.com/InteractiveComputerGraphics/SPlisHSPlasH) - A C++ library for the physically-based simulation of fluids using Smoothed Particle Hydrodynamics 
* [PBD] (https://github.com/InteractiveComputerGraphics/PositionBasedDynamics) - A C++ library for physically-based simulation of rigid bodies, deformables, cloth and fluids using Position-Based Dynamics (Coming soon)


## Build Instructions

This project is based on [CMake](https://cmake.org/). Simply generate project, Makefiles, etc. using [CMake](https://cmake.org/) and compile the project with the compiler of your choice. The code was tested with the following configurations:
- Windows 10 64-bit, CMake 3.7, Visual Studio 2015 & 2017
- Debian 8 64-bit, CMake 3.7, GCC 4.9.2.

## Usage
Creating a generic parameter for an integer value by providing the pointer of an integer variable:
```c++
	m_intValue = 3;
	MY_INT_PARAMETER = createNumericParameter("intParam", "Int param", &m_intValue);
	setGroup(MY_INT_PARAMETER, "ParameterGroup");
	setDescription(MY_INT_PARAMETER, "Help text");
	IntParameter* intParam = static_cast<IntParameter*>(getParameter(MY_INT_PARAMETER));
	intParam->setMinValue(2);
	intParam->setMaxValue(4);
```

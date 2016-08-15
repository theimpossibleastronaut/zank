cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
# Above line indicates to Cmake that minimum version 2.8 is required.
# As you may have noted all lines beginning with hash symbol are treated as comments by Cmake.
SET(ProjectName Zank)
# In the above line we declared a variable sampleName and assigned it a value MyApp. We will make use of the same later.project(PrjMyApp)
# here we define the project or solution (for visual studio) name

# In following lines we try to find out the packages of additional libraries, if reqd. Here we are trying to locate PCL and mrpt library.
# u may replace the names by yours. Each such package should have a Cmake file in them, if not then we may have to manually define the paths.
# we Show that later.
#find_package(PCL 1.2 REQUIRED)
#FIND_PACKAGE(MRPT REQUIRED base;bayes;obs;gui)

# here we specify the additional include directories for the project. These files come in additional include directories option of VC++
# project.
# either the variable values from package like ${PCL_INCLUDE_DIRS} or absolute paths as shown in second and third line may be used.
#include_directories(${PCL_INCLUDE_DIRS})
#include_directories("G:/Matlab/extern/include")
#include_directories("C:/Program Files/MobileRobots/Aria/include")
include_directories("/usr/include")
include_directories("/mingw/include/ncurses")
#include_directories("/usr/include/x86_64-linux-gnu")

# here we specify the additional library directories for the linker in the project. These files come in additional library directories
# option of VC++ project.
# either the variable values from package like ${PCL_LIBRARY_DIRS} or absolute paths as shown in second and third line may be used.
# An update, link_directories is being pulled out, you may use TARGET_LINK_LIBRARIES instead as shown below
#link_directories(${PCL_LIBRARY_DIRS})
#link_directories("G:/Matlab/extern/lib/win32/microsoft")
#link_directories("C:/Program Files/MobileRobots/Aria/lib")
#link_directories("/lib32")
#link_directories("/usr/lib/x86_64-linux-gnu")

# here we add definitions for any package if requred.
#add_definitions(${PCL_DEFINITIONS})

# The following line is very important.
# It specifies the executable name. Here the executable is the first parameter i.e. MyApp and a file MyApp.exe will be created on
# compilation in windows platform.
# Followed by the executable name come all your source and header files.
# All cpp fles will be clubbed into source folder and all .h files will be added to header files folder of the project.
#add_executable (Zank Local.cpp part.h grab.h interface.h test.cpp test.h)

SET(BIN_OUTPUT Zank)

add_executable (${BIN_OUTPUT} main.c functions.c)

# There may be some additional dependencies which you may have to specify for the project, which you may do as in following lines.
# Note that first parameter is the executable name.
target_link_libraries (${BIN_OUTPUT} ncurses)
#target_link_libraries (MyApp ${PCL_LIBRARIES} libeng.lib libmx.lib libmex.lib libmat.lib Aria.lib winmm.lib wsock32.lib)
# Add the required libraries for linking:
#TARGET_LINK_LIBRARIES(${sampleName}
#${MRPT_LIBS} # This is filled by FIND_PACKAGE(MRPT ...)
#"" # Optional extra libs...
#)
# End of CMakeLists.Txt file. Save it as a plain text file and the name should be exactly CMakeLists.Txt


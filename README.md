# PythonScriptingInterface
Simple interface to add Python modules to your Qt/C++ Project

## How to use
First Create one ore more modules. Then you can create objects(classes) described in those module

### Create Module 
1. Create
```
PythonBinding py;
py.init(<your module>,<path to module(optional)>);
```
2. Call Function 
```
py.callFunction("pythonFunction",{<Args>}); //eg. {PyLong_FromLong(3), PyLong_FromLong(5)}
```
3. Access Variables
It is recommended to use getter and setter functions to access global variables.


### Create Object
1. Create
```
PythonObject obj = py.createObject("pythonClass");
```
2. Call Function 
```
obj.callFunction("pythonFunction",{<Args>}); //eg. {PyLong_FromLong(3), PyLong_FromLong(5)}
```
3. Access Attributes 
```
obj.setAttribute(name,value) 	//eg. name="attr1" value="PyLong_FromLong(3)"
PySharedRef val=obj.getAttribute(name)		//eg. name="attr1"
```

### PySharedRef
If you want to secure a value from getting removed by the garbage collector use PyShrardRef.
The Object will be deleted after PySharedRef desctructor is called.




## Further Documentation 

There is a large Doxygen compatibel documentation with code snippets 
in the source code. Just create a doxygen documentation for this repo covering all source and header files.

# Dub (Doxygen based Ubiquitous Binder)

This is a tool to ease the creation of scripting language bindings for a C++ library.
It was initially developed to create the OpenCV bindings for Lua in Lubyk (http://lubyk.org).

The generator uses Doxygen to parse C++ headers.

Homepage: [lubyk/dub](http://lubyk.org/en/project311.html)

Please donate so we can free up some time to write good documentation...

[![Click here to lend your support to: Doxygen based Lua binder (Dub) and make a donation at www.pledgie.com !](https://www.pledgie.com/campaigns/17041.png?skin_name=chrome)](http://www.pledgie.com/campaigns/17041)


# Features

Currently, the parser supports:

* public methods
* public attributes read/write
* pseudo-attributes read/write by calling getter/setter methods.
* custom bindings (for methods and global functions).
* custom read/write attributes (with void *userdata helper, union handling)
* public class methods
* public static attributes read/write
* pointer to member (gc protected)
* cast(default)/copy/disable const attribute
* member pointer assignment (gc protected)
* natural casting from std::string to string type (can include '\0')
* class instantiation from templates through typedefs
* class alias through typedefs
* bindings for superclass
* automatic casting to base class
* default argument values
* overloaded functions with optimized method selection from arguments
* operator overloading (even operator[], operator() and operator+= and such)
* return value optimization (no copy)
* simple type garbage collection optimization (no __gc method)
* namespace
* nested classes
* class enums
* global enums
* build system
* group multiple bindings in a single library
* rewrite class or library names
* native Lua table wrapping setmetatable({super = obj}, Vect)
* callback from C++ with error handling in Lua (with self.error).
* error function captures current 'print' function and can be used with self._errfunc.
* fully tested
* custom method binding name

# TODO

* documentation

# Usage

Create an inspector that will inspect a list of headers given by 'INPUT' (a list
of files and directories. You need to have Doxygen installed

    local ins = dub.Inspector {
      INPUT    = 'foo/include',
      -- optional
      DOXYGEN_CMD = 'path/to/doxygen',
    }
  
Create bindings:

    local binder = dub.LuaBinder()
  
    binder:bind(ins, {
      output_directory = 'tmp',
    })
    
You should now have a 'cpp' file for each class in tmp.

Example to build a class called 'Vect':

    binder:build {
      work_dir = '.',
      output   = 'tmp/Vect.so',
      inputs   = {
        'tmp/dub/dub.cpp',
        'tmp/Vect.cpp',
        'fixtures/pointers/vect.cpp',
      },
      includes = {
        'tmp',
        'foo/include',
      },
    }     

You can now use your class:

    package.cpath = package.cpath .. 'tmp/?.so;'
    require 'Vect'
    local v = Vect(1,3)
    v.x = 4
    print(v.x)
    -- etc

Please read the tests for more detail until the documentation is updated.

# Things to know

The bindings are made to look as close as possible to the C++ versions. This means that constructors look like C++: Vect(1, 2). Behind the hood, this is resolved as a call to Vect.new(1,2). By storing the 'new' function in a local variable, you can remove this small overhead.

Lua bindings usage examples:

    -- Create a Car instance, Car.Noisy is a constant defined in a C++ enum.
    local car = Car('my car', Car.Noisy)
  
    -- Execute the C++ 'brandName' method.
    print(car:brandName())
  
    -- Set the name of the car (public C++ attribute, a std::string here).
    car.name = 'my old car'
  
    -- Get the std::string name
    print(car.name)
  
    -- You can store \0 in strings
    car.name = 'my old car\0which I did not like'
  
    -- Create a vector
    local v1 = Vect(1,2)
    local v2 = Vect(4,5)
  
    -- Calls the overloaded operator+(). This is return value optimized to allocate a single Vect.
    local v3 = v1 + v2
  
    -- operator*(double d)
    v3 = v1 * 4
  
    -- cross product
    -- operator*(const Vect &v)
    print(v3 * Vect(1,2))



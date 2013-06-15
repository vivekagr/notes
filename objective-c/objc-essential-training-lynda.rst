Objective C Essential Training
==============================

Objective C is a strict super-set of C. Any C code is perfectly valid in Objective C.

Various functions have "NS" prefix which is present for historic reasons. "NS" prefix was adopted by "NeXT STEP" which developed the Foundation and AppKit libraries. Because Objective-C is an extension of C and thus doesn't have namespaces like in C++, symbols must be prefixed with a unique prefix so that they don't collide. This is particularly important for symbols defined in a framework.

Variable initialization is same as in C with the data type first, also the variable naming rules and like C, they can optionally be can be initialized to some value.

In Objective C, strings are prefixed with @ symbol which indicates to the compiler that it isn't normal C style string. E.g. ``@"I'm a string! Whooo!"``.

Conditional statements (including switch), logical, arithmetic & comparision operators, loops are same as in C.

There are a lot of pre-configured snippets in XCode under the Utilities panel (right bottom side) under the ``{ }`` tab.

Functions (declaration and definition) are exactly same as in C.

C's primitive data types are present in Objective C and also it's own data types like ``BOOL`` (with values of either ``YES`` or ``NO``), etc. Also there are class data types such as ``NSString`` and ``NSDate`` that are classes written in Obj C which are not same as the primitive ones.

``bool`` which is present in C99 is also present in Objective C but ``BOOL`` is preferred because there are many libraries that internally use ``BOOL`` and using ``bool`` can cause errors. ``BOOL`` is internally represented as a char.

For strings, Foundation library for Objective C has a ``NSString`` data type that is much better than using C style char array based strings. Example:

.. code-block:: objc

    NSString *message = @"Hello World";
    NSLog(@"The value of message is %@", message);

In the above code, ``message`` is a pointer to a ``NSString`` object that contains the string. ``%@`` is a placeholder for objects. When this placeholder is used, object's ``description`` method is called which should return ``NSString`` object.

In Objective C, all objects are accessed using pointers.

To call a method on an object, square bracket notation is used (#1). Passing an argument ``[myObject someMethod:arg]`` (#2). But a method that accepts multiple arguments is written weirdly (#3). Nested method calls can be done the way as shown at #4.

.. code-block:: objc

    [myObject someMethod]; // #1
    [myObject someMethod:arg]; // #2
    [myObject insertString: @"Hello" atIndex: 11]; // #3
    [myObject someMethod: [anotherObject anotherMethod]]; // #4

Regardng #3, where the method takes two arguments, the method name is split into the number of parameters it takes.

In Objective C documentation, "+" sign before a method means that it is a class method while "-" sign refers to it being an object method.

Object creation can be done in the following way -

.. code-block:: objc

    NSDate *myDate = [NSDate new];

What is happening here is that memory space enough for ``NSDate`` is being allocated, then it is initialized and its memory address is returned which is stored in ``myDate``. These are the two stages - allocation and initialization which can also done separately as shown below. When ``init`` method is called, it initializes the object by setting up the necessary internal values and other things that need to be done.

.. code-block:: objc

    NSDate *myDate = [NSDate alloc]; // will just allocate the space and return mem addr
    myDate = [myDate init]; // will initialize the variable

    // Above can be nested together as
    NSDate *myDate = [[NSDate alloc] init]; // most common way

So, why isn't the ``new`` method used instead of the double work we just did above? Thats because there isn't always just an ``init`` method but there are several init methods that are useful such as -

.. code-block:: objc

    Person *fred = [[Person alloc] initWithName: @"Fred Smith"];

The objects that were created this way will linger in the memory for until the end of program's execution. If any object is no longer required, then it can be released by calling release method on it. But the pointer will still have the address where the object existed. To remove that address, set its value to ``nil``.

.. code-block:: objc

    [myDate release];
    myDate = nil;

A ``retainCount`` is maintained for every object. When an object is created, its ``retainCount`` is 1. This retain count can be increased by calling ``retain`` method on the object. But every ``retainCount`` has to be matched with equal number of releases. So, if the ``retainCount`` is 3, then it has to be released 3 times to take it back down to zero.

There is however another option for releasing. ``autorelease`` method can be called on any function. When ``release`` method is called, it asks the system to reduce the retain count right then. But with ``autorelease``, the object is released later on. When ``autorelease`` is called, it adds an entry to ``autoreleasepool``. ``autoreleasepool`` is just a list of objects that need to have ``release`` called on them at some point later on. At some point later on in the program, when ``[pool drain];`` (pool is an ``NSAutoreleasePool`` object) is executed, every single object in the ``autoreleasepool`` is released.

For programs that run for longer, it is advised to drain the pool at the end of every event loop. Suppose a function creates an object and returns it. That object has to be released at some time. In the function itself, it cannot be released before returning it otherwise nothing would get returned. In that situation, ``autorelease`` can be called on it so that it will last long enough to be returned and when the pool is drain later in the future, it will be released as well. If the object user needs to keep that object for longer, then he can call retain on it and then its his responsibility to release it.

If any object is created with either of ``new``, ``alloc``, ``retain`` or ``copy`` (NARC), it has to released manually. For other objects that are created with class methods, they are already ``autorelease``d before they are returned. Be careful to not call ``release`` or ``autorelease`` on these objects.


Automatic Reference Counting
----------------------------

With ARC, there is no need to write the ``retain``, ``release`` or ``autorelease`` calls anymore. ARC is a compiler process which automatically determines when to retain or release the objects. ARC does not allow memory management code. ARC is not garbage collector.

Keep these in mind -

- Do not call any memory management methods.
- Do not use ``NSAutoreleasePool``. It has been replaced by ``@autoreleasepool`` block.
- No object references in C structs.


Creating Classes
----------------

There are two parts of class creation - interface (sort of prototype; in .h file) and implementation (in .m file). Class names should start with capital letters. All classes inherit from ``NSObject`` (base class).

Classes can be created in an XCode project by going to `New File` -> `Cocoa` -> `Objective-C class`.

Example of a class's interface (in the.h file).

.. code-block:: objc

    @interface Employee : NSObject

    @property NSString *name;
    @property NSDate *hireDate;
    @property int employeeNumber;

    // - sign denotes the method being an instance method
    // return type is mentioned in parentheses
    -(void) someMethod;

    @end

And the implementation part where methods need to be implemented.

.. code-block:: objc

    @implementation Employee

    @synthesize name, hireDate, employeeNumber;

    -(void) someMethod {
        NSLog(@"In the method");
    }

    @end

To use this class in the program, it's header file needs to be imported. For every property in the class Employee, a couple of methods are automatically created for us to manipulate them. Such as ``setName``, ``setHireDate`` and ``setEmployeeNumber``.

Declaring methods with parameters.

.. code-block:: objc

    // here input is a parameter of type NSString
    -(void) someMethod: (NSString *) input;

    // here is a method that accepts two parameters
    -(int) addNumber: (int) a  toNumber: (int) b;


While creating an object, properties can be also be defined the same way any variable is declared, like ``int score;`` but this member cannot be directly accessed from outside the object. Helper methods have to be written that do the manupulation of such members. But is tedious to write these accessor methods for every single member. So, here comes ``@property`` into the play which automates the creation of such accessor methods for us. In XCode 4.4+, ``@synthesize`` is no longer required.

In classes, properties (not the simple data types, but the objects) can also have attributes. For example -

.. code-block:: objc

    @property (strong) NSString *firstName;

In the above code, ``strong`` attribute indicates to the compiler that this property should be consider a strong reference to the ``firstName`` object. Its opposite property is ``weak`` which is not much used. Another property is ``readonly`` which, as it implies, makes the property read-only by not generating a setter method for it.

If there is a need to define any property that shouldn't be exposed, it can be done in the following way -

.. code-block:: objc

    @implementation
    {
        int somePrivateValue;
    }

    // method implementation...
    @end

This should be done in the implementation part and not the interface part. Since these members are not preceded by ``@property`` keyword, its accessor properties are not automatically generated so they are private. It is a good practice to keep these private members in a block.

Every object has a ``init`` method which is a part of ``NSObject`` base class. A custom ``init`` method can also be defined. Xcode's Code Snippet Library has the init method signature, so use it when necessary. Also, there can be multiple initlization methods in class and by convention, their names should start with ``init``.

When an object is destroyed, ``dealloc`` method present on it (which came from ``NSObject``) is called which deallocates it. A custom ``dealloc`` method can also be defined which can do the wrap-up stuff if needed. ``dealloc``'s method signature is also present in Xcode's Code Snippet Library. With ARC, you cannot call the ``dealloc`` method but you can still customize it so that it runs when called automatically by ARC.


Collections
-----------

C style arrays can be used in Objective-C both with primitive data types and objects.

Foundation framework also has an array object ``NSArray``.

.. code-block:: objc

    NSArray *myArray = [NSArray arrayWithObjects: @"one", @"two", @"three", nil];

    // and now to access an element

    NSLog(@"The second element is: %@", [myArray objectAtIndex: 1]);

``NSArray`` can have multiple data types or object classes within a same array. ``NSArray`` is immutable. Its size is fixed during its creation and it cannot be changed later on.

``NSMutableArray`` can be used whenever size flexibile array is required. It is a sub-class of ``NSArray`` and has methods to add and remove elements such as ``addObject`` and ``removeObject``.

``NSDictionary`` is present for creating key-value pair dicts.

.. code-block:: objc

    NSDictionary *states = [NSDictionary dictionaryWithObjectsAndKeys:
                            @"Arizona", @"AZ",
                            @"California", @"CA",
                            @"Colorado", @"CO",
                            nil];
    NSString *someState = @"CA";
    NSLog("%@ is for %@.", someState, [NSDictionary objectForKey: someState]);

``NSDictionary`` is also unmutable and there is a mutable variation for it called ``NSMutableDictionary`` which has methods to add and remove key-value pairs.

To enumerate over all the elements in an ``NSArray`` or the keys in ``NSDictionary``, ``for (NSString *i in myDict) { ... }`` can be used (assuming that elements/keys are of type ``NSString``).


To interact with files, use ``NSFileManager`` class. Rather than passing around file paths as strings, it is preferable to use ``NSURL`` object.

Objects can be saved to and retrieved back from files using ``NSKeyedArchiver`` and ``NSKeyedUnarchiver`` classes. For an object to be saved this way, its class has to have ``encodeWithEncoder`` method and for it to be read by, it has to have ``initWithCoder`` method.

.. code-block:: objc

    -(void) encodeWithCoder: (NSCoder *) coder {
        // here we are saving name and job properties
        // and they have to be given a unique identifier (keys)
        [coder encodeObject:name forKey:@"EmpName"];
        [coder encodeObject:job forKey:@"EmpJob"];
    }

    -(id) initWithCoder: (NSCoder *) coder {
        name = [coder decodeObjectForKey:@"EmpName"];
        job = [coder decodeObjectForKey:@"EmpJob"];
        return self;
    }


**Extending Classes with Categories**

Suppose you want to have a reverse method in ``NSString`` class. You can sub-class it and then add your function but there is a better way than that. Custom methods can be added to existing classes with the help of categories.

.. code-block:: objc

    // we are extending NSString class, no curly braces required
    @interface NSString (category)
    // no new instance variables
    // add methods
    @end


**Protocol** is a way to standardize interaction between objects not worrying about any formal relationshit. Just a few lines ago, when we wrote ``encodeWithCoder`` and ``initWithCoder`` methods, we conformed to the ``NSCoder`` protocol. ``NSKeyedArchiver`` and ``NSKeyedUnarchiver`` only care about the presence of those two functions in our object to be able to work with it. Sort of like duck typing. Protocol can be defined in the following way-

.. code-block:: objc

    @protocol Cleaner

    @required
    - (void) cleanFloors;
    - (void) vaccum;
    - (void) emptyTrash;

    @optional
    - (void) cleanWindows;

    @end

Conforming to protocols-

.. code-block:: objc

    @interface MyClass : NSObject <Cleaner>

    - (void) cleanFloors;
    - (void) vaccum;
    - (void) emptyTrash;

    @end

Existing protocols can be looked up in the documentation. Also, there is a template for protocols in Xcode.


**Dynamic Typing**

``id`` is a type in Objective-C which can represent any object is very commonly used in frameworks. ``alloc`` and ``init`` returns an ``id``. It is used in situations where the type of object is unknown. For example, if an array has objects of different data types and we want to enumerate over it. In that case, ``id`` can be used - ``for (id eachObject in myArray) { ... }``.

Beware though, Xcode and compiler cannot detect any error with ``id`` objects.

To check if an ``id`` object belongs to a certain class, it can be done as in #1 which is checking if ``eachObject`` is of class ``SomeClass``.

Also, if we want to check if an object has a certain method, it can be done as shown in #2 which is checking if ``eachObject`` class instance has a method ``someMethod``.

.. code-block:: objc

    if ([eachObject isKindOfClass:[SomeClass Class]]) { ... } // #1
    if ([eachObject respondsToSelector:@selector(someMethod)]) { ... } // #2


**Exception Handling**

.. code-block:: objc

    // this template is also present in Code Snippet Library
    @try { ... }
    @catch (NSException *e) { ... } // exception object is stored in e
    @finally { ... }

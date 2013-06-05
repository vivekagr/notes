More on Data Types
==================

:date: 2013-06-04



Enumerated Data Types
---------------------

An enumerated data type in C is one in which the permissible values of it can be specified during its definition.

.. code-block:: c

    // defining a enumerated data type primaryColor
    enum primaryColor { red, yellow, blue };
    // defining unnamed enumerated data type and declare variable color to be of that type
    enum { red, yellow, blue } color;

This defines a enumerated data type primaryColor which can be assigned with only the three values specified above and nothing else. A variable of type ``enum primaryColor`` can be declared as

.. code-block:: c

    enum primaryColor myColor, yourColor;
    myColor = red; // assigning value red to myColor
    if (myColor == green) // using it in expressions
        printf("green!\n");

The C compiler actually treats enumeration identifiers as integer constants. Beginning with the first name on the list, the compiler assigns sequential integer values to these names starting with 0. So, ``red`` is 0, ``yellow`` 1 and ``blue`` is 2 above.

Specific integer values can also be associated with the identifiers by mentioning them explicitly.

.. code-block:: c

    enum direction { up, down, left=10, right };
    // sequential values - up 1, down 2, left 10, right 11

Enumeration identifiers can also share same values.

.. code-block:: c

    enum switch { no=0, off=0, yes=1, on=1 };

Integer values can also be assigned explictly to enumerated data types with type casting.

.. code-block::c

    enum direction dir;
    dir = (enum direction) 11;


The typedef Statement
---------------------

The typedef statement can be used to assign alternate names to data types. It is handled by the compiler during compilation stage and it is different than preprocessors.

.. code-block:: c

    typedef int Counter;
    Counter i, j;

    typedef char Linebuf[81];
    Linebuf text; // same as below
    char text[81] // same as above

    typedef char *StringPtr;
    StringPtr buffer; // same as below
    char *buffer; // same as above

    typedef struct {
        float x;
        float y;
    } Point; // defining an unnamed struct under the alias `Point`
    Point origin = { 0.0, 0.0 }, currentPoint;

The first example above could also have been done using #define preprocessor as ``#define Counter int``. But the rest examples can't be done using preprocessor.

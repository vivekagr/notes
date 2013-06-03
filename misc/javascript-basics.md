# JavaScript Basics

- date: 2013-03-27
- tags: javascript, basics, notes

------------------------------------

The core language features of JavaScript are defined in ECMA-262 as a pseudolanguage named ECMAScript. ECMAScript contains all of the basic syntax, operators, data types, and objects necessary to complete basic computing tasks, though it provides no way to get input or to produce output. Understanding ECMAScript and its intricacies is vital to a complete understanding of JavaScript as implemented in web browsers.

**Data types**

- undefined - for undefined variables
- null - empty object pointer
- boolean - true or false
- string
- number
- object
- function

Variable initiliazation

    ::js
    var abc = "lola"; // creates local variable
    xyz = "loli;" // creates global variable (bad)

Type checking

    ::js
    typeof any_uninitialized_variable; // undefined
    
    var spam;
    typeof undefined; // undefined

undefined is unpredictable. You won't know if the variable has been just initialized or it hasn't.

* Don't set value of any variable to undefined explicitly.
* Any time an object is expected but is not available, null should be used in its place.

Because storing floating-point values uses twice as much memory as storing integer values, ECMAScript always looks for ways to convert values into integers.

    ::js
    var someNum = 22.0; // interpreted as integer 22

There is a special numeric value called **NaN**, short for Not a Number, which is used to indicate when an operation intended to return a number has failed (as opposed to throwing an error).

* Dividing a number by 0 gives NaN.
* Any operation involving NaN returns NaN.

NaN's peculiar behavior.

    ::js
    NaN == NaN; // returns false

Use isNaN(); function to check for NaN.

    ::js
    isNaN("11"); // false - can be converted to 11
    isNaN("lola"); // true - cannot be converted to a number
    isNaN(true); // false - can be converted to 1

**Numbers**

    ::js
    Number("100 Cats"); // NaN
    Number("100"); // 100
    Number(""); // 0
    Number(true); // 1
    Number("000010"); // 10 (leading 0s are ignored)

Because of the complexities and oddities of the Number() function when converting strings, the parseInt() function is usually a better option when you are dealing with integers.

    ::js
    parseInt("100 Cats 323"); // 100
    parseInt("Cats 100 203"); // NaN

If this first character isn’t a number, the minus sign, or the plus sign, parseInt() always returns NaN, which means the empty string returns NaN (unlike with Number(), which returns 0).

Radix can be passed as second argument to parseInt(). It is a good idea to pass the value (10 for decimals, 2 for binary, 8 for octal and 16 for hexadecimal) to avoid any errors.

**Strings**

Strings are immutable in ECMAScript like in Python. To change the string value held by a variable, it must be destroyed and replaced with the new one.

A value can be converted to string easily by adding "" to it.

    ::js
    9 + ""; // "9"

**Boolean**

Logical NOT can be performed with ! sign before the value.

Logical AND: &&

Logical OR: ||

    ::js
    null == undefined; //true
    "NaN" == NaN; //false
    5 == NaN; //false
    NaN == NaN; //false
    NaN =! NaN; //true
    false == 0; //true
    true == 1; //true
    true == 2; //false
    undefined == 0; //false
    null == 0; //false
    "5" == 5; //true
    "5" === 5; //false

=== does comparison without type conversion.

**Conditional Operator**

    ::js
    variable = boolean_expression ? true_value : false_value;
    var max = (num1 > num2) ? num1 : num2;

**if Statement**

    ::js
    if (condition) {
        statement1;
    } else if {
         statement2;
    } else {
         statement3;
    }

**do Statement**

    ::js
    do {
        statement;
    } while (expression);

**while Statement**

    ::js
    while (expression) {
        statement;
    }

**for Statement**

Nothing can be done with a for loop that can’t be done using a while loop. The for loop simply encapsulates the loop-related code into a single location.

    ::js
    for (initialization; expression; post-loop-expression) {
        statement;
    }

    for (var i=0; i<=5; i++) {
        alert(i);
    }

**for-in Statement**

    ::js
    for (property in expression) {
        statement;
    }

**Labeled Statement**

Statements can be labeled using following syntax. Mostly used in loops to break out the outer loop.

    ::js
    label: statement;

**with Statement**

The with statement sets the scope of the code within a particular object.

    ::js
    with (expression) {
        statement;
    }

Example:

    ::js
    var qs = location.search.substring(1);
    var hostName = location.hostname;
    var url = location.href;

can be rewritten as:

    ::js
    var qs = search.substring(1);
    var hostName = hostname;
    var url = href;

Note: It is widely considered a poor practice to use the with statement in production code because of its negative performance impact and the difficulty in debugging code contained in the with statement.

**switch Statement**

    ::js
    switch (expression) {
        case value/expression: statement;
        break;
        case value/expression: statement;
        break;
        default: statement;
    }

Each case in a switch statement says, “If the expression is equal to the value, execute the statement.” The break keyword causes code execution to jump out of the switch statement. Without the break keyword, code execution falls through the original case into the following one.

##Functions

    ::js
    function functionName(arg1, arg2,…, argN) {
        statements
    }

Function arguments in ECMAScript don’t behave in the same way as function arguments in most other languages. **An ECMAScript function doesn’t care how many arguments are passed in**, nor does it care about the data types of those arguments. Just because you define a function to accept two arguments doesn’t mean you can pass in only two arguments. You could pass in one or three or none, and the interpreter won’t complain. This happens because arguments in ECMAScript are represented as an array internally.

There is an arguments object that can be accessed inside a function which contains all the passed in arguments. Individual arguments can be accessed by using index notation.

All arguments in ECMAScript are passed by value. It is not possible to pass arguments by reference.

Functions that don't return any value explicitly actually return undefined.

**Primitive and Reference Values**

ECMAScript variables may contain two different types of data: primitive values and reference values.

**Primitive Values** - Simple atomic pieces of data. These are accessed by value. These are undefined, null, number, string and boolean.

**Reference Values** - Objects that may be made up of multiple values. JavaScript does not permit direct access of memory locations, so direct manipulation of the object’s memory space is not allowed. When you manipulate an object, **you’re really working on a reference to that object rather than the actual object itself**. For this reason, such values are said to be accessed by reference.

- When copying primitive values, stored value in one variable is hard copied to the other variable. They then have nothing to do with each other.
- Whereas when copying reference values, pointer from one variable is simply copied to the other variable, both of which point to the same object stored on the heap. Changes made to the object with access from any of the variable affects all the other ones.

Now, let's focus on argument passing. All function arguments in ECMAScript are passed by values. This means that the value outside of the function is copied into an argument on the inside of the function the same way a value is copied from one variable to another.

When the argument is passed by value, the value is copied into a local variable (a named argument is available and in arguments object). This happens in accordance to the rules mentioned above.

In case of reference values when passed in arguments, a local copy of the pointer is made but they both still point to the same object. Changes made to the object inside the function will reflect even outside of it.

It can be checked whether the variable contains primitive or reference value by using isinstanceof operator with following syntax.

    ::js
    result = variable isinstanceof constructor;

    person isinstanceof Object;
    colors isinstanceof Array;

All reference values, by definition, are instances of Object, so the instanceof operator always returns true when used with a reference value and the Object constructor. Similarly, if instanceof is used with a primitive value, it will always return false, because primitives aren’t objects.

**Execution Context and Scope**

There are mainly two execution context (or scope) which are at global and function level. Also the with statement and the catch block in try-catch statement have their own execution context.

If var is omitted while initializing a variable inside of a function, it is created in global context.


##Reference Types

A reference value (object) is an instance of a specific reference type. In ECMAScript, reference types are structures used to group data and functionality together and are often incorrectly called classes.

**Object Type**

Can be created in two ways:

    ::js
    var person = new Object();
    person.name = "lola";

    //or

    var person = {
        name: "lola";
    }

Object properties can be accessed using dot notation as well as using bracket notation.

    ::js
    person.name;
    person["name"]; // both are same

**Array Type**

ECMAScript arrays are dynamically sized. A same array can hold any data type in each slot. Can be created in following ways:

    ::js
    var colors = new Array("red", "green", "yellow");
    var colos = Array("red", "green", "yellow");
    var colors = ["red", "green", "yellow"];

Elements can be accessed using bracket notation. Arrays have length property with which the size of an array can be known. By setting the length property, you can easily remove items from or add items to the end of the array.

**Array Methods**


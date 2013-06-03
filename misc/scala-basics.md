# Scala Basics

- date: 2013-03-27
- tags: scala, basics

--------------------------------

Imperative Programming is about

- modifying mutable variables,
- using assignments
- and control structures such as if-then-else, loops, breaks, continue, return.

Pure imperative programming is limited by the “Von Neumann” bottleneck:

> One tends to conceptualize data structures word-by-word.

We need other techniques for deﬁning high-level abstractions such as collections, polynomials, geometric shapes, strings, documents.

A theory consists of one or more data types, operation on these data types and laws that describe the relationship between values and operations.

Normally, a theory doesn't describes mutations!

Functional Programming is about

- In a restricted sense, it means programming without mutable variables, assignments, loops and other imperative control stuctures.
- In a wider sense, functional programming means focusing on the functions to construct elegant programs.
- In particular, functions can be values that are produced, consumed and composed.
- Functions are first class citizens. They can be defined anywhere, including inside other functions.
- Functions like any other value, passed as parameter to functions and returned as results. As for other values, there exists a set operators to compose
functions.

Functional Programming is becoming increasingly popular because it oﬀers an attractive method for exploiting parallelism for multicore and cloud computing.

In a parallel environment, when multiple threads try to access and mutate a shared mutable state, problems arises. Though there are ways to solve it, it is not always easy and elegant as desired. In functional programming, by eliminating the use of mutable states these problems can be easily solved.

Functions can be defined as:

````scala
def square(x: Double) = x * x

def sumOfSquares(x: Double, y: Double) = square(x) + square(y)

/* Here, the return type is defined as well. */
def power(x: Double, y: Int): Double = ...
````

**Call by value (CBV)** - All the arguments are evaluated to a simple value and then passed on to the function body as soon as the function is ran.

Example:
	
````scala
def example(x: Int, y: Int) = x * x

example(2+3, 7)

/*
Evaluated as-
example(2+3, 7) -> example(5, 7) -> 5 * 5 -> 25
*/
````

**Call by name (CBN)** - All the arguments are passed to the function body as it is and evaluation is done by the code within the function body.

Example:

````scala
example(2+3, 7)

/*
 * Evaluated as-
 * example(2+3, 7) -> (2+3) * (2+3) -> 5 * (2+3) -> 5 * 5 -> 25
 */
````

If CBV evaluation of an expression *e* terminates, then CBN evaluation of *e* terminates too.

The other direction is not true.

Non-termination example

````scala
def first(x: Int, y: Int) = x

first(1, loop)

/*
 * Here, the loop resolves to itself infinitely.
 * 
 * Under CBN:
 * first(1, loop) -> 1
 * 
 * Under CBV:
 * first(1, loop) -> first(1, loop) -> first(1, loop)....
 */
````

Scala normally uses call-by-value.

But if the type of a function parameter starts with =>, it uses call-by-name.

````scala
def consOne(x: Int, y: => Int) = 1

/* Here, x is evaluated as CBV by default and y is evaluated as CBN which we explicitly forced it to. */
````

**Conditional Expressions**

if-else in Scala is used for expressions, not statements.

````scala
def abs(x: Int) = if (x >= 0) x else -x
````

Rewrite rules for Booleans (e is an arbitrary expression):

````scala
/* !true		--> false
 * !false		--> true
 * true && e 	--> e
 * false && e 	--> false
 * true || e 	--> true
 * false || e 	--> e
 */
````

**Value Definitions**

The `def` form is "by name", its right hand side evaluated on each use.

There is also a `val` for, which is "by value". Example-

````scala
val x = 2
val y = square(x)
````

The right hand side of a val definition is evaluated at the point of the definition itself.

Afterwards the name refers to the value. Here y refers to 4, not square(2).

**Difference between val and def**

The difference becomes apparent when the right hand side does not terminate.

````scala
/* This works fine. */
def loop: Boolean = loop
def x = loop

/* However, this will get stuck in an infinite loop since the interpreter tries to evaluate the loop right at the point of definition. */
val x = loop
````

&& and || implementation as functions-

````scala
def and(x: Boolean, y: => Boolean) = if (x) y else false
def or(x: Boolean, y: => Boolean) = if (!x) y else true
````

**Return type is required when calling a function recursively.**

**Blocks in Scala**

A block is defined by curly braces {....}.

````scala
{
	val x = f(3)
	x * x
}
````

It constains a sequence of definition or expressions.
The last element of a block is an expression that deﬁnes its value.
This return expression can be preceded by auxiliary deﬁnitions.
Blocks are themselves expressions; a block may appear everywhere an expression can.

- The deﬁnitions inside a block are only visible from within the block.
- The deﬁnitions inside a block shadow deﬁnitions of the same names outside the block.

**Semicolons**

In Scala, semicolons at the end of a line is optional in most cases. If there are more than one statements in one line, then they need to be separatd with a semi-colon.

**Semicolons and inﬁx operators**

One issue with Scala’s semicolon convention is how to write expressions that span several lines. For instance-

````scala
someLongExpression
+ someOtherExpression

/* would be interpreted as */

someLongExpression;
+ someOtherExpression
````

Two ways to overcome the problem.

````scala
/* Multiline expression can be written inside parentheses. */
(someLongExpression
	+ someOtherExpression)

/* Or operator can be written on the first line because this tells the Scala compiler that the expression is not yet finished. */
someLongExpression +
someOtherExpression
````

**Tail Recursion**

If a function calls itself as its last action, the function's stack frame can be reused. This is called tail recursion. Tail recursive functions are iterative processes.

In general, if the last action of a function consists of calling a function (which may be the same), one stack frame would be suﬃcient for both functions. Such calls are called tail-calls.

Example of non-tail recursive factorial function:

````scala
def factorial(x: Int): Int = 
	if (x == 0) 1
	else x * factorial(x-1)
````

Example of tail recursive factorial function:

````scala
def factorial(x: Int) = 
	def fac_loop(accum: Int, n: Int): Int = 
		if (n == 0) accum
		else fac_loop(accum * n, n - 1)
	loop(1, x)
````

In the first example, the return value `x * factorial(x-1)` has a pending calculation of x multiplied by factorial of (x-1) which would have to wait until that factorial has been computed and thus that recursive chain keeps on growing.

However, in the second example, for the return value `fac_loop(accum * n, n - 1)` the function calls itself and there are no pending computation to be done, so the further function calls can take place in the same stack frame without growing like crazy like in the previous example.
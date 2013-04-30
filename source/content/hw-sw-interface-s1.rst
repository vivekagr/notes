S1 - Memory, Data and Addressing
================================

:date: 2013-04-30
:tags: hwswint


Performance
-----------

Performance is not just about CPU clock speed. Data and instructions reside in the memory and they must be fetched to the CPU from memory to operate upon.

CPU<->Memory bandwidth can bottleneck performance. Two things can be done for this-
- Increase memory bandwidth so that more data can travel at a time. (DDR1 -> DDR2 -> DDR3)
- Move less data into/out of the CPU. This can be achieved by putting a small amount of memory on the CPU itself (which is called cache memory).


Binary Representations
----------------------

0s and 1s are represented by high and low voltage. It takes a little bit of time while changing the voltage and it is what limits the speed of the computing system. Electronics are designed to only care about the two specific voltages for 0 and 1 and not care about the voltages in between.


Representing information as bits and bytes
------------------------------------------

We're going to group our binary digits into groups of eight which are called **bytes**. The range can be-

``00000000``\ :sub:`2`\  - ``11111111``\ :sub:`2`\

In decimal, the above range can be expressed as-

``0``\ :sub:`10`\  - ``255``\ :sub:`10`\

But using binary form to represent data in our programs can get tedious so hexadecimal form is used. Each hexadecimal digit is 4 bit long. A byte can also be represented as two hexadecimal digits. The range can be-

``00``\ :sub:`16`\  - ``FF``\ :sub:`16`\  (which is also same as ``0``\ :sub:`10`\  - ``225``\ :sub:`10`\)

In C, ``FA1D37B``\ :sub:`16`\  can be represented as ``0xFA1D37B`` or ``0xfa1d37b``. This is an 8 digit hexadecimal number, so it is 8 x 4 bit = 32 bits or 4 bytes long number.


Byte Oriented Memory Organization
---------------------------------

Memory is organized in bytes. Basically it is a big long array of bytes. Each byte has an address.


Machine Words
-------------

Machine has a "word size".

Until recently, most machines used 32-bit (4-byte) words. It limited address to 4GB and it has become too small for memory intensive applications.

Now, most x86 systems use 64-bit (8-byte) words which has potential address space of 2\ :sup:`64`\  ~ 1.8 x 10\ :sup:`19`\  bytes (18EB - exabytes).

For backward compatibility, many CPUs support different word sizes of 16-bit, 8-bit, 4-bit, 2-bit and 1-bit.


Word Oriented Memory Organization
---------------------------------

Addresses specify location of bytes in memory and each byte has an address.

In 32-bit systems, 4 bytes have to be grouped together into a word. And 64-bit systems have 8 byte words. So, what address do we give to those word with multiple bytes?

To maintain uniformity, address of a word is said to be the address of its first byte. [Refer to the last slide in ``lecture_slides_01_012-memorg.pdf``]

Pointer is a data object that contains an address.


Byte Ordering
-------------

Say you want to store the 4-byte word ``0xaabbccdd``. In what order will the bytes be stored? There are two different conventions for that.

Big Endian and Little Endian. (Origin: Gulliver's Travels)

**Big Endian**: The most significant byte of the number goes the lowest address.

**Little Endian**: The least significant byte of the number goes the lowest address.

Example -

Variable has 4-byte representation ``0x01234567`` and address of variable is ``0x100``.

**Big Endian**

+-------+-------+-------+-------+
| 0x100 | 0x101 | 0x102 | 0x103 |
+-------+-------+-------+-------+
| 01    | 23    | 45    | 67    |
+-------+-------+-------+-------+

**Little Endian**

+-------+-------+-------+-------+
| 0x100 | 0x101 | 0x102 | 0x103 |
+-------+-------+-------+-------+
| 67    | 45    | 23    | 01    |
+-------+-------+-------+-------+

x86 architecture uses little endian convention.


Address and Pointers in C
-------------------------

Variable declaration: ``int x, y;``

The two variables will find two locations in memory in which to store 2 integers (1 word each).

Pointer declaration: ``int *ptr;``

Declares aa variable ``ptr`` that is a pointer to a data item that in an integer. This will store an address rather than a value.

Assignment to a pointer: ``ptr = &x;``

This assigns ptr to point to the address where x is located. ``&`` is used to get the address of a variable.

Get value pointed to by a pointer:

Dereference operator (``*``) is used to get the value pointed to by a pointer. ``*ptr`` will give us the value at the memory address given by the value of ``ptr``.

Examples

- If ``ptr = &x;`` then ``y = *ptr + 1`` is same as ``y = x + 1``.
- ``*(&y)`` is equivalent to ``y``.

We can do arithmetic on pointers.

``ptr = ptr + 1`` - Since type of ptr is int and an int uses 4 bytes, C automatically adds (1 x 4 =) 4. But this can be dangerous if we don't exactly know what is present at the next memory address.


Assignment in C
---------------

Left-Hand-Side = Right-Hand-Side

LHS must evaluate to a memory location (variable).

RHS must evaluate to a value (could be an address).

``int x, y; x = y + 3;`` - Get value at y, add 3, put it in x

``int *x; int y; x = &y + 3;`` - Get address of y, add (3 x 4 =) 12 to it, put it in x

``*x = y;`` - Here ``*`` says to the compiler not to use ``x`` itself as the variable rather get the value stored at x, interpret it as an address, put value of y at that address.





















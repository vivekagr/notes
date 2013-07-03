Mac OS X Shortcuts/Tips
=======================


Finder or Open/Save dialog
--------------------------

- ``⌘`` + ``I`` - Info window shows for the selected item.

- ``⌘`` + ``D`` - Selects the Desktop folder as a destination.

- ``⌘`` + ``.`` - Cancels and closes the dialog window.

- ``⌘`` + ``⇧`` + ``.`` - Show all hidden files/directories in open/save dialog.

- Typing ``/`` or ``~`` in an open/save dialog will also trigger the file path text field to appear.


Terminal
--------

**Copy and Paste**

- Copy a string: echo "ohai im in ur clipboardz" | pbcopy
- Copy the HTML of StackOverflow.com: curl "http://stackoverflow.com/" | pbcopy
- Open a new buffer in VIM, initialized to the content of the clipboard: pbpaste | vi -
- Save the contents of the clipboard directly to a file: pbpaste > newfile.txt

**Emacs Shortcuts**

- ``ctrl`` + ``A``: beginning of line.
- ``ctrl`` + ``E``: end of line.
- ``ctrl`` + ``U``: delete from cursor to beginning of line.
- ``ctrl`` + ``K``: delete from cursor to end of line.
- ``ctrl`` + ``W``: erase word to the left.
- ``ctrl`` + ``T``: transpose characters around cursor.

**open command**

- launch programs by exact path to the executable
- launch any program in the PATH directories by executable name
- open files in default applications ``open <file>``
- open files with other applications ``open -a <app-name> <file>``

More - ``man open``


Screenshots
-----------

- ``⌘`` + ``⇧`` + ``4`` + ``space`` - Take screenshot of just a single window and preserve the window drop shadow, with full alpha transparency.

- ``⌘`` + ``⇧`` + ``3`` - Capture entire screen and save as a file

- ``⌘`` + ``⇧`` + ``4`` - Capture dragged area and save as a file


Shutdown/Sleep
--------------

- ``ctrl`` + ``⌥`` + ``⌘`` + ``⏏`` - Shuts the computer down
- ``⌥`` + ``⌘`` + ``⏏`` - Sends computer to sleep
- ``⇧`` + ``ctrl`` + ``⏏`` - Send display only to sleep (great for locking your computer instantly)
- ``ctrl`` + ``⌘`` + ``⏏`` - Restarts the Mac
- ``⌥`` + ``⌘`` + ``esc`` - Lets you kill not responding programs (including the Finder)


General
-------

- While typing - Just press F5 to get the quickest suggestion of what you typing ( almost equivalent to spell check-suggestions ).

- Select a word/phrase, then ``ctrl`` + ``⌘`` + ``D`` to get the definition.

- ``⌥`` + ``Backspace`` - Delete the entire word before the cursor.

- ``ctrl`` + ``⇧`` + ``←``/``→`` - Select previous/next word.

- Change screen/keyboard brightness and sound in quarter values by holding ``⌥`` + ``⇧`` while using the corresponding function keys.

- Holding ``⌥`` while clicking menu bar icons (volume, network, bluetooth, battery) will give you additional menu items or alternate menus.

- While Command+Tabbing, if you hold down Option while letting go of Command at the end, you'll open a new window in the specified application if it currently doesn't have any open.

- Without the option key, Cmd-C/Cmd-V just copies and pastes. Cmd-C/Cmd+Opt-V cuts and pastes.

- Hold ``⌘`` to move around background windows without giving it focus.




Source:

- http://apple.stackexchange.com/questions/400/please-share-your-hidden-os-x-features-or-tips-and-tricks

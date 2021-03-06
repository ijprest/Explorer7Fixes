
# Explorer 7 Fixes

In Windows 7, Microsoft changed some things seemingly for the sake of 
change.  This project's goal is to fix some of these "problems" with 
Windows 7.

Currently, this project includes only one fix:

## No "Sort-Header" in Explorer

In Vista, Microsoft made the sort-header visible in _all_ view modes 
(not only the _Details_ view-mode, where it has always been present).
They removed this in Windows 7, and didn't leave a setting or registry 
key to bring it back.

For background on this problem, see: 

* [http://www.windows7taskforce.com/view/461](http://www.windows7taskforce.com/view/461)

## Installation

To install, simply run <tt>regsvr32.exe</tt> on the DLL appropriate for
your installation (either the 32- or 64-bit version).  e.g., one of:

* <tt>regsvr32 Release\Explorer7Fixes.dll</tt>
* <tt>regsvr32 x64\Release\Explorer7Fixes.dll</tt>

There is a batch file (<tt>install.bat</tt>) that largely automates this 
process.


## Uninstallation

To uninstall, simply run <tt>regsvr32.exe /u</tt> on the DLL you previously
registered.  e.g., one of:

* <tt>regsvr32 /u Release\Explorer7Fixes.dll</tt>
* <tt>regsvr32 /u x64\Release\Explorer7Fixes.dll</tt>

There is a batch file (<tt>uninstall.bat</tt>) that largely automates this 
process.

## Upgrading from a Previous Version

To upgrade:

* First uninstall the old version, following the process above.
* Because any running copies of Explorer will still have the DLL locked, you 
should then log out and log back on.
* Finally, install the new version.

## History

* v1.0.0.2 - Fixed an issue (#2) where BHO was being listed as an addon in IE.
* v1.0.0.1 - Fixed an issue (#1) where folder icon-size was being reset.
* v1.0.0.0 - First public release.

## Acknowledgements

* I would like to thank the [QTTabBar](http://qttabbar.sourceforge.net/) folks 
for discovering a mechanism to turn the sort-header back on.
* I would also like to thank the [ClassicShell](http://classicshell.sourceforge.net/)
project for their source-code, which served as the base for this project.
It has now been so heavily modified that it no longer much resembles
ClassicShell, but without that example/base from which to start, it would
have taken me much longer to get a working Browser-Helper Object (BHO) 
working.

## License

Explorer7Fixes is released under the [MIT License](http://www.opensource.org/licenses/mit-license.html):

Copyright (c) 2010 Ian Prest

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

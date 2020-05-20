AsmXml 1.4

Introduction
============
AsmXml is a very fast XML parser and decoder for x86 platforms.
It achieves high speed by using the following features:
  * Written in pure assembler
  * Optimized memory access
  * Parsing, validation and lookup at the same time. Lookup makes attributes 
    and elements accessibles in O(1) time.

To give an idea of the relative speed of AsmXml, the best open source 
XML parsers process between 10 and 30 MBs of XML per seconds while AsmXml 
processes around 200 MBs per seconds (tests performed on an Athlon XP 1800).

This library is also very small, it will increase the size of your 
application by only 20K.

This parser is intended for applications that need intensive processing of XML.
This project will likely appeal you if XML parsing is a bottleneck in your 
data-flow. 

License
=======
AsmXml is released under the BSD License.

Changes
=======
Version 1.4 - 2012-11-08
	- Bug fix: rare bug when allocating memory while reading an
	  attribute with a character reference
	  
Version 1.3 - 2010-10-06
	- Bug fix: crash when allocating memory while reading an
	  attribute with a character reference

Version 1.2 - 2009-10-18
	- Bug fix: unknown attribute could raise an error in non strict mode

Version 1.1 - 2008-10-13
	- Bug fix: cannot parse empty documents (<doc/>)
	- Bug fix: text was ignored after the root element 
	  (now it checks well-formedness)
	- Reads Processing Instructions (but ignores it)
	- Reads <!DOCTYPE > (but ignores it)

Version 1.0 - 2008-01-24
	- Version and encoding from XML declaration are accessibles
	- Bug fix: mixed content starting with a comment or CDATA

Version 0.7 - 2008-01-02
	- Non-strict mode ignores unknown elements
	- Bug fix: CDATA in ignored text is now correctly handled

Version 0.6 - 2007-11-29
	- Strict mode: option to ignore unknown attributes
	- Elements can be referenced
	- Bug fix: unexpected conflicts with elements
	- Bug fix: crash when not enough memory
	
Version 0.5 - 2007-11-05
	- Bug fix: when two attributes differs only by the last chars 
	- Bug fix: crash when too many groups defined
	- Bug fix: wrong definition in header file
	- Bug fix: reference can point to a wrong definition
	- All source files use unix end of line style (LF).
	- Added a small utility script (in Ruby) to generate a C++
	  header from a schema to help processing of parsed documents.

Version 0.4 - 2007-10-22
	- Bug fix: text element starting with a comment
	- Attributes and text elements can be ignored to speed up parsing and
	  to save memory
	- 'group' elements can contains attributes and text elements
	- report error when the parsing of a schema fails

Version 0.3 - 2007-05-30
	- Added supports of mixed content
	- Added <references> in schema
	- Added <includes> in schema
	- Elements can have ids for fast recognition
	- Mac OS X makefiles
	
Version 0.2 - 2007-02-12
	- Added access to all class objects
	- Detect an attribute name appearing twice in an element
	- Comments fully supported (mixed with text)
	- CDATA fully supported (mixed with text)

Version 0.1 - 2007-01-26
	- First release

Author
======
Marc Kerbiquet, 
mkerbiquet@users.sourceforge.net, 
http://mkerbiquet.free.fr/

Contributors
============
Damien Doiselet.


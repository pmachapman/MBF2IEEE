ARTICLE-ID:Q113439
TITLE     :PRB: Converting MBF to IEEE in Visual Basic for Windows

---------------------------------------------------------------------
The information in this article applies to:

- Microsoft Visual Basic programming system for Windows, version 3.0
---------------------------------------------------------------------

SYMPTOMS
========

Data files created with older Microsoft Basic products (Quick Basic,
GW-Basic, and Basica (IBM and Compaq licensed Basic)) may not be readable
by Visual Basic for Windows.

CAUSE
=====

Prior to the IEEE floating point standard being widely accepted, Microsoft
used an internal floating point format known as Microsoft Binary Format
(MBF). The IEEE standard was introduced later and became the industry
standard.

Early versions of Microsoft QuickBASIC and GW-Basic supported only MBF
format. Microsoft Basic Professional Development System (PDS) and Visual
Basic for MS-DOS has functions available to convert between MBF and IEEE
formats. As Microsoft moved toward complete acceptance of the IEEE
standard, however, support for the MBF format was removed.

Visual Basic for Windows uses the IEEE standard. The MBF format, however,
is incompatible with the IEEE standard and data saved in this manner will
not be readable.

WORKAROUND
==========

The PDS and Visual Basic for MS-DOS products contained functions that
convert between MBF format and IEEE format. These functions are not
available in Visual Basic for Windows. Here are two possible solutions to
this dilemma:

1. A program could be written in PDS or Visual Basic for MS-DOS that
   re-creates the file containing the MBF data. After reading the file
   information into PDS or Visual Basic for MS-DOS, you can use the
   MKxMBF$ functions (see the manuals for PDS or Visual Basic for
   MS-DOS or their Help menus) to convert the data to IEEE format.
   This method is preferred for two reasons:

    - It converts your data to IEEE so that other programs can access
      your files.

    - If you use method 2, your program will need an extra DLL that
      you must distribute with your application.

2. Previously, there was no way to convert the data from Visual Basic
   for Windows. But now there is a DLL available to do this. This DLL
   (MBF2IEEE.DLL) contains functions that simulate the MKS, MKD, CVS, and
   CVD functions that were present in some of the MS-DOS-based Basic
   products. These function (MKS, MKD, CVS, and CVD) do not exist in Visual
   Basic for Windows, thus the need for this DLL. The More Information
   section below gives details about the DLL and explains how to download
   it from the Microsoft Software Library.

STATUS
======

This behavior is by design.

MORE INFORMATION
================

Details About Method Two: Using MBF2IEEE.DLL
--------------------------------------------

NOTE: These functions all do conversions between Microsoft Binary Format
(MBF) and IEEE floating point values. Some of the newer MS-DOS-based Basic
products had versions of these functions that worked differently. For
example, they let you look at an IEEE number as a string without converting
it to MBF. The routines described here are only provided as a way of
retrieving old MBF data.

These function provide conversions between IEEE floating point values and
Microsoft Binary Format (MBF) floating point values. Below is a set of
declare statements which must be included in a Visual Basic program which
will call these functions:

   Declare Function Cvs Lib "MBF2IEEE.DLL" (X As String) As Single
   Declare Function Cvd Lib "MBF2IEEE.DLL" (X As String) As Double
   Declare Function Mks Lib "MBF2IEEE.DLL" (X As Single) As String
   Declare Function Mkd Lib "MBF2IEEE.DLL" (X As Double) As String

Below is a description of each of these functions along with an example.

CVS and CVD Functions
---------------------

These functions accept a 4-byte (CVS) or 8-byte (CVD) string as an
argument. They expect the bit pattern of this string to represent a single
or double precision MBF value, respectively. The function will return an
IEEE result.

   Dim MBF As String, IEEE As Single
   ' load the string from a file, etc.
   IEEE = CVS(MBF)

MKS and MKD Functions
---------------------

These functions accept an IEEE single (MKS), or double (MKD) precision
value as an argument. It will then convert this value into a 4- or 8-byte
MBF value and return it in a string.

   Dim MBF AS String, IEEE As Single
   MBF = MKS(IEEE)
   ' Now write the MBF value out to disk

Potential Problems
------------------

There are differences between the IEEE format and MBF. For this reason
precision may be lost during the translations. It is also possible that
a number will not be able to be converted between the two formats. If
this is the case, a Visual Basic Overflow (Error #6) will be generated.
This is a trappable error, so handle the error accordingly.

How to Get MBF2IEEE.DLL
-----------------------

Download MBF2IEEE.EXE, a self-extracting file, from the Microsoft Software
Library (MSL) on the following services:

 - CompuServe
      GO MSL
      Search for MBF2IEEE.EXE
      Display results and download

 - Microsoft Download Service (MSDL)
      Dial (206) 936-6735 to connect to MSDL
      Download MBF2IEEE.EXE

 - Internet (anonymous FTP)
      ftp ftp.microsoft.com
      Change to the \softlib\mslfiles directory
      Get MBF2IEEE.EXE

After downloading MBF2IEEE.EXE, run it to obtain MBF2IEEE.DLL along with
the source files and a MBF2IEEE.TXT file, which is a readme that contains
the text of this article.

Source Code Included in MBF2IEEE.EXE
------------------------------------

In addition to the .DLL itself, you will also find the source code for the
.DLL, so you can make modifications and recompile if you have Microsoft C.
To recompile and build a new .DLL file, you must use Microsoft C because
the routines are specific to Microsoft C and rely on the way Microsoft C
returns floating point values. It will not compile with Borland C.

To recompile with Microsoft C, use the following command line statements to
build the DLL:

    cl -ALw -Ow -W2 -Zp -Tp mbf2ieee.c
    link /nod c:\vb\cdk\vbapi.lib mbf2ieee, mbf2ieee.dll, NUL, sdllcew
       oldnames libw, mbf2ieee
    rc -t mbf2ieee.dll
    implib mbf2ieee.lib mbf2ieee.def

Additional reference words: BASCOM QBASIC GWBASIC BASICA 3.00 Softlib
KBCategory: APrg
KBSubcategory: APrgOther



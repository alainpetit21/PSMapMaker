PSMapMaker

Date : September 2006

Ahhh ... Phantasy Star 1 for the Sega Master system, such a wonderful game. BUt, was a freaking confusing maze the dungeons are! In order to fully enjoy this game I started creating a project that would track the Map making process by mimicing my moves on the joystick.

Build using MFC, it was using a little trick that I've discovered to "link" an HWND (basically any control in MFC to the output of a DirectDraw. This enable me to draw inside an MFC window


WHAT YOU NEED TO COMPILE :
- Microsoft Visual C++ 6.0
- Microsoft DXSDK_Aug09.exe from https://download.microsoft.com/download/4/C/F/4CFED5F5-B11C-4159-9ADC-E133B7E42E5C/DXSDK_Aug09.exe


Files ID :
*.dsw : Visual Studio 6 Workspace
*.dsp : Visual Studio 6 project
*.aps,.clw, opt, pl, rc, ncb : Debug and/or MFC stuff
archive/ : old stuff
res/ : MFC resources stuff
Data/ : a few maps for dungeons that I've started
Debug/ : a windows XP compiled version Debug
Release/ : a windows XP compiled version Release

MFC README Below
=================================
========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : PSMapMaker
========================================================================


AppWizard has created this PSMapMaker application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your PSMapMaker application.

PSMapMaker.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

PSMapMaker.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CPSMapMakerApp application class.

PSMapMaker.cpp
    This is the main application source file that contains the application
    class CPSMapMakerApp.

PSMapMaker.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

PSMapMaker.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\PSMapMaker.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file PSMapMaker.rc.

res\PSMapMaker.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.



/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in PSMapMaker.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

PSMapMakerDoc.h, PSMapMakerDoc.cpp - the document
    These files contain your CPSMapMakerDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CPSMapMakerDoc::Serialize).

PSMapMakerView.h, PSMapMakerView.cpp - the view of the document
    These files contain your CPSMapMakerView class.
    CPSMapMakerView objects are used to view CPSMapMakerDoc objects.



/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named PSMapMaker.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////

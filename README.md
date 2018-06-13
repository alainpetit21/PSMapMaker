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

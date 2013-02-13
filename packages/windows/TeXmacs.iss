; -- TeXmacs.iss --
; Inno Setup configuration file for the compilation of the 
; Windows TeXmacs installer

[Setup]
AppName=TeXmacs
AppVerName=Texmacs
DefaultDirName={pf}\TeXmacs
DefaultGroupName=TeXmacs
;denis begin
VersionInfoProductTextVersion=1.0.7.18
VersionInfoVersion=1.0.7.18
AppPublisher=MAGIX
AppPublisherURL=http://www.texmacs.org/
AppVersion=1.0.7.18
;denis end

UninstallDisplayIcon={app}\TeXmacs.ico
OutputDir=..\..\..\distr
OutputBaseFilename=TeXmacs-1.0.7.18-installer
; SourceDir=../..
ChangesAssociations=yes

WizardImageFile=TeXmacs-large.bmp
WizardImageStretch=no
WizardSmallImageFile=TeXmacs-small.bmp

;PrivilegesRequired=none

[Registry]
Root: HKCR; Subkey: ".tm"; ValueType: string; ValueName: ""; ValueData: "tmfile"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "tmfile"; ValueType: string; ValueName: ""; ValueData: "text/tm"; Flags: uninsdeletekey
Root: HKCR; Subkey: "tmfile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\TeXmacs.ico"
Root: HKCR; Subkey: "tmfile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\bin\texmacs.exe"" ""%1""" 

[Files]
Source: ..\..\..\distr\TeXmacs-Windows\*; DestDir: {app}; Flags: recursesubdirs createallsubdirs
Source: TeXmacs.ico; DestDir: {app}

[Icons]
Name: "{group}\TeXmacs"; Filename: "{app}\bin\texmacs.exe"; IconFilename: "{app}\TeXmacs.ico"
Name: "{group}\Uninstall TeXmacs"; Filename: "{uninstallexe}"
Name: "{commondesktop}\TeXmacs"; Filename: "{app}\bin\texmacs.exe"; IconFilename: "{app}\TeXmacs.ico"

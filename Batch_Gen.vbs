Rem Object variables
Rem=================
Dim objFilesys
Dim objFolder
Dim objShell
Dim writebatfile

Rem Variables to hold the paths
Rem============================
Dim selectedPath
Dim currentPath

Rem Common Variables
REm=================
Dim evfn(12)
Dim ta(12)
Dim mafn(12)

evfn(1)="Decision"
evfn(2)="Decision_1"
evfn(3)="Motion"
evfn(4)="Motion_effi"
evfn(5)="Joint1"
evfn(6)="Joint2"
evfn(7)="Homing"
evfn(8)="MotionController"
evfn(9)="MotionController_1"
evfn(10)="RobotArm"
evfn(11)="RobotArm_1"
evfn(12)="RobotArm_effi"

ta(1)="00:00:10:000"
ta(2)="00:00:10:000"
ta(3)="00:00:86:000"
ta(4)="00:01:40:000"
ta(5)="00:00:10:000"
ta(6)="00:00:10:000"
ta(7)="00:00:10:000"
ta(8)="00:00:10:000"
ta(9)="00:01:40:000"
ta(10)="00:00:10:000"
ta(11)="00:00:10:000"
ta(12)="00:01:40:000"

mafn(1)="Decision"
mafn(2)="Decision"
mafn(3)="Motion"
mafn(4)="Motion"
mafn(5)="Joint1"
mafn(6)="Joint2"
mafn(7)="Homing"
mafn(8)="MotionController"
mafn(9)="MotionController"
mafn(10)="RobotArm"
mafn(11)="RobotArm"
mafn(12)="RobotArm"

Set objShell = CreateObject( "Shell.Application" )
Set objFolder = objShell.BrowseForFolder( 0, "Select the folder path of the MA files", 0, 17)
if (objFolder Is Nothing) then wscript.quit
selectedPath=objFolder.Items.Item.Path

WScript.Echo "selectedPath= " & selectedPath


currentpath = WScript.ScriptFullName  'returns the path of the running script (with the file name) so we extract the folder path as follows:

'j=instrRev(currentpath, "\")
'currentpath = left(currentpath, j)
'wscript.echo "currentpath=" & currentpath


set objFilesys=CreateObject("Scripting.FileSystemObject")

FOR i=1 to 12

	maParam = " -m" & """" & mafn(i) & ".ma" & """" 
	eventParam = " -e" & """" & evfn(i) & ".ev" & """"	
	outParam = " -o" & """" & evfn(i) & "OUT.out" & """"
	logParam = " -l" & """" & evfn(i) & "LOG.log" & """"
	timeParam = " -t" & """" & ta(i) & """"

	simParam = maParam & eventParam & outParam & logParam & timeParam

	writebat1= "cd /D " & """" & selectedPath & """"
	writebat2= """" & selectedPath & "\simu.exe" & """" & simParam
				
	batfn = evfn(i) & ".bat"
	
	set writebatfile = objfilesys.OpenTextFile(batfn, 8, True)
 	
	writebatfile.writeline(writebat1)
	writebatfile.writeline(writebat2)
	set writebatfile = NOTHING

NEXT

set objFilesys = NOTHING
set objFolder = NOTHING
set objShell = NOTHING

wscript.quit







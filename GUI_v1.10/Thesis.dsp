# Microsoft Developer Studio Project File - Name="Thesis" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Thesis - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Thesis.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Thesis.mak" CFG="Thesis - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Thesis - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Thesis - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Thesis - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Thesis - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Thesis - Win32 Release"
# Name "Thesis - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AbstractGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimationDlgEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrayIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\ASAnimationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Association.cpp
# End Source File
# Begin Source File

SOURCE=.\Bezier.cpp
# End Source File
# Begin Source File

SOURCE=.\BinaryHeap.cpp
# End Source File
# Begin Source File

SOURCE=.\BObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonSSL.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\coloredvertex.cpp
# End Source File
# Begin Source File

SOURCE=.\Container.cpp
# End Source File
# Begin Source File

SOURCE=.\controlstruct.cpp
# End Source File
# Begin Source File

SOURCE=.\DelayTimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectedGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawTool.cpp
# End Source File
# Begin Source File

SOURCE=.\Edge.cpp
# End Source File
# Begin Source File

SOURCE=.\EdgeContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\EdgeContainerAsLists.cpp
# End Source File
# Begin Source File

SOURCE=.\EdgeContainerAsMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\EdgeTab.cpp
# End Source File
# Begin Source File

SOURCE=.\EdgeView.cpp
# End Source File
# Begin Source File

SOURCE=.\EditBar.cpp
# End Source File
# Begin Source File

SOURCE=.\EKAnimationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GMLPairList.cpp
# End Source File
# Begin Source File

SOURCE=.\GMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\GMLScanner.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphController.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphUtilities.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphView.cpp
# End Source File
# Begin Source File

SOURCE=.\InOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertingVisitor.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkedQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkedStack.cpp
# End Source File
# Begin Source File

SOURCE=.\ListIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MDITabs.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuEx.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkEdge.cpp
# End Source File
# Begin Source File

SOURCE=.\NewEdgeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewGraphDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewVertexDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NullIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\NullObject.cpp
# End Source File
# Begin Source File

SOURCE=.\OddButton.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Ownership.cpp
# End Source File
# Begin Source File

SOURCE=.\Partition.cpp
# End Source File
# Begin Source File

SOURCE=.\PartitionAsForest.cpp
# End Source File
# Begin Source File

SOURCE=.\PostOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\PreOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\PrePostVisitor.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesEDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesGDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesVDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizeGraphDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Shape.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StackAsArray.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabCtrlSSL.cpp
# End Source File
# Begin Source File

SOURCE=.\TabPageSSL.cpp
# End Source File
# Begin Source File

SOURCE=.\Thesis.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\Thesis.hpj

!IF  "$(CFG)" == "Thesis - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__THESI="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Release
TargetName=Thesis
InputPath=.\hlp\Thesis.hpj
InputName=Thesis

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Thesis - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__THESI="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=Thesis
InputPath=.\hlp\Thesis.hpj
InputName=Thesis

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Thesis.rc
# End Source File
# Begin Source File

SOURCE=.\ThesisDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ThesisView.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\UndirectedGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\Vector2D.cpp
# End Source File
# Begin Source File

SOURCE=.\Vertex.cpp
# End Source File
# Begin Source File

SOURCE=.\VertexTab.cpp
# End Source File
# Begin Source File

SOURCE=.\VertexView.cpp
# End Source File
# Begin Source File

SOURCE=.\Visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\WeightedEdge.cpp
# End Source File
# Begin Source File

SOURCE=.\WeightedNode.cpp
# End Source File
# Begin Source File

SOURCE=.\WeightedVertex.cpp
# End Source File
# Begin Source File

SOURCE=.\WrapperUtilities.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AbstractGraph.h
# End Source File
# Begin Source File

SOURCE=.\AlgorithmImpls.h
# End Source File
# Begin Source File

SOURCE=.\Algorithms.h
# End Source File
# Begin Source File

SOURCE=.\AnimationDlg.h
# End Source File
# Begin Source File

SOURCE=.\AnimationDlgEx.h
# End Source File
# Begin Source File

SOURCE=.\Array2D.h
# End Source File
# Begin Source File

SOURCE=.\ArrayIterator.h
# End Source File
# Begin Source File

SOURCE=.\ASAnimationDlg.h
# End Source File
# Begin Source File

SOURCE=.\Association.h
# End Source File
# Begin Source File

SOURCE=.\BArray.h
# End Source File
# Begin Source File

SOURCE=.\Bezier.h
# End Source File
# Begin Source File

SOURCE=.\BinaryHeap.h
# End Source File
# Begin Source File

SOURCE=.\BObject.h
# End Source File
# Begin Source File

SOURCE=.\ButtonSSL.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\coloredvertex.h
# End Source File
# Begin Source File

SOURCE=.\Container.h
# End Source File
# Begin Source File

SOURCE=.\controlstruct.h
# End Source File
# Begin Source File

SOURCE=.\Definitions.h
# End Source File
# Begin Source File

SOURCE=.\DelayTimeDlg.h
# End Source File
# Begin Source File

SOURCE=.\DialogEx.h
# End Source File
# Begin Source File

SOURCE=.\DirectedGraph.h
# End Source File
# Begin Source File

SOURCE=.\DrawTool.h
# End Source File
# Begin Source File

SOURCE=.\Edge.h
# End Source File
# Begin Source File

SOURCE=.\EdgeContainer.h
# End Source File
# Begin Source File

SOURCE=.\EdgeContainerAsLists.h
# End Source File
# Begin Source File

SOURCE=.\EdgeContainerAsMatrix.h
# End Source File
# Begin Source File

SOURCE=.\EdgeTab.h
# End Source File
# Begin Source File

SOURCE=.\EdgeView.h
# End Source File
# Begin Source File

SOURCE=.\EditBar.h
# End Source File
# Begin Source File

SOURCE=.\EKAnimationDlg.h
# End Source File
# Begin Source File

SOURCE=.\GenerateDlg.h
# End Source File
# Begin Source File

SOURCE=.\GMLPair.h
# End Source File
# Begin Source File

SOURCE=.\GMLPairList.h
# End Source File
# Begin Source File

SOURCE=.\GMLParser.h
# End Source File
# Begin Source File

SOURCE=.\GMLScanner.h
# End Source File
# Begin Source File

SOURCE=.\GraphBuilder.h
# End Source File
# Begin Source File

SOURCE=.\GraphController.h
# End Source File
# Begin Source File

SOURCE=.\GraphFactory.h
# End Source File
# Begin Source File

SOURCE=.\GraphGenerator.h
# End Source File
# Begin Source File

SOURCE=.\Graphics.h
# End Source File
# Begin Source File

SOURCE=.\GraphLayout.h
# End Source File
# Begin Source File

SOURCE=.\GraphLoader.h
# End Source File
# Begin Source File

SOURCE=.\GraphUtilities.h
# End Source File
# Begin Source File

SOURCE=.\GraphView.h
# End Source File
# Begin Source File

SOURCE=.\InOrder.h
# End Source File
# Begin Source File

SOURCE=.\InsertingVisitor.h
# End Source File
# Begin Source File

SOURCE=.\Iterator.h
# End Source File
# Begin Source File

SOURCE=.\LinkedList.h
# End Source File
# Begin Source File

SOURCE=.\LinkedQueue.h
# End Source File
# Begin Source File

SOURCE=.\LinkedStack.h
# End Source File
# Begin Source File

SOURCE=.\ListIterator.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MDITabs.h
# End Source File
# Begin Source File

SOURCE=.\MenuEx.h
# End Source File
# Begin Source File

SOURCE=.\Message.h
# End Source File
# Begin Source File

SOURCE=.\NetworkEdge.h
# End Source File
# Begin Source File

SOURCE=.\NewEdgeDlg.h
# End Source File
# Begin Source File

SOURCE=.\NewGraphDlg.h
# End Source File
# Begin Source File

SOURCE=.\NewVertexDlg.h
# End Source File
# Begin Source File

SOURCE=.\NullIterator.h
# End Source File
# Begin Source File

SOURCE=.\NullObject.h
# End Source File
# Begin Source File

SOURCE=.\OddButton.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\OutputDlg.h
# End Source File
# Begin Source File

SOURCE=.\Ownership.h
# End Source File
# Begin Source File

SOURCE=.\Partition.h
# End Source File
# Begin Source File

SOURCE=.\PartitionAsForest.h
# End Source File
# Begin Source File

SOURCE=.\PostOrder.h
# End Source File
# Begin Source File

SOURCE=.\PreOrder.h
# End Source File
# Begin Source File

SOURCE=.\PrePostVisitor.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesEDlg.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesGDlg.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesVDlg.h
# End Source File
# Begin Source File

SOURCE=.\Queue.h
# End Source File
# Begin Source File

SOURCE=.\ResizeGraphDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "Thesis - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=Thesis
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Thesis - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=Thesis
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\SearchableContainer.h
# End Source File
# Begin Source File

SOURCE=.\SearchDlg.h
# End Source File
# Begin Source File

SOURCE=.\Set.h
# End Source File
# Begin Source File

SOURCE=.\Shape.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\SortableLinkedList.h
# End Source File
# Begin Source File

SOURCE=.\Stack.h
# End Source File
# Begin Source File

SOURCE=.\StackAsArray.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabCtrlSSL.h
# End Source File
# Begin Source File

SOURCE=.\TabPageSSL.h
# End Source File
# Begin Source File

SOURCE=.\Thesis.h
# End Source File
# Begin Source File

SOURCE=.\ThesisDoc.h
# End Source File
# Begin Source File

SOURCE=.\ThesisView.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarWrapper.h
# End Source File
# Begin Source File

SOURCE=.\UndirectedGraph.h
# End Source File
# Begin Source File

SOURCE=.\Vector2D.h
# End Source File
# Begin Source File

SOURCE=.\Vertex.h
# End Source File
# Begin Source File

SOURCE=.\VertexTab.h
# End Source File
# Begin Source File

SOURCE=.\VertexView.h
# End Source File
# Begin Source File

SOURCE=.\Visitor.h
# End Source File
# Begin Source File

SOURCE=.\WeightedEdge.h
# End Source File
# Begin Source File

SOURCE=.\WeightedNode.h
# End Source File
# Begin Source File

SOURCE=.\WeightedVertex.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\WrapperUtilities.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\algorithm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\algorithms.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edge.cur
# End Source File
# Begin Source File

SOURCE=.\res\edit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\email.bmp
# End Source File
# Begin Source File

SOURCE=.\res\graph.bmp
# End Source File
# Begin Source File

SOURCE=.\res\network.bmp
# End Source File
# Begin Source File

SOURCE=.\res\next.bmp
# End Source File
# Begin Source File

SOURCE=.\res\np_completes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prev.bmp
# End Source File
# Begin Source File

SOURCE=.\res\remove.cur
# End Source File
# Begin Source File

SOURCE=.\res\Thesis.ico
# End Source File
# Begin Source File

SOURCE=.\res\Thesis.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ThesisDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\utilities.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vertex.cur
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Thesis.cnt

!IF  "$(CFG)" == "Thesis - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\Thesis.cnt
InputName=Thesis

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "Thesis - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\Thesis.cnt
InputName=Thesis

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Thesis.reg
# End Source File
# End Target
# End Project

# Microsoft Developer Studio Project File - Name="Thesis" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

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
!MESSAGE "Thesis - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Thesis - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Thesis - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Thesis - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

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

SOURCE=.\ArrayIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\Association.cpp
# End Source File
# Begin Source File

SOURCE=.\BinaryHeap.cpp
# End Source File
# Begin Source File

SOURCE=.\BObject.cpp
# End Source File
# Begin Source File

SOURCE=.\coloredvertex.cpp
# End Source File
# Begin Source File

SOURCE=.\Container.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectedGraph.cpp
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

SOURCE=.\EuclideanHeuristic.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphUtilities.cpp
# End Source File
# Begin Source File

SOURCE=.\InOrder.cpp
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

SOURCE=.\NetworkEdge.cpp
# End Source File
# Begin Source File

SOURCE=.\NullIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\NullObject.cpp
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

SOURCE=.\PrintingVisitor.cpp
# End Source File
# Begin Source File

SOURCE=.\StackAsArray.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Thesis.cpp
# End Source File
# Begin Source File

SOURCE=.\Thesis.rc
# End Source File
# Begin Source File

SOURCE=.\UndirectedGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\Vertex.cpp
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

SOURCE=.\Array2D.h
# End Source File
# Begin Source File

SOURCE=.\ArrayIterator.h
# End Source File
# Begin Source File

SOURCE=.\Association.h
# End Source File
# Begin Source File

SOURCE=.\AstarHeuristic.h
# End Source File
# Begin Source File

SOURCE=.\BArray.h
# End Source File
# Begin Source File

SOURCE=.\BinaryHeap.h
# End Source File
# Begin Source File

SOURCE=.\BObject.h
# End Source File
# Begin Source File

SOURCE=.\coloredvertex.h
# End Source File
# Begin Source File

SOURCE=.\Container.h
# End Source File
# Begin Source File

SOURCE=.\Definitions.h
# End Source File
# Begin Source File

SOURCE=.\DirectedGraph.h
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

SOURCE=.\EuclideanHeuristic.h
# End Source File
# Begin Source File

SOURCE=.\GraphBuilder.h
# End Source File
# Begin Source File

SOURCE=.\GraphFactory.h
# End Source File
# Begin Source File

SOURCE=.\GraphUtilities.h
# End Source File
# Begin Source File

SOURCE=.\InOrder.h
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

SOURCE=.\NetworkEdge.h
# End Source File
# Begin Source File

SOURCE=.\NullIterator.h
# End Source File
# Begin Source File

SOURCE=.\NullObject.h
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

SOURCE=.\PrintingVisitor.h
# End Source File
# Begin Source File

SOURCE=.\Queue.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchableContainer.h
# End Source File
# Begin Source File

SOURCE=.\Set.h
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

SOURCE=.\Thesis.h
# End Source File
# Begin Source File

SOURCE=.\UndirectedGraph.h
# End Source File
# Begin Source File

SOURCE=.\Vertex.h
# End Source File
# Begin Source File

SOURCE=.\VertexIterator.h
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
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

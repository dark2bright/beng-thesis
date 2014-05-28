#if !defined(AFX_DEFINITIONS_H__8E72C151_D437_4FD9_9EA2_8E428664C299__INCLUDED_)
#define AFX_DEFINITIONS_H__8E72C151_D437_4FD9_9EA2_8E428664C299__INCLUDED_

// Math definition
#define sqr(X)					X*X
// Object ID definition
#define NULLOBJECTID			1
#define ASSOCIATIONID			2
#define VERTEXID				3
#define EDGEID					4
#define WEIGHTEDEDGEID			5
#define WEIGHTEDVERTEXID		6
#define LINKEDQUEUEID			7
#define EDGECONTAINERASLISTSID	8
#define EDGECONTAINERASMATRIXID	9
#define DIRECTEDGRAPHID			10
#define UNDIRECTEDGRAPHID		11
#define WRAPPERID				12
#define BINARYHEAPID			13
#define ASSOCID					14
#define VERTEXVIEWID			15
#define EDGEVIEWID				16
#define NETWORKEDGEID			17
#define COLOREDVERTEXPTRID		18
#define PARTITIONTREEID			19
#define PARTITIONASFORESTID		20
#define LINKEDSTACKID			21
#define STACKASARRAYID			22
// Rectangle definition
#define TOPLEFT					0
#define TOPRIGHT				1
#define BOTTOMLEFT				2
#define BOTTOMRIGHT				3
// Drawing definition
#define MIN_RADIUS				13
#define MAX_RADIUS				50
// Cusor type definiton
#define DO_NOTHING				0
#define DO_SELECT				1
#define DO_RESIZE_HORZ			2
#define DO_RESIZE_VERT			3
#define DO_RESIZE_NEWS			4
#define DO_DRAW_NEW				5
// Update mode of edge
#define DO_UPDATE				6
#define DO_LAYOUT				7	
// Bezier constants definition
#define NONE					-1
#define START					0
#define FIRST					1
#define SECOND					2
#define END						3
// Shape constants definition
#define TOP						0
#define BOTTOM					1
#define LEFT					2
#define RIGHT					3
// Weight type definition
#define None					0
#define Int						1
#define Float					2
// Network definiton
#define VALID					0
#define REDUCE_SOURCE			1
#define REDUCE_SINK				2
#define REDUCE_BOTH				3
#define INVALID					4
// GML definitions
#define INITIAL_SIZE 1024

typedef UINT NUMBER;

typedef enum {
    GML_KEY, GML_INT, GML_DOUBLE, GML_STRING, GML_L_BRACKET, 
		GML_R_BRACKET, GML_END, GML_LIST, GML_ERROR
} GML_value; 


typedef enum {
    GML_UNEXPECTED, GML_SYNTAX, GML_PREMATURE_EOF, GML_TOO_MANY_DIGITS,
		GML_OPEN_BRACKET, GML_TOO_MANY_BRACKETS, GML_OK
} GML_error_value;

#endif //defined(AFX_DEFINITIONS_H__8E72C151_D437_4FD9_9EA2_8E428664C299__INCLUDED_)
// CGMLParser.cpp: implementation of the CGMLParser class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "GMLParser.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGMLParser::CGMLParser(const char*fileName)
{
	source = fopen (fileName, "r");
	if (source == 0) {
		AfxMessageBox("No such file:");
		isDone = true;
		return;
	}
	// Reach here ==> open file success
	isDone = FALSE;
	stat=(GML_stat*)malloc(sizeof(GML_stat));
	stat->key_list = NULL;
}

CGMLParser::~CGMLParser()
{
	purge();
	free(stat);
}

void CGMLParser::purge()
{
	GML_list_elem* keys = stat->key_list;
    GML_list_elem* tmp_key;
    while (keys) {
		free (keys->key);
		tmp_key = keys->next;
		free (keys);
		keys = tmp_key;
    }
	freeList(list);
}
void CGMLParser::freeList(LPGMLPAIR aList)
{
	GMLPAIR* tmp = aList;
    while (aList) {
		
		switch (aList->kind) {
		case GML_LIST:
			freeList (aList->value.list);
			break;
			
		case GML_STRING:
			free (aList->value.string);
			break;
			
		default:
			break;
		}
		
		tmp = aList->next;
		free (aList);
		aList = tmp;
    }
}

LPGMLPAIR CGMLParser::parse(int open)
{
	GML_token token;
    GMLPAIR* pair,*aList;
    GMLPAIR* tmp = NULL;
    GML_list_elem* tmp_elem;
	
    assert (stat);
	
    pair = (GMLPAIR*) malloc (sizeof (GMLPAIR));
    aList = pair;
	
    for (;;) {
		token = scan(source);
		
		if (token.kind == GML_END) {
			if (open) {
				stat->err.err_num = GML_OPEN_BRACKET;
				stat->err.line = GML_line;
				stat->err.column = GML_column;
				free (pair);
				
				if (tmp == NULL) {
					return NULL;
				} else {
					tmp->next = NULL;
					return aList;
				}
			}
			
			break;
			
		} else if (token.kind == GML_R_BRACKET) {
			if (!open) {
				stat->err.err_num = GML_TOO_MANY_BRACKETS;
				stat->err.line = GML_line;
				stat->err.column = GML_column;
				free (pair);
				
				if (tmp == NULL) {
					return NULL;
				} else {
					tmp->next = NULL;
					return aList;
				}
			}
			
			break;
			
		} else if (token.kind == GML_ERROR) {
			stat->err.err_num = token.value.err.err_num;
			stat->err.line = token.value.err.line;
			stat->err.column = token.value.err.column;
			free (pair);
			
			if (tmp == NULL) {
				return NULL;
			} else {
				tmp->next = NULL;
				return aList;
			}
			
		} else if (token.kind != GML_KEY) {
			stat->err.err_num = GML_SYNTAX;
			stat->err.line = GML_line;
			stat->err.column = GML_column;
			free (pair);
			
			if (token.kind == GML_STRING) {
				free (token.value.string);
			}
			
			if (tmp == NULL) {
				return NULL;
			} else {
				tmp->next = NULL;
				return aList;
			}
		}
		
		if (!stat->key_list) {
			stat->key_list = (GML_list_elem*) 
				malloc (sizeof (GML_list_elem));
			stat->key_list->next = NULL;
			stat->key_list->key = token.value.string;
			pair->key = token.value.string;
			
		} else {
			tmp_elem = stat->key_list;
			
			while (tmp_elem) {
				if (!strcmp (tmp_elem->key, token.value.string)) {
					free (token.value.string);
					pair->key = tmp_elem->key;
					
					break;
				}
				
				tmp_elem = tmp_elem->next;
			}
			
			if (!tmp_elem) {
				tmp_elem = (GML_list_elem*)
					malloc (sizeof (GML_list_elem));
				tmp_elem->next = stat->key_list;
				stat->key_list = tmp_elem;
				tmp_elem->key = token.value.string;
				pair->key = token.value.string;
			}
		}
		
		token = scan(source);
		
		
		switch (token.kind) {
		case GML_INT:
			pair->kind = GML_INT;
			pair->value.integer = token.value.integer;
			break;
			
		case GML_DOUBLE:
			pair->kind = GML_DOUBLE;
			pair->value.floating = token.value.floating;
			break;
			
		case GML_STRING:
			pair->kind = GML_STRING;
			pair->value.string = token.value.string;
			break;
			
		case GML_L_BRACKET:
			pair->kind = GML_LIST;
			pair->value.list = parse(1);
			
			if (stat->err.err_num != GML_OK) {
				return aList;
			}
			
			break;
			
		case GML_ERROR:
			stat->err.err_num = token.value.err.err_num;
			stat->err.line = token.value.err.line;
			stat->err.column = token.value.err.column;
			free (pair);
			
			if (tmp == NULL) {
				return NULL;
			} else {
				tmp->next = NULL;
				return aList;
			}
			
		default:    
			stat->err.line = GML_line;
			stat->err.column = GML_column;
			stat->err.err_num = GML_SYNTAX;
			free (pair);
			
			if (tmp == NULL) {
				return NULL;
			} else {
				tmp->next = NULL;
				return aList;
			}
		}
		
		tmp = pair;
		pair = (GMLPAIR*) malloc (sizeof (GMLPAIR));
		tmp->next = pair;
    }
	
    stat->err.err_num = GML_OK;
    free (pair);
    
    if (tmp == NULL) {
		return NULL;
    } else {
		tmp->next = NULL;
		return aList;
    }
}

void CGMLParser::showLastError(CMessage*pMessage) const
{
	if (stat->err.err_num != GML_OK) {
		CString str;
		str.Format("An error occured while reading line %d column %d of %s:", stat->err.line, stat->err.column);
		pMessage->show(str);
		switch (stat->err.err_num) {
		case GML_UNEXPECTED:
			pMessage->show("UNEXPECTED CHARACTER");
			break;
			
		case GML_SYNTAX:
			pMessage->show ("SYNTAX ERROR"); 
			break;
			
		case GML_PREMATURE_EOF:
			pMessage->show ("PREMATURE EOF IN STRING");
			break;
			
		case GML_TOO_MANY_DIGITS:
			pMessage->show ("NUMBER WITH TOO MANY DIGITS");
			break;
			
		case GML_OPEN_BRACKET:
			pMessage->show ("OPEN BRACKETS LEFT AT EOF");
			break;
			
		case GML_TOO_MANY_BRACKETS:
			pMessage->show ("TOO MANY CLOSING BRACKETS");
			break;
			
		default:
			break;
		}
	} 
}

bool CGMLParser::parse()
{
	if (isDone) return FALSE;
	list = parse(0);
	fclose(source);
	isDone = true;
	return stat->err.err_num == GML_OK ;
}

void CGMLParser::showAllKeys(CMessage *pMessage)
{
	pMessage->show("Key used in this file :");
	GML_list_elem* pTmp = stat->key_list;
	while (pTmp) {
		CString str;
		str.Format("%s\n", pTmp->key);
		pMessage->show(str);
		pTmp = pTmp->next;
    }
}

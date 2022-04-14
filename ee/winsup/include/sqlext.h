#ifndef _SQLEXT_H
#define _SQLEXT_H
#include "sql.h"
#ifdef __cplusplus
extern "C" {
#endif
#define SQL_DEFAULT_PARAM (-5)
#define SQL_IGNORE (-6)
#define SQL_LEN_DATA_AT_EXEC_OFFSET (-100)
#define SQL_LEN_DATA_AT_EXEC(l) (-l+SQL_LEN_DATA_AT_EXEC_OFFSET)
#define SQL_ENTIRE_ROWSET 0
#define SQL_POSITION 0
#define SQL_REFRESH 1
#define SQL_UPDATE 2
#define SQL_DELETE 3
#define SQL_ADD 4
#define SQL_LOCK_NO_CHANGE 0
#define SQL_LOCK_EXCLUSIVE 1
#define SQL_LOCK_UNLOCK 2
#define SQL_POSITION_TO(s,r) SQLSetPos(s,r,SQL_POSITION,SQL_LOCK_NO_CHANGE)
#define SQL_LOCK_RECORD(s,i,l) SQLSetPos(s,r,SQL_POSITION,l)
#define SQL_REFRESH_RECORD(s,i,f) SQLSetPos(s,r,SQL_REFRESH,fLock)
#define SQL_UPDATE_RECORD(s,r) SQLSetPos(s,r,SQL_UPDATE,SQL_LOCK_NO_CHANGE)
#define SQL_DELETE_RECORD(s,r) SQLSetPos(s,r,SQL_DELETE,SQL_LOCK_NO_CHANGE)
#define SQL_ADD_RECORD(s,r) SQLSetPos(s,r,SQL_ADD,SQL_LOCK_NO_CHANGE)
#define SQL_DRIVER_NOPROMPT 0
#define SQL_DRIVER_COMPLETE 1
#define SQL_DRIVER_PROMPT 2
#define SQL_DRIVER_COMPLETE_REQUIRED 3
#define SQL_FETCH_LAST 3
#define SQL_FETCH_PRIOR 4
#define SQL_FETCH_ABSOLUTE 5
#define SQL_FETCH_RELATIVE 6
#define SQL_FETCH_BOOKMARK 8
#define SQL_ROW_SUCCESS 0
#define SQL_ROW_DELETED 1
#define SQL_ROW_UPDATED 2
#define SQL_ROW_NOROW 3
#define SQL_ROW_ADDED 4
#define SQL_ROW_ERROR 5
#define SQL_CASCADE 0
#define SQL_RESTRICT 1
#define SQL_SET_NULL 2
#define SQL_NO_ACTION 3
#define SQL_SET_DEFAULT 4
#define SQL_PARAM_TYPE_UNKNOWN 0
#define SQL_PARAM_INPUT 1
#define SQL_PARAM_INPUT_OUTPUT 2
#define SQL_RESULT_COL 3
#define SQL_PARAM_OUTPUT 4
#define SQL_RETURN_VALUE 5
#define SQL_PT_UNKNOWN 0
#define SQL_PT_PROCEDURE 1
#define SQL_PT_FUNCTION 2
#define SQL_PARAM_TYPE_DEFAULT SQL_PARAM_INPUT_OUTPUT
#define SQL_SETPARAM_VALUE_MAX (-1L)

SQLRETURN SQL_API SQLDriverConnect(SQLHDBC,SQLHWND,SQLCHAR,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLSMALLINT*,SQLUSMALLINT);
SQLRETURN SQL_API SQLBrowseConnect(SQLHDBC,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLSMALLINT*);
SQLRETURN SQL_API SQLColumnPrivileges(SQLHSTMT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT);
SQLRETURN SQL_API SQLDescribeParam(SQLHSTMT,SQLUSMALLINT,SQLSMALLINT*,SQLUINTEGER*,SQLSMALLINT*,SQLSMALLINT*);
SQLRETURN SQL_API SQLExtendedFetch(SQLHSTMT,SQLUSMALLINT,SQLINTEGER,SQLUINTEGER*,SQLUSMALLINT*);
SQLRETURN SQL_API SQLForeignKeys(SQLHSTMT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT);
SQLRETURN SQL_API SQLMoreResults(SQLHSTMT);
SQLRETURN SQL_API SQLNativeSql(SQLHDBC,SQLCHAR*,SQLINTEGER,SQLCHAR*,SQLINTEGER,SQLINTEGER*);
SQLRETURN SQL_API SQLNumParams(SQLHSTMT,SQLSMALLINT*);
SQLRETURN SQL_API SQLParamOptions(SQLHSTMT,SQLUINTEGER,SQLUINTEGER*);
SQLRETURN SQL_API SQLPrimaryKeys(SQLHSTMT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT);
SQLRETURN SQL_API SQLProcedureColumns(SQLHSTMT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT);
SQLRETURN SQL_API SQLProcedures(SQLHSTMT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT);
SQLRETURN SQL_API SQLSetPos(SQLHSTMT,SQLUSMALLINT,SQLUSMALLINT,SQLUSMALLINT);
SQLRETURN SQL_API SQLTablePrivileges(SQLHSTMT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT,SQLCHAR*,SQLSMALLINT);
SQLRETURN SQL_API SQLDrivers(SQLHENV,SQLUSMALLINT,SQLCHAR*,SQLSMALLINT,SQLSMALLINT*,SQLCHAR*,SQLSMALLINT,SQLSMALLINT*);
SQLRETURN SQL_API SQLBindParameter(SQLHSTMT,SQLUSMALLINT,SQLSMALLINT,SQLSMALLINT,SQLSMALLINT,SQLUINTEGER,SQLSMALLINT,SQLPOINTER,SQLINTEGER,SQLINTEGER*);
#ifdef __cplusplus
}
#endif
#endif

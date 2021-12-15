#if !defined(AFX_ERRMSG_H__BC064F47_40FC_45B6_AA67_2E6D2568E219__INCLUDED_)
#define AFX_ERRMSG_H__BC064F47_40FC_45B6_AA67_2E6D2568E219__INCLUDED_

#define IDS_CLIENT_NOT_SET				_SA("API client not set")
#define IDS_CLIENT_NOT_SUPPORTED		_SA("API client not supported")

#if defined(LINUX)
#define IDS_LOAD_LIBRARY_FAILS \
	_SA("%s\n\n") \
    _SA("DBMS API Library '%s' loading fails\n") \
    _SA("This library is a part of DBMS client installation, not SQLAPI++\n") \
    _SA("Make sure DBMS client is installed and\n") \
    _SA("this required library is available for dynamic loading\n\n") \
    _SA("Linux/Unix:\n") \
    _SA("1) The directories in the user's LD_LIBRARY_PATH environment variable\n") \
    _SA("2) The list of libraries cached in /etc/ld.so.cache\n") \
    _SA("3) /usr/lib, followed by /lib\n")
#endif	// defined(LINUX)

#if defined(WIN32)
#define IDS_LOAD_LIBRARY_FAILS \
	_SA("%s\n\n") \
    _SA("DBMS API Library '%s' loading fails\n") \
    _SA("This library is a part of DBMS client installation, not SQLAPI++\n") \
    _SA("Make sure DBMS client is installed and\n") \
    _SA("this required library is available for dynamic loading\n\n") \
    _SA("Win32:\n") \
    _SA("1) The directory from which the application loaded\n") \
    _SA("2) The current directory\n") \
    _SA("3) The Windows, Windows system or 32-bit Windows system directory\n") \
    _SA("4) The directories in the PATH environment variable\n")
#endif	// defined(WIN32)

#define IDS_GET_LIBRARY_VERSION_FAILS	_SA("API Library '%s' quering version fails")
#define IDS_CLIENT_VERSION_OLD			_SA("This version of client (%d.%d) is too old and not supported")
#define IDS_CLIENT_INIT_FAILS			_SA("API Library initialization fails")

#define IDS_BIND_VAR_NOT_FOUND			_SA("Bind variable/parameter '%s' not found")
#define IDS_FIELD_NOT_FOUND				_SA("Field '%s' not found")
#define IDS_UNKNOWN_DATA_TYPE			_SA("Unknown data type")
#define IDS_UNKNOWN_PARAMETER_TYPE		_SA("Unknown parameter data type ('%s')")
#define IDS_UNKNOWN_DIRECTION_TYPE		_SA("Unknown parameter direction type ('%s')")
#define IDS_UNKNOWN_COLUMN_TYPE			_SA("Unknown column data type ('%s')")

#define IDS_CONVERTION_FROM_STRING_TO_SHORT_ERROR	_SA("Can't convert form string '%s' to short")
#define IDS_CONVERTION_FROM_STRING_TO_LONG_ERROR	_SA("Can't convert from string '%s' to long")
#define IDS_CONVERTION_FROM_STRING_TO_DOUBLE_ERROR	_SA("Can't convert from string '%s' to double")
#define IDS_CONVERTION_FROM_STRING_TO_NUMERIC_ERROR	_SA("Can't convert from string '%s' to numeric")

#endif // !defined(AFX_ERRMSG_H__BC064F47_40FC_45B6_AA67_2E6D2568E219__INCLUDED_)

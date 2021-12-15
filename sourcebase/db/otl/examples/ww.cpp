#include <iostream>
using namespace std;
#include <stdio.h>

#define OTL_ODBC // Compile OTL 4.0/ODBC
// The following #define is required with MyODBC 3.51.11 and higher
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE
// #define OTL_ODBC_UNIX // uncomment this line if UnixODBC is used
#define OTL_BIGINT long long // Enabling G++ 64-bit integers

#include <otlv4.h> // include the OTL 4.0 header file

otl_connect db; // connect object

inline otl_stream& operator>>(otl_stream& s, int64_t& n)
{
  long long temp;
  s>>temp;
  n=temp;
}

inline otl_stream& operator<<(otl_stream& s, const int64_t& n)
{
  s<<static_cast<long long>(n);
}

void insert()
// insert rows into table
{ 
 otl_stream o(1, // buffer size
              "insert into test_tab values(:f1<bigint>,:f2<char[31]>)", 
                 // SQL statement
              db // connect object
             );
 char tmp[32];

 for(int64_t i=1;i<=10;++i){
  o<<i<<tmp;
 }
}

void select()
{ 
 otl_stream i(50, // buffer size
              "select * from test_tab where f1>=:f<bigint> and f1<=:ff<bigint>*2",
                 // SELECT statement
              db // connect object
             ); 
   // create select stream
 
 int64_t f1=0;
 char f2[31];

 i<<static_cast<int64_t>(8)
  <<static_cast<int64_t>(8); // assigning :f = 8; :ff = 8
   // SELECT automatically executes when all input variables are
   // assigned. First portion of output rows is fetched to the buffer

 while(!i.eof()){ // while not end-of-data
  i>>f1>>f2;
  cout<<"f1="<<f1<<", f2="<<f2<<endl;
 }

}

int main()
{
 otl_connect::otl_initialize(); // initialize ODBC environment
 try{

  db.rlogon("scott/tiger@mysql35"); // connect to ODBC

  otl_cursor::direct_exec
   (
    db,
    "drop table test_tab",
    otl_exception::disabled // disable OTL exceptions
   ); // drop table

  otl_cursor::direct_exec
   (
    db,
    "create table test_tab(f1 bigint, f2 varchar(30))"
    );  // create table

  insert(); // insert records into table
  select(); // select records from table

 }

 catch(otl_exception& p){ // intercept OTL exceptions
  cerr<<p.msg<<endl; // print out error message
  cerr<<p.stm_text<<endl; // print out SQL that caused the error
  cerr<<p.sqlstate<<endl; // print out SQLSTATE message
  cerr<<p.var_info<<endl; // print out the variable that caused the error
 }

 db.logoff(); // disconnect from Oracle

 return 0;

}

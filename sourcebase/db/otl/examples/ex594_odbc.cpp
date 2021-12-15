#include <iostream>
using namespace std;

#include <stdio.h>

#define OTL_ODBC_ENTERPRISEDB // Compile OTL 4.0/EnterpriseDB-ODBC
#define OTL_ODBC_ALTERNATE_RPC
// Uncomment the #define below when used in Linux / Unix
//#define OTL_ODBC_UNIX
#include <otlv4.h> // include the OTL 4.0 header file

otl_connect db; // connect object

void insert()
// insert rows into table
{ 
 otl_stream o(200, // buffer size
              "insert into test_tab values(:f1<int>,:f2<char[31]>)", 
                 // SQL statement
              db // connect object
             );
 char tmp[32];

 for(int i=1;i<=123;++i){
#if defined(_MSC_VER)
#if (_MSC_VER >= 1400) // VC++ 8.0 or higher
  sprintf_s(tmp,sizeof(tmp),"Name%d",i);
#else
  sprintf(tmp,"Name%d",i);
#endif
#else
  sprintf(tmp,"Name%d",i);
#endif
  o<<i<<tmp;
 }
 o.flush();

 cout<<"Rows inserted: "<<o.get_rpc()<<endl;

}

void delete_rows()
{ 
  long rpc=otl_cursor::direct_exec(db,"delete from test_tab where f1>=95");
  
  cout<<"Rows deleted: "<<rpc<<endl;
}

int main()
{
 otl_connect::otl_initialize(); // initialize ODBC environment
 try{

  db.rlogon("scott/tiger@edbsql"); // connect to EDB

  otl_cursor::direct_exec
   (
    db,
    "drop table test_tab",
    otl_exception::disabled // disable OTL exceptions
   ); // drop table

  otl_cursor::direct_exec
   (
    db,
    "create table test_tab(f1 number, f2 varchar2(30))"
    );  // create table

  insert(); // insert records into table
  delete_rows(); // select records from table

 }

 catch(otl_exception& p){ // intercept OTL exceptions
  cerr<<p.msg<<endl; // print out error message
  cerr<<p.stm_text<<endl; // print out SQL that caused the error
  cerr<<p.var_info<<endl; // print out the variable that caused the error
 }

 db.logoff(); // disconnect from EDB

 return 0;

}

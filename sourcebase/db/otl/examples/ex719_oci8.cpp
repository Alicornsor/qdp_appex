#include <iostream>
using namespace std;

#include <stdio.h>

#if !defined(OTL_ORA10G_R2)
#define OTL_ORA10G_R2 // Compile OTL 4.0/OCI10gR2
#endif
//#define OTL_ORA11G // Compile OTL 4.0/OCI11G
//#define OTL_ORA11G_R2 // Compile OTL 4.0/OCI11G_R2
#include <otlv4.h> // include the OTL 4.0 header file

otl_connect db; // connect object

void insert()
// insert rows into table
{ 
 otl_stream o(10, // buffer size
              "insert into test_tab values(:f1<int>,:f2<char[200001]>)",
                 // SQL statement
              db // connect object
             );
 char f2[200001];
 for(int i=1;i<=20;++i){
  for(int j=0;j<199999;++j)
   f2[j]='*';
  f2[199999]='?';
  f2[200000]=0;
  o<<i<<f2;
 }

}

void select()
{ 
 otl_stream i(10, // buffer size
              "select f1, f2 :#2<char[200001]> from test_tab "
// override f2's default data type "CLOB" with char[XXX] so that the bulk interface
// can be used efficiently
              "where f1>=:f11<int> and f1<=:f12<int>*2",
                 // SELECT statement
              db // connect object
             ); 
   // create select stream
 
 int f1=0;
 char f2[200001]={0};

 i<<4<<4; // assigning :f11 = 4, :f12 = 4
   // SELECT automatically executes when all input variables are
   // assigned. First portion of output rows is fetched to the buffer

 while(!i.eof()){ // while not end-of-data
  i>>f1>>f2;
  cout<<"f1="<<f1<<", f2="<<f2[0]<<f2[strlen(f2)-1]<<", len="<<strlen(f2)<<endl;
 }

}

int main()
{
 otl_connect::otl_initialize(); // initialize the database API environment
 try{

  db.rlogon("system/oracle@myora_tns"); // connect to Oracle

  otl_cursor::direct_exec
   (
    db,
    "drop table test_tab",
    otl_exception::disabled // disable OTL exceptions
   ); // drop table

  otl_cursor::direct_exec
   (
    db,
    "create table test_tab(f1 number, f2 clob)"
    );  // create table

  insert(); // insert records into table
  select(); // select records from table

 }

 catch(otl_exception& p){ // intercept OTL exceptions
  cerr<<p.msg<<endl; // print out error message
  cerr<<p.stm_text<<endl; // print out SQL that caused the error
  cerr<<p.var_info<<endl; // print out the variable that caused the error
 }

 db.logoff(); // disconnect from the database

 return 0;

}
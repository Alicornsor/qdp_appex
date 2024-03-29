#include <iostream>
#include <stdio.h>
using namespace std;

#define OTL_ORA9I // Compile OTL 4.0/OCI9i
//#define OTL_ORA10G // Compile OTL 4.0/OCI10g
//#define OTL_ORA10G_R2 // Compile OTL 4.0/OCI10R2
//#define OTL_ORA11G // Compile OTL 4.0/OCI11g
//#define OTL_ORA11G_R2 // Compile OTL 4.0/OCI11gR2


#include <otlv4.h> // include the OTL 4.0 header file


otl_connect db; // connect object

void insert(void)
// insert rows into table
{ 
 otl_stream o(10, // stream buffer size in logical rows.
              "insert into test_tab "
              "values(:f1<int>,:f2<char[31]>)",
                 // INSERT statement
              db // connect object
             );
  o<<1<<"Line1";
  o<<2<<"Line21";
  o.flush();
}

void merge(void)
// merge rows into table
{ 
 otl_stream o(10, // stream buffer size in logical rows.
              "merge into test_tab d "
              "using (select :f1<int> f1, :f2<char[31]> f2 from dual) s "
              "on (s.f1=d.f1) "
              "when matched then update set d.f2=s.f2||'--'||s.f1 "
              "when not matched then insert (d.f1, d.f2) values(s.f1,s.f2)",
                 // MERGE statement
              db // connect object
             );
  o<<2<<"Line22";
  o<<3<<"Line3";
  o.flush();
}


void select(void)
{ 
 otl_stream i(5, // stream buffer size in logical rows
              "select * from test_tab ",
                 // SELECT statement
              db // connect object
             ); 
// SELECT output columns
 int f1=0;
 char f2[31];

 while(!i.eof()){ // while not end-of-data
  i>>f1>>f2;
  cout<<"f1="<<f1<<", f2="<<f2<<endl;
 }
 
}


int main()
{
 otl_connect::otl_initialize(); // initialize OCI environment
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
    "create table test_tab (f1 int, f2 varchar(30))"
    );  // create table

  db<<"create unique index ind001 on test_tab(f1)";
     // create unique index

  insert(); // insert records into table
  merge(); // merge records into table
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

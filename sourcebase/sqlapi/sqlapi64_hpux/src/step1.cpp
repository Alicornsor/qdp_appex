#include <stdio.h>  // for printf
#include <stdlib.h>  // for printf
#include <SQLAPI.h> // main SQLAPI++ header
#include <sys/time.h>
#include <string.h>
#include <strings.h>

void gettime();
int main(int argc, char* argv[])
{
    SAConnection con; // connection object
    SACommand cmd;    // command object
    
    try
    {
	char  sDatabase[1024];
	char  sUsername[1024];
	char  sPassword[1024];
	strcpy(sDatabase,"sample");
	strcpy(sUsername,"db2inst1");
	strcpy(sPassword,"db2inst1");
fflush(stdout);
	con.setClient(SA_DB2_Client);
	con.Connect(sDatabase, sUsername, sPassword);
	con.setAutoCommit(SA_AutoCommitOff);

        cmd.setConnection(&con);

	
	char tmpstr[7];
	char name[25];

gettime();
        cmd.setCommandText( "update  project set projname=:1,prstdate=:3 where projno=:2");

	for (int i=0;i<atoi(argv[1]);i++)
	{
		sprintf(tmpstr,"%06d",i);	
		cmd.Param(2).setAsString() = tmpstr;
		sprintf(name,"zzzz%06d",i);
		cmd.Param(1).setAsString() = name;
		cmd.Param(3).setAsString() = "01/30/1990";


		cmd.Execute();

	}
	con.Commit();
gettime();
    }
    catch(SAException &x)
    {
        // SAConnection::Rollback()
        // can also throw an exception
        // (if a network error for example),
        // we will be ready
        try
        {
            // on error rollback changes
            con.Rollback();
        }
        catch(SAException &)
        {
        }
        // print error message
        printf("%s\n", (const char*)x.ErrText());
    }
    
    return 0;
}



void gettime()
{

	
	struct timeval timeout;
	gettimeofday(&timeout,0);

	printf("secs=%ld\n",timeout.tv_sec);
	printf("secs=%ld\n",timeout.tv_usec/1000);
	

}



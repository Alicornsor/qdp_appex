#include <stdio.h>  // for printf
#include <SQLAPI.h> // main SQLAPI++ header

int main(int/* argc*/, char* /* argv[]*/)
{
	SAConnection con;

	// print menu
	printf("1.\tOracle\n");
	printf("2.\tSQL Server\n");
	printf("3.\tDB2\n");
	printf("4.\tInformix\n");
	printf("5.\tSybase\n");
	printf("6.\tInterBase\n");
	printf("7.\tSQLBase\n");
	printf("8.\tMySQL\n");
	printf("9.\tPostrgeSQL\n");
	printf("0.\tODBC\n");

	int ch = getchar();
	try
	{
/*
		switch(ch)
		{
		case '1':
			con.setClient(SA_Oracle_Client);
			break;
		case '2':
			con.setClient(SA_SQLServer_Client);
			break;
		case '3':
			con.setClient(SA_DB2_Client);
			break;
		case '4':
			con.setClient(SA_Informix_Client);
			break;
		case '5':
			con.setClient(SA_Sybase_Client);
			break;
		case '6':
			con.setClient(SA_InterBase_Client);
			break;
		case '7':
			con.setClient(SA_SQLBase_Client);
			break;
		case '8':
			con.setClient(SA_MySQL_Client);
			break;
		case '9':
			con.setClient(SA_PostgreSQL_Client);
			break;
		case '0':
			con.setClient(SA_ODBC_Client);
			break;
		default:
			return 0;
		}


		long nVersionClient;
/*
		long nVersionClient = con.ClientVersion();
		if(nVersionClient)
		{
			short minor = (short)(nVersionClient & 0xFFFF);
			short major = (short)(nVersionClient >> 16);
		
			printf("Client version: %hd.%hd\n", major, minor);
		}
		else
		{
			printf("Client version: unknown before connection\n");
		}

*/
		con.setClient(SA_DB2_Client);
		printf("Database name (connection string):\t");
		char sDatabase[1024];
		scanf("%s", sDatabase);
		printf("User name:\t");
		char sUsername[1024];
		scanf("%s", sUsername);
		printf("Password:\t");
		char sPassword[1024];
		scanf("%s", sPassword);
printf("sDatabase=%s name=%s passwd=%s\n",sDatabase,sUsername, sPassword);

		strcpy(sDatabase,"sample");
                strcpy(sUsername,"db2inst1");
                strcpy(sPassword,"db2inst1");
printf("sDatabase=%s name=%s passwd=%s\n",sDatabase,sUsername, sPassword);

		con.Connect(sDatabase, sUsername, sPassword);

		long nVersionServer = con.ServerVersion();
		short minor = (short)(nVersionServer & 0xFFFF);
		short major = (short)(nVersionServer >> 16);
		printf("Server: %s\n", (const char*)con.ServerVersionString());
		printf("Server version: %hd.%hd\n", major, minor);
		
		if(!nVersionClient)
		{
			nVersionClient = con.ClientVersion();
			if(nVersionClient)
			{
				short minor = (short)(nVersionClient & 0xFFFF);
				short major = (short)(nVersionClient >> 16);
		
				printf("Client version: %hd.%hd\n", major, minor);
			}
			else
			{
				printf("Client version: unknown after connection\n");
			}
		}
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
		printf("Error text: %s\n", (const char*)x.ErrText());
	}

	return 0;
}

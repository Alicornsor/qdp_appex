!!function!!
#include <string>
#include <map>
#include <iostream>
#include <stdio.h>
using namespace std;

map<string,string>  entitymap;
string strResult;

void resetEntityMap()
{
	entitymap.clear();
}

char* getEntityTypeName(char *name)
{
	map<string,string>::iterator it = entitymap.find(string(name));
	if(it != entitymap.end())
	{
		strResult = (*it).second;
		return (char *)(*it).second.c_str();
	}
	return NULL;
}

string convertToReadOnly(const char *sz)
{
	char *szTemp = new char[strlen(sz)];
	string result = "CReadOnly";
	sprintf(szTemp,"%s",++sz);
	result += szTemp;
	delete szTemp;
	return result;
}

void getReadOnlyEntityTypeName(char* name)
{
	map<string,string>::iterator it = entitymap.find(string(name));
	if(it != entitymap.end())
	{
		strResult = convertToReadOnly((*it).second.c_str());
		return;
	}
	printf("Can not find type for field %s\n",name);
	exit(1);
	return;
}

void addEntity(char *name,char *szTypeName)
{
	entitymap[string(name)] = string(szTypeName);
}

bool isTypeNeedCast(char *type)
{
	if(strcmp(type,"char")== 0 || strcmp(type,"int") == 0)
		return false;
	return true;
}

void printType(char *type,char *name)
{
	cout <<"The Name is: " << name << endl; 
	cout << type <<endl;
}
!!endfunction!!

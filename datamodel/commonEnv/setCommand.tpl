!!function!!
#include <vector>
using namespace std;

typedef struct
{
	char *keyName;
	char *tableName;
	int setIsKey;
	int setNotNull;
}	TSetColumn;

typedef struct
{
	char *keyName;
	char *tableName;
	int setUnique;
	int setDelete;
}	TSetIndex;

vector<TSetColumn> setColumns;
vector<TSetIndex> setIndexes;

void startSetCommand(void)
{
	setColumns.clear();
	setIndexes.clear();
}

char *tryGetString(char *name)
{
	if (!valid_name(name))
	{
		return NULL;
	}
	return get_string(name);
}

int getSetting(char *name)
{
	char *value=tryGetString(name);
	
	if (value==NULL)
	{
		return 0;
	}
	if (!strcmp(value,"yes"))
	{
		return 1;
	}
	return -1;
}

void addSetCommand(void)
{
	char *name=get_string("name");
	
	if (!strcmp(name,"setColumn"))
	{
		TSetColumn setColumn;
		
		setColumn.keyName=tryGetString("columnName");
		setColumn.tableName=tryGetString("tableName");
		setColumn.setIsKey=getSetting("setIskey");
		setColumn.setNotNull=getSetting("setNotnull");
		
		setColumns.push_back(setColumn);
	}
	else if (!strcmp(name,"setIndex"))
	{
		TSetIndex setIndex;

		setIndex.keyName=tryGetString("indexName");
		setIndex.tableName=tryGetString("tableName");
		setIndex.setUnique=getSetting("setUnique");
		setIndex.setDelete=getSetting("setDelete");
		
		setIndexes.push_back(setIndex);
	}
	else
	{
		printf("unknown set command %s\n",name);
		exit(1);
	}
}

#define getItem(group,tableValue,keyValue,valueName)		\
	for (int i=0;i<group.size();i++)			\
	{							\
		if (!strcmp(group.at(i).keyName,keyValue))	\
		{						\
			if ((group.at(i).tableName==NULL)||!strcmp(group.at(i).tableName,tableValue))	\
			{					\
				if (group.at(i).valueName==1)	\
				{				\
					return 1;		\
				}				\
				if (group.at(i).valueName==-1)	\
				{				\
					return 0;		\
				}				\
				break;				\
			}					\
		}						\
	}

int isNotNull(char *tableName)
{
	char *columnName=get_string("name");
	
	getItem(setColumns,tableName,columnName,setNotNull);

	if (!strcmp(get_string("notnull"),"yes"))
	{
		return 1;
	}
	return 0;
}

int isKey(char *tableName)
{
	char *columnName=get_string("name");

	getItem(setColumns,tableName,columnName,setIsKey);

	if (!strcmp(get_string("iskey"),"yes"))
	{
		return 1;
	}
	return 0;
}

int isUnique(char *tableName)
{
	char *indexName=get_string("name");
	
	getItem(setIndexes,tableName,indexName,setUnique);

	if (!strcmp(get_string("unique"),"yes"))
	{
		return 1;
	}
	return 0;
}

int isDelete(char *tableName)
{
	char *indexName=get_string("name");
	
	getItem(setIndexes,tableName,indexName,setDelete);

	return 0;
}

!!endfunction!!

#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<string>
#include<cstring>
#include<ctime>
#include<io.h>
#include<direct.h>
#define BigPrime 2147483647
#define Length 22
#define FolderName "HashList\\"
class HASH
{
	private:
        int Amount;
		int FoundAnswer;
        char DataFound[Length];
        char DataRead[Length];
		time_t Start;
		time_t End;
	public:
		HASH();
		void Init();
		int Hashmap(char *x);
		void Insert(char *x);
		void Find();
		int GetFoundAnswer();
		int CountTime();
};
HASH::HASH()
{
	Amount=0;
	FoundAnswer=0;
	memset(DataFound,0,sizeof(char)*Length);
	memset(DataRead,0,sizeof(char)*Length);
	_rmdir(FolderName);
	_mkdir(FolderName);
}
void HASH::Init()
{
	printf("String to be found:");
    scanf("%s",&DataFound);
	time(&Start);
	FILE *DataIn;
	DataIn=fopen("V1.in","r");
	fscanf(DataIn,"%d",&Amount);
	for(int i=0;i<Amount;i++)
	{
		fscanf(DataIn,"%s",&DataRead);
		Insert(DataRead);
	}
	fclose(DataIn);
}
int HASH::Hashmap(char *x)
{
	int Seed=13;
	int Sol=0;
	while(*x)
		Sol=(Sol*Seed+(*x++))%BigPrime;
	return Sol%BigPrime;
}
void HASH::Insert(char *x)
{
	int HashAnswer;
	HashAnswer=Hashmap(x);
	char Name[Length],Compare[Length],Path[Length];
	memset(Name,0,sizeof(char)*Length);
	memset(Compare,0,sizeof(char)*Length);
	memset(Path,0,sizeof(char)*Length);
	_itoa(HashAnswer,Name,10);
	strcpy(Path,FolderName);
	bool Ismatch=0;
	strcat(Path,Name);
	while(_access(Path,0)==0)
	{
		FILE *CompareIn;
		char EndlStore='\0';
		CompareIn=fopen(Path,"r");
		while(fscanf(CompareIn,"%s",Compare)!=EOF)
		{
			fscanf(CompareIn,"%c",&EndlStore);
			if(strcmp(Compare,x)==0)
			{
				Ismatch=1;
				break;
			}
		}
		fclose(CompareIn);
		if(Ismatch==1)break;
		memset(Path,0,sizeof(char)*Length);
		strcpy(Path,FolderName);
		HashAnswer++;
		if(HashAnswer==BigPrime-1)HashAnswer=0;
		_itoa(HashAnswer,Name,10);
		strcat(Path,Name);
	}
	if(Ismatch==0)
	{
		freopen(Path,"a+",stdout);
		printf("%s\n",x);
		fclose(stdout);
	}
}
void HASH::Find()
{
	int HashAnswer;
	HashAnswer=Hashmap(DataFound);
	char Name[Length],Compare[Length],Path[Length];
	memset(Name,0,sizeof(char)*Length);
	memset(Compare,0,sizeof(char)*Length);
	memset(Path,0,sizeof(char)*Length);
	_itoa(HashAnswer,Name,10);
	strcpy(Path,FolderName);
	strcat(Path,Name);
	while(_access(Path,0)==0)
	{
		freopen(Path,"r",stdin);
		while(scanf("%s",Compare)!=EOF)
		{
			getchar();
			if(strcmp(Compare,DataFound)==0)
			{
				FoundAnswer=1;
				break;
			}
		}
		fclose(stdin);
		if(FoundAnswer==1)return;
		memset(Path,0,sizeof(char)*Length);
		strcpy(Path,FolderName);
		HashAnswer++;
		if(HashAnswer==BigPrime-1)HashAnswer=0;
		_itoa(HashAnswer,Name,10);
		strcat(Path,Name);
	}
	FoundAnswer=0;
	return;
}
int HASH::GetFoundAnswer()
{
	return FoundAnswer;
}
int HASH::CountTime()
{
	time(&End);
	return (int)difftime(End,Start);
}
int main()
{
    HASH Hash;
	Hash.Init();
	Hash.Find();
	freopen("V1.out","w",stdout);
	printf("Found bool:%d\n",Hash.GetFoundAnswer());
	printf("Difftime is:%d\n",Hash.CountTime());
	fclose(stdout);
	return 0;
}
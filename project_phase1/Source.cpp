#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/*const int T_S = 58;
class HashTableEntry {
   public:
      int k;
      string v;
      HashTableEntry(int k, string v) {
         this->k= k;
         this->v = v;
      }
};
class HashMapTable {
   private:
      HashTableEntry **t;
   public:
      HashMapTable() {
         t = new HashTableEntry * [T_S];
         for (int i = 0; i< T_S; i++) {
            t[i] = NULL;
         }
      }
      int HashFunc(int k) {
         return k % T_S;
      }
      void Insert(int k, string v) {
         int h = HashFunc(k);
         while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
         }
         if (t[h] != NULL)
            delete t[h];
         t[h] = new HashTableEntry(k, v);
      }
      string SearchKey(int k) {
         int h = HashFunc(k);
         while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
         }
         if (t[h] == NULL)
            return NULL;
         else
            return t[h]->v;
	  }
	  ~HashMapTable() {
         for (int i = 0; i < T_S; i++) {
            if (t[i] != NULL)
               delete t[i];
               delete[] t;
         }
      }
};
*/

//global Varibals
int AsciiArray[255];
int finalStates[500];
int sizeFinalStates=0;
int array[500][500];
int StartP,currentP,State;
int otherStates[500];
int sizeOtherStates=0;
char KeywordArray[500];
int keywordSize=0;
bool error;

//functions
void Fill_TwoD_Array()
{
	ifstream fin("Tabular_States.txt");
	if(fin.is_open()==false)
	{
		cout<<"file to read tabular not found";
	}
	else
	{
		int row,col;
		char s;
		fin>> row;
		fin>>s;
		fin >> col;
		for(int r=1;r<=row;r++)
		{
			for(int c=1;c<=col;c++)
			{
				
				fin>>array[r][c];
				if(c!=col)
				{
					fin>>s;
				}
			}
		}
	}
}
void Read_Ascii_Array()//int AsciiArray[]
{
	ifstream fin("Ascii.txt");
	//int AsciiArray[255];
	if(fin.is_open()==false)
	{
		cout<<"file to read Ascii not found";
	}
	else
	{
		for(int i=0;i<=32;i++)
		{
			AsciiArray[i]=-1;
		}
		for(int i=33;i<127;i++)
		{
			fin>>AsciiArray[i];
		}
	}
}
void Fill_finalStates()
{
	ifstream fin("finalStates.txt");
	if(fin.is_open()==false)
	{
		cout<<"finalState File not found to read";
	}
	else
	{
		while(!fin.eof())
		{
			fin>>finalStates[sizeFinalStates];
			sizeFinalStates++;
		}
	}
}
void Fill_otherStates()
{
	ifstream fin("otherStates.txt");
	if(fin.is_open()==false)
	{
		cout<<"finalState File not found to read";
	}
	else
	{
		while(!fin.eof())
		{
			fin>>otherStates[sizeOtherStates];
			sizeOtherStates++;
		}
	}
}
char Getchar(char Arr[])
{
	char s=Arr[currentP];
	currentP++;
	return s;
}
void copyString(char Arr[],char Arr2[])
{
	int count=0;
	int j=StartP;
	int res=currentP-StartP;
	for(int i=0;i<=res;i++)
	{
		Arr2[i]=Arr[j];
		j++;
		count++;
	}
	Arr2[count]='\0';
}
/*void FillKeyword()
{
	ifstream fin("keywords.txt");
	if(fin.is_open()==false)
	{
		cout<<"keywords File not found to read";
	}
	else
	{
		while(!fin.eof())
		{
			fin>>KeywordArray[keywordSize];
			keywordSize++;
		}
	}
}*/
bool IsKeyword(char temp[])
{
	ifstream fin("keywords.txt");
	if(fin.is_open()==false)
	{
		cout<<"keywords File not found to read";
	}
	else
	{
		while(!fin.eof())
		{
			fin>>KeywordArray;//[keywordSize];
			keywordSize++;
			if(strcmp(KeywordArray,temp)==0)
			{
				return true;
			}
		}
	}
			return false;
	/*for(int i=0;i<keywordSize;i++)
	{
		if(strcmp(KeywordArray,temp)==0)
		{
			return true;
		}
	}
	return false;*/
}
int IsNumber(char temp[])
{
	/*bool a;
	int res;
	int flag[4];
	for(int i=0;i<4;i++)
	{
		flag[i]=-1;
	}
	int form[2];
	for(int i=0;temp[i]!='\0';i++)
	{
		if(temp[i]>='0' && temp[i]<='9')
		{
			flag[0]=0;
			a=true;
		}
		else if(temp[i]=='.' && flag[0]==0)
		{
			flag[1]=1;
			a=true;
		}
		else if(temp[i]=='E' ||temp[i]=='e')
		{
			flag[2] =2;
			a=true;
		}
		else if(temp[i]=='+' && temp[i+1]!='\0')
		{
			flag[3]=3;
			a=true;
		}
	}
	if(flag[2]==2 && flag[0]!=0)
	{
		return false;
	}
	if(a!=true)
	{
		return false;
	}
	if(flag[2]==2 && flag[3]==3)
	{
		form[0]=1;
	}
	if(flag[0]==0 || flag[1]==1)
	{
		form[1]=2;
	}
	if(form[0]==1||(form[1]==2 && form[0]==2))
	{
		return true;
	}
	else
	{
		return false;
	}*/
	for(int i=0;temp[i]!='\0';i++)
	{
		if(temp[i]>='0' && temp[i]<='9')
		{
			return true;
		}
	}
	return false;

}
bool IsSpecialChar(char temp[])
{
	int i=0;
	//for(int i=0;temp[i]!='\0';i++)
	{
		if((temp[i]>='!' && temp[i]<='/')||
			(temp[i]>=':' && temp[i]<='@')||
			(temp[i]>='[' && temp[i]<='^')||
			(temp[i]>='{' && temp[i]<='}'))
		{
			return true;
		}
	}
	return false;
}
bool IsIdentifier(char temp[])
{
	if(temp[currentP]=='_' || (temp[currentP]>='0' && temp[currentP]<='9'))
	{
		return true;
	}
	else 
		return false;
}
void LexicalToken(char temp[],char tokenType[])
{
	ofstream fout("LexicalToken.txt",std::ios_base::app);
	if(fout.is_open()==false)
	{
		cout<<"file to read LexicalToken not found";
	}
	else
	{
		fout<<'<'<<temp<<','<<tokenType<<'>'<<endl;
	}
}
void ErrorFile(char temp[])
{
	ofstream fout("ERROR.txt",std::ios_base::app);
	if(fout.is_open()==false)
	{
		cout<<"file to read LexicalToken not found";
	}
	else
	{
		fout<<'<'<<temp<<','<<"Error"<<'>'<<endl;
	}
}
void CheckValidation(char Arr[])
{
		char temp[100]="\0";
		char input[10]="input";
		char output[10]="output";
		copyString(Arr,temp);
		if(error==true)
		{
			//copyString(Arr,temp);
			int in=strcmp(input,temp);
			int out=strcmp(output,temp);
			if(in==0)
			{
				if(Arr[currentP+1]=='-' && Arr[currentP+2]=='>')
				{
					currentP+=2;
					LexicalToken("input->","input->");
					cout<<"("<<"input->,input->"<<")"<<endl;
				}
			}
			else if(out==0)
			{
				if(Arr[currentP+1]=='<' && Arr[currentP+2]=='-')
				{
					currentP+=2;
					LexicalToken("output<-","output<-");
					cout<<"("<<"output<-,output<-"<<")"<<endl;
				}
			}
			else if(IsKeyword(temp)==true)
			{
				LexicalToken(temp,temp);
				cout<<"("<<temp<<","<<temp<<")"<<endl;
			}
			else
			{
				ErrorFile(temp);
				cout<<"("<<temp<<","<<"error"<<")"<<endl;
			}

		}
		else if(IsNumber(temp)==true)
		{
			LexicalToken(temp,"Num");
			cout<<"("<<temp<<","<<"Num"<<")"<<endl;
		}
		else if(IsSpecialChar(temp)==true)
		{
			LexicalToken(temp,temp);
			cout<<"("<<temp<<","<<temp<<")"<<endl;
		}
		else if(IsKeyword(temp)==true)
		{
			LexicalToken(temp,temp);
			cout<<"("<<temp<<","<<temp<<")"<<endl;
		}
		else if(IsIdentifier(temp)==true)
		{
			LexicalToken(temp,"ID");
			cout<<"("<<temp<<","<<"ID"<<")"<<endl;
		}
}
int IsFinalState(int State)
{
	for(int i=0;i<sizeFinalStates;i++)
	{
		if(State==finalStates[i])
		{
			return 1;
		}
	}
	for(int i=0;i<sizeOtherStates;i++)
	{
		if(State==otherStates[i])
		{
			return 0;
		}
	}
	return -1;
}
bool IsDotExsist(char Arr[])
{
	for(int i=StartP;i<currentP;i++)
	{
		if(Arr[i]=='.')
		{
			return true;
		}
	}
	return false;
}
void Tokenization(char Arr[],int size)
{
	int flag=0;
	State=1;
	StartP=0;
	currentP=0;
	while(true)//for(int i=0;i<=size*2;i++)//while(true)//do//while(Arr[currentP]!='\0')//for(int i=0;i<=size+2;i++)
	{
		error=false;
		char s=Getchar(Arr);
		int ascci_value=(int)s;
		if(ascci_value==32)
		{
			currentP-=2;
			CheckValidation(Arr);	
			State=1;
			currentP+=2;
			StartP=currentP;
		}
		/*else if((Arr[currentP-1]=='e' || Arr[currentP-1]=='E') && (Arr[currentP-2]>='0' && Arr[currentP-2]<='9') && State!=1)
		{
			if(IsDotExsist(Arr))
			{
				State=18;
			}
			else
			{
				error=true;
				currentP-=2;
				Write_Token(Arr);
				State=1;
				StartP=currentP+1;
				currentP=StartP;
			}
		}*/
		else
		{
			State=array[State][AsciiArray[ascci_value]];
			if(State==-1)
			{
				error=true;
				currentP-=2;
				CheckValidation(Arr);
				State=1;
				StartP=currentP+1;
				currentP=StartP;
			}
			if(IsFinalState(State)==0)
			{
				State=0;
				flag=0;//other
			}
			else if(IsFinalState(State)==1)
			{
				State=0;
				flag=1;//final
			}
			if(State==0)
			{
				if(flag==1)
				{
					currentP--;
					CheckValidation(Arr);
					if(Arr[currentP+1]=='\0')
					{
						break;
					}
				}
				else{
					currentP-=2;
					CheckValidation(Arr);
				}			
				State=1;
				StartP=currentP+1;
				currentP=StartP;
			}
		}
	}
}
void Read_Code_file()
{
	ifstream fin("code.txt");
	char Read_code[255];
	if(fin.is_open()==false)
	{
		cout<<"file to read code not found";
	}
	else
	{
		while(!fin.eof())
		{
			fin.getline(Read_code,255);
			Tokenization(Read_code,strlen(Read_code));		
		}
	}
}


int main()
{
	//int StateArray[500][500];
	//int AsciiArray[255];
	Fill_TwoD_Array();
	Read_Ascii_Array();
	Fill_otherStates();
	Fill_finalStates();
	//FillKeyword();
	Read_Code_file();
}

/*State=1;
	StartP=0;
	currentP=0;
	while(true)//for(int i=0;i<=size*2;i++)//while(true)//do//while(Arr[currentP]!='\0')//for(int i=0;i<=size+2;i++)
	{
		char s=Getchar(Arr);
		int ascci_value=(int)s;
		if(Arr[currentP-1]=='\0')
		{
			currentP-=2;
			Write_Token(Arr,AsciiArray[ascci_value]);
			break;
		}
		State=array[State][AsciiArray[ascci_value]];
		if(State==-1)
		{
			currentP-=2;
			Write_Token(Arr,AsciiArray[ascci_value]);
			State=1;
			StartP=currentP+1;
			currentP=StartP;
		}
		if(IsFinalState(State)==true)
		{
			State=0;
		}
		if(State==0)
		{
			if(Arr[currentP-1]!=';')
			{
				currentP-=2;
			}
			Write_Token(Arr,AsciiArray[ascci_value]);
			if(Arr[currentP-1]==';')
			{
				break;
			}
			State=1;
			StartP=currentP+1;
			currentP=StartP;
		}
	}*/
/*//wrongif(Arr[currentP]!='\0')
			{ 
				currentP=currentP-1;
			}
			if((currentP-1 == StartP)||((currentP-1)-StartP)==1)
			{
				currentP--;
			}
			else if(Arr[currentP-1]!=';')//else if
			{
				currentP-=2;
			}
			Write_Token(Arr,AsciiArray[ascci_value]);
			if(Arr[currentP-1]==';')
			{
				break;
			}
			State=1;
			StartP=currentP+1;
			currentP=StartP;
			if(Arr[currentP]==' ')
			{
				StartP++;
				currentP++;
			}*/
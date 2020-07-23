#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<regex>
using namespace std;

//-999 stack symobl
//-777 skip
//-888 pop
int lexical_input[20];
int lexical_input_index;
int Stack[30];
int currentPtrStack;
int CFG_rules[50][20];
int LLOneTable[24][26];
//char Display_Rules[30][50];

void GetInput(char input[])//store Inputs
{
	ifstream fin("input.txt");
	if(fin.is_open()==false)
	{
		cout<<"file to read tabular not found";
	}
	else
	{
		while(!fin.eof())
		{
			fin>>input;			
		}
		/*for(int i=0;i<strlen(input);i++)
		{
			cout<<input[i]<<endl;
		}*/
	}
	fin.close();
}
int Convert_LexicalType(char input[],int i)
{
	ifstream fin("numberLexicalType.txt");
	if(fin.is_open()==false)
	{
		cout<<"file to read tabular not found";
	}
	else
	{	
		char get[10];
		int num;
		int j=0;
		while(!fin.eof())
		{
			fin.getline(get,10,'.');
			regex newlines_re("\n+");
			auto result=std::regex_replace(get,newlines_re,"");
			fin>>num;
			//cout<<get<<" "<<num<<endl;
			if((input[i]=='i'&& result[j] =='i') && (input[i+1]=='d'&& result[j+1] =='d'))
			{
				i+=2;
				j=0;
				lexical_input[lexical_input_index]=num;
				lexical_input_index++;
				fin.close();
				return i;
			}
			else if((input[i]=='i'&& result[j] =='i')&&(input[i+1]=='f'&& result[j+1] =='f'))
			{
				i+=2;
				j=0;
				lexical_input[lexical_input_index]=num;
				lexical_input_index++;
				fin.close();
				return i;
			}
			else if(input[i]=='n'&& result[j] =='n')
			{
				i+=3;
				j=0;
				lexical_input[lexical_input_index]=num;
				lexical_input_index++;
				fin.close();
				return i;
			}
			else if((input[i]=='i'&& result[j] =='i')&&(input[i+1]=='n'&& result[j+1] =='n'))
			{
				i+=3;
				j=0;
				lexical_input[lexical_input_index]=num;
				lexical_input_index++;
				fin.close();
				return i;
			}
			else if(input[i]=='f'&& result[j] =='f')
			{
				i+=5;
				j=0;
				lexical_input[lexical_input_index]=num;
				lexical_input_index++;
				fin.close();
				return i;
			}
			else if(input[i]=='w'&& result[j] =='w')
			{
				i+=5;
				j=0;
				lexical_input[lexical_input_index]=num;
				lexical_input_index++;
				fin.close();
				return i;
			}
			else if(input[i]=='e'&& result[j] =='e')
			{
				i+=4;
				j=0;
				lexical_input[lexical_input_index]=num;
				lexical_input_index++;
				fin.close();
				return i;
			}
			else
				if(input[i]==result[j])
				{
					i++;
					j=0;
					lexical_input[lexical_input_index]=num;
					lexical_input_index++;
					fin.close();
					return i;
				}
		}
	}
}
void IsConverted(char input[])
{
	int i=0;
	while(true)
	{
		if(input[i]=='$')
		{
			//lexical_input_index++;
			lexical_input[lexical_input_index]=-999;
			break;//lexical_input_index;
		}
		else
		{
			i=Convert_LexicalType(input,i);
			
		}
	}
	/*for(int i=0;i<=lexical_input_index;i++)
	{
		cout<<lexical_input[i]<<" ";
	}*/
}
void Fill_CFG_Rules()
{
	ifstream fin("GrammerRule.txt");
	if(fin.is_open()==false)
	{
		cout<<"file to read tabular not found";
	}
	else
	{
		int r=1,c=0;
		char comma;
		while(!fin.eof())
		{
			fin>>CFG_rules[r][c];
			if(CFG_rules[r][c]==999)
			{
	//			cout<<CFG_rules[r][c]<<endl;
				r++;
				c=0;
				continue;
			}
			else
			{
	//			cout<<CFG_rules[r][c]<<' ';
				c++;
			}
			fin>>comma;
		}
	}
}
/*void Rules_Char_Store()
{
	ifstream fin("Rules.txt");
	if(fin.is_open()==false)
	{
		cout<<"file to read tabular not found";
	}
	else
	{
		for(int r=1;r<=24;r++)
			{
				for(int c=0;c<=50;c++)
				{
					if(Display_Rules[r][c]==9)
					{
						break;
					}
					fin>>Display_Rules[r][c];
			//		cout<<Display_Rules[r][c]<<' ';
				}
			// 	cout<<endl;
			}
		}
}*/
void Fill_LL1ParseTable()
{
	ifstream fin("LL1Parsing.txt");
	if(fin.is_open()==false)
	{
		cout<<"file to read tabular not found";
	}
	else
	{
			for(int r=1;r<=24;r++)
			{
				for(int c=1;c<=25;c++)
				{
					fin>>LLOneTable[r][c];
			//		cout<<LLOneTable[r][c]<<' ';
				}
			// 	cout<<endl;
			}
		}
	
}
int getInput(int i)
{
	return lexical_input[i];
}
int POP()
{
	int s=Stack[currentPtrStack];
	Stack[currentPtrStack]=0;
	currentPtrStack--;
	return s;
}
int	LengthGrammerRule(int index)
{
	int i=0;
	while(true)
	{
		if(CFG_rules[index][i]==999)
		{
			i--;
			return i;
		}
		else
		{
			i++;
		}
	}
}
void PrintStack()
{
	for(int i=0;i<=currentPtrStack;i++)
	{
		cout<<Stack[i]<<' ';
	}
	cout<<endl;
}
void Push(int length,int index)
{

	for(int i=length;i>=0;i--)
	{
		currentPtrStack++;
		Stack[currentPtrStack]=CFG_rules[index][i];
	}
	//cout<<endl;
}
void Parsing()
{
	int i=0;
	int in,top,row,indexLL1,length;
	in=getInput(i);
	top=POP();
	row=top*-1;
	PrintStack();
	while(true)
	{
 		if(in==top)
		{
			cout<<"match"<<endl;
			i++;
			in=getInput(i);
			PrintStack();
			top=POP();
			row=top*-1;
		}
		else if(top==0)
		{
			cout<<"null POP"<<endl;
			PrintStack();
			top=POP();
			row=top*-1;
		}
		else if(in==-999)
		{
			while(top!=-999)
			{
				top=POP();
				cout<<"POP"<<endl;
				PrintStack();
			}
			break;
		}
		else
		{
			if(LLOneTable[row][in]==-777)
			{
				i++;
				in=getInput(i);
				cout<<"Error"<<endl;
			}
			else if(LLOneTable[row][in]==-888)
			{
				top=POP();
				row=top*-1;
				cout<<"POP"<<endl;
				PrintStack();
			}
			else
			{
				indexLL1=LLOneTable[row][in];//shows which rule gonna run
				length=LengthGrammerRule(indexLL1);
				Push(length,indexLL1);
				PrintStack();
				//Display_Rules_(in);
				in=getInput(i);
				top=POP();
				row=top*-1;
			}
		}

	}
}
int main()
{
	char input[20];
	GetInput(input);
	IsConverted(input);
	Fill_CFG_Rules();
	Fill_LL1ParseTable();
	//Rules_Char_Store();
	Stack[0]=-999;
	Stack[1]=-20;
	currentPtrStack=1;
	PrintStack();
	Parsing();
	return 0;
}
//(id+id)*num$   test case
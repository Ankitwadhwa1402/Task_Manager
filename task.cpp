#include <bits/stdc++.h>
using namespace std;
int main(int argc,char *argv[])
{
	fstream pending,complete,temp;
	temp.open("temp.txt",ios::in|ios::out|ios::trunc);
	complete.open("completed.txt",ios::in|ios::out|ios::app);
	pending.open("task.txt",ios::in|ios::out|ios::app);
	string usage="Usage :-\n$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list\n$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order\n$ ./task del INDEX            # Delete the incomplete item with the given index\n$ ./task done INDEX           # Mark the incomplete item with the given index as complete\n$ ./task help                 # Show usage\n$ ./task report               # Statistics";
	if(argc==1)
	{
		cout<<usage;
	}
	else if(argc==2 && string(argv[1])=="help")
	{
		cout<<usage;
	}
	else if(string(argv[1])=="ls")
	{
		string line;
		int ln=1;
		pending.seekg(0,ios::end);
		if(pending.tellg()==0)
		{
			cout<<"There are no pending tasks!";
		}
		else
		{
			pending.seekg(0,ios::beg);
			while(!pending.eof())
			{
				getline(pending,line);
				if(line=="")
				{
					break;
				}
				string s(line);
				int l;
				for(int j=0;j<s.size();j++)
				{
					if(line[j]-'0'<0 || line[j]-'0'>9 )
					{
						l=j;
						break;
					}
				}
			cout<<ln<<". "<<line.substr(l+1,s.size()-l)<<" ["<<line.substr(0,l)<<"]"<<'\n';
				ln++;
			}
			pending.close();
		}
		
	}
	else if(string(argv[1])=="add")
	{
		if(argc!=4)
		{
			cout<<"Error: Missing tasks string. Nothing added!";
		}
		else
		{
			int x=1,len,p,prty=stoi(argv[2]);
			string line,text(string(argv[2])+" "+string(argv[3]));
			pending.seekg(0,ios::end);
			if(pending.tellg()==0)
			{
				pending<<text<<'\n';
			}
			else
			{
				pending.seekg(0,ios::beg);
				while(!pending.eof())
				{
					getline(pending,line);
					if(line=="")
					{
						break;
					}
					string s(line);
					int l;
					for(int j=0;j<s.size();j++)
					{
						if(s[j]==' ')
						{
							l=j;
						}
					}
					p=stoi(s.substr(0,l));
					if(p>prty && x==1)
					{
						temp<<text<<'\n';
						x=0;
					}
					temp<<line<<'\n';
				}
				if(x==1)
				{
					temp<<text<<'\n';
				}
				pending.close();
				fstream pnding;
				pnding.open("task.txt",ios::out|ios::trunc);
				temp.seekg(0,ios::beg);
				while(!temp.eof())
				{
					getline(temp,line);
					if(line=="")
					{
						break;
					}
					pnding<<line<<'\n';
				}
				temp.close();
				fstream tmp;
				tmp.open("temp.txt",ios::out|ios::trunc);	
				tmp.close();
			}
			cout<<"Added task: \""<<argv[3]<<"\" with priority "<<prty;
		}
	}
	else if(string(argv[1])=="done")
	{
		if(argc!=3)
		{
			cout<<"Error: Missing NUMBER for marking tasks as done.";
		}
		else
		{
			string line;
			int l,ln=1,n=stoi(argv[2]);
			while(!pending.eof())
			{
				if(ln==n)
				{
					getline(pending,line);
					if(line=="")
					{
						break;
					}
					string s(line);
					for(int j=0;j<s.size();j++)
					{
						if(line[j]-'0'<0 && line[j]-'0'>9 )
						{
							l=j;
						}
					}
					complete<<line.substr(l+1,s.size()-l)<<'\n';
					ln++;
					continue;
				}
				getline(pending,line);
				if(line=="")
				{
					break;
				}
				temp<<line<<'\n';
				ln++;	
			}
			pending.close();
			if(n==0 || ln<=n)
			{
				cout<<"Error: no incomplete item with index #"<<n<<" exists.";
			}
			else
			{
				fstream pnding;
				pnding.open("task.txt",ios::out|ios::trunc);
				temp.seekg(0,ios::beg);
				while(!temp.eof())
				{
					getline(temp,line);
					if(line=="")
					{
						break;
					}
					pnding<<line<<'\n';
				}
				temp.close();
				fstream tmp;
				tmp.open("temp.txt",ios::out|ios::trunc);	
				tmp.close();
				cout<<"Marked item as done.";
			}
		}
		
		
	}
	else if(string(argv[1])=="del")
	{
		if(argc!=3)
		{
			cout<<"Error: Missing NUMBER for deleting tasks.";
		}
		else
		{

			string line;
			int ln=1,n=stoi(argv[2]);
			while(!pending.eof())
			{
				if(ln==n)
				{
					getline(pending,line);
					if(line=="")
					{
						break;
					}
					ln++;
					continue;
				}
				getline(pending,line);
				if(line=="")
				{
					break;
				}
				temp<<line<<'\n';
				ln++;
			}	
			pending.close();
			if(n==0 || ln<=n)
			{
				cout<<"Error: task with index #"<<n<<" does not exist. Nothing deleted.";
			}
			else
			{
				fstream pnding;
				pnding.open("task.txt",ios::out|ios::trunc);	
				temp.seekg(0,ios::beg);
				while(!temp.eof())
				{
					getline(temp,line);
					if(line=="")
					{
					break;
					}
					pnding<<line<<'\n';
				}
				temp.close();
				fstream tmp;
				tmp.open("temp.txt",ios::out|ios::trunc);	
				tmp.close();	
				cout<<"Deleted task #"<<argv[2];
			}
		}	
	}
	else if(string(argv[1])=="report")
	{
		string line;
		int ln=0;
		while(!pending.eof())
		{
			getline(pending,line);
			if(line=="")
			{
				break;
			}
			ln++;
		}
		cout<<"Pending : "<<ln<<'\n';
		fstream pnding;
		pnding.open("task.txt",ios::in);
		ln=1;
		while(!pnding.eof())
		{
			getline(pnding,line);
			if(line=="")
			{
				cout<<'\n';
				break;
			}
				string s(line);
				int l;
				for(int j=0;j<s.size();j++)
				{
					if(line[j]-'0'<0 || line[j]-'0'>9 )
					{
						l=j;
						break;
					}
				}
			cout<<ln<<". "<<line.substr(l+1,s.size()-l)<<" ["<<line.substr(0,l)<<"]"<<'\n';
			ln++;
		}
		ln=0;
		
		while(!complete.eof())
		{
			getline(complete,line);
			if(line=="")
			{
				break;
			}
			ln++;
		}
		cout<<"Completed : "<<ln<<'\n';
		line="";
		fstream cmplete;
		cmplete.open("completed.txt",ios::in);
		ln=1;
		while(!cmplete.eof())
		{
			getline(cmplete,line);
			if(line=="")
			{
				break;
			}
				string s(line);
				int l;
				for(int j=0;j<s.size();j++)
				{
					if(line[j]-'0'<0 || line[j]-'0'>9 )
					{
						l=j;
						break;
					}
				}
			cout<<ln<<". "<<line.substr(l+1,s.size()-l)<<'\n';
			ln++;
		}
		
	}

}

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include"indexer_list.h"
char* words[1200];
int count=0;
/*


void find_meta(char* html)
{
	int i=0;
	printf("meta");
	char* metaStart,*metaEnd;
	while(html[i]!='\0')
	{
		if((html[i]=='<') && (html[i+1]=='m'))
		{
			metaStart=&html[i];
			metaStart=strpbrk(metaStart," ");
			metaStart++;
			metaEnd=strpbrk(metaStart,"/");
			printf("\n\n");
			for(;metaStart!=metaEnd;metaStart++)
			{
				printf("%c",*metaStart);
			}
		}
		i++;
	}
	
}
*/

void getWords(char* str,int l)
{
	char s[200]="";
	int c=0,i=0,j=0,inword=0;
	//rem_spaces(str);
	//for(i=0;i<l;i++)
	
	while(str[i]!='\0')
	{
		if(str[i]==' ')
		{
			if(inword==1)
			{
				str[j++]=' ';
				inword=0;
			}
		}
		else
		{
			inword=1;
			str[j++]=str[i];
		}
	i++;
	}
	if(inword==0)
	{
		str[j-1]='\0';	
	}
	else
		str[j]='\0';
	i=0;
	//printf("%s",str);	
	while(str[i]!='\0')
	{
		if(str[i]==' ' || str[i]=='\0' || str[i]=='\n')
		{
			s[c]='\0';
			//printf("%s\n",s);
			//if(s[0]!=' ')
				//put_words_in_list(s,file_name);
			words[count]=(char*)calloc(100,1);
			strcpy(words[count],s);
			c=0;
			count++;
			//i++;
		}
		else
		{
			if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z'))
				s[c++]=str[i];
			//i++;
		}
		i++;
		
	}
	s[c]='\0';
	//if(s[0]!=' ')
	//put_words_in_list(s,file_name);
	//printf("%s\n",s);
	words[count]=(char*)calloc(100,1);
	strcpy(words[count],s);
	count++;
}

void find_heading(char* html)
{
	int i=0,j=0;
	//char *b=(char*)calloc(300,1);
	
	char* hStart,*hEnd;
	while(html[i]!='\0')
	{
		hStart=NULL;
		hEnd=NULL;
		if((html[i]=='<') && (html[i+1]=='h'))
		{
			char *b=(char*)calloc(700,1);
			j=0;
			hStart=&html[i];
			hStart=strpbrk(hStart,">");
			hStart++;
			hEnd=strpbrk(hStart,"<");
			//printf("\n\n");
			while(hStart!=hEnd)
			{
				//printf("%c",*hStart);
				b[j]=*hStart;
				//printf("%c",b[j]);
				j++;
				hStart++;
			}
			b[j++]='\0';
			//printf("%s\n",b);
			getWords(b,j);
			free(b);
			
		}
		i++;
	}
	//b[j]='\0';
	
	//printf("%s",b);
	//printf("\n");
	//getWords(b,j);
}


void find_title(char* html)
{
	int i=0,j=0;
	//char buffer[1000];
	char* buffer=(char*)calloc(70,1);
	char* titleStart,*titleEnd;
	while(html[i]!='\0')
	{
		if((html[i]=='<') && (html[i+1]=='t'))
		{
			titleStart=&html[i];
			titleStart=strpbrk(titleStart,"\'\">");
			titleStart++;
			break;
		}
		i++;
	}
	titleEnd=strpbrk(titleStart,"<");
	for(;titleStart!=titleEnd;titleStart++)
	{
		//printf("%c",*titleStart);
		buffer[j++]=*titleStart;
	}
	buffer[j]='\0';
	//printf("%s",buffer);
	//printf("\n");
	getWords(buffer,j);
	free(buffer);
}
void read_copied_content(char* html)
{
	find_title(html);
	find_heading(html);
	//unique_words(words,count);
	put_words_in_list(words,count,html);
}
void copy_content(char *name)
{
	int i=0;
	char ch1;
	FILE *ptr;
	ptr=fopen(name,"r");
	struct stat st; //variable which will count length of file.
        stat(name,&st); // temp.txt is the file where wget fetch the html
        int file_size=st.st_size;
	char *html=(char*)calloc(file_size,1);
	while((ch1=fgetc(ptr))!=EOF)
	{
		
		html[i++]=ch1;
	}
	html[i]='\0';
	read_copied_content(html);
	free(html);
}

int main()
{
	char choice;
	printf("Retrieve words_info from file?\n");
	scanf("%c",&choice);
	if(choice=='y')
	{
		retrieve_from_file();
	}
	else
	{
	int i=1;
	for(i=1;i<=5;i++)
	{
		//static int c=1;
		//char ch1;
		char file_name[20]={0};
		char open[100]={0};
		char ch[15]={0};
		sprintf(ch, "%d" ,i);	
		strcat(file_name,ch);
		strcat(file_name,".txt");
		//c++;
		strcat(open,"/home/hp/Documents/");
		strcat(open,file_name);
	copy_content(open);
	//free(words);
	count=0;
	//printf("%s ",open);
	}	
	//display(head);
	display_vertical_nodes(head);
	//put_words_info_in_file(head);
	}
return 0;
}












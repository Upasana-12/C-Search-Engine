#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include"linkedlist.h"
#define BASE_URL "www.chitkara.edu.in"
#define DEPTH 5

void valid_url(char* argv1)
{
	char url[400]="wget --spider ";
	//rcat(url,"wget --spider ");
	strcat(url,argv1);
	if(!system(url))
	printf("\nValid URL");
	else
	{
	printf("\nInvalid URL");
	exit(1);
	}
}

//---------------------------

void compare_url(char argv[])
{
  int i=0;
  char seed[strlen(argv)+5];
  //char base_url[100]="www.chitkara.edu.in";
	  while(argv[i]!='/' && argv[i]!='\0')
  	  {
             seed[i]=argv[i];
             i++;
  	  }
   seed[i]='\0';
   if(strcmp(seed,BASE_URL)==0)
     printf("\ncorrect url");
        else
	{
		printf("\nincorrect url");
		exit(0);
	}
}

//------------------------------------------------------------------


void check_depth(char argv[])
{
	int i=atoi(argv);
	if(i>=1 && i<=DEPTH)
	{
		printf("\ncorrect depth");
	}
	else
	{
		printf("\nWrong Depth");
		exit(0);
	}
}

//------------------------------------------------------------------

void testDir(char *dir)
{
  struct stat statbuf;

  if(stat(dir,&statbuf)==-1) 
  {
    printf("-----------------\n");
    printf("Invalid directory\n");
    printf("-----------------\n");
    exit(1);
  }

  //Both check if there's a directory and if it's writable
  if ( !S_ISDIR(statbuf.st_mode) ) 
  {
    printf("-----------------------------------------------------\n");
    printf("Invalid directory entry. Your input isn't a directory\n");
    printf("-----------------------------------------------------\n");
    exit(1);
  }
else
printf("\nvalid directory");

  if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR ) 
  {
    printf("------------------------------------------\n");
    printf("Invalid directory entry. It isn't writable\n");
    printf("------------------------------------------\n");
    exit(1);
  }
else
printf("\ndirectory is writable");
}
//----------------------------------------------------------------------

void removeWhiteSpace(char* html) 
{
  int i;
  char *buffer = malloc(strlen(html)+1), *p=malloc (sizeof(char)+1);
  memset(buffer,0,strlen(html)+1);
  for (i=0;html[i];i++) 
  {
    if(html[i]>32)
    {
      sprintf(p,"%c",html[i]);
      strcat(buffer,p);
    }
  }
  strcpy(html,buffer);
  free(buffer); 
  free(p);
}

//---------------------------------------------------------------------

int GetNextURL(char* html, char* urlofthispage, char* result, int pos) 
{
  char c;
  int len, i, j;
  char* p1;  //!< pointer pointed to the start of a new-founded URL.
  char* p2;  //!< pointer pointed to the end of a new-founded URL.

  if(pos == 0) {
    removeWhiteSpace(html);
  }
  
 // Find the <a> <A> HTML tag.
  while (0 != (c = html[pos])) 
  {
    if ((c=='<') && ((html[pos+1] == 'a') || (html[pos+1] == 'A'))) {
      break;
    }
    pos++;
  }
  //! Find the URL it the HTML tag. They usually look like <a href="www.abc.com">
  //! We try to find the quote mark in order to find the URL inside the quote mark.
  if (c) 
  {  
    p1 = strchr(&(html[pos+1]), '=');
    
    if ((!p1) || (*(p1-1) == 'e') || ((p1 - html - pos) > 10)) 
    {
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*(p1+1) == '\"' || *(p1+1) == '\'')
      p1++;

    p1++;    

    p2 = strpbrk(p1, "\'\">");
    if (!p2) 
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*p1 == '#') 
    { 
	return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (!strncmp(p1, "mailto:",7))
      return GetNextURL(html, urlofthispage, result, pos+1);

    if (!strncmp(p1, "http", 4) || !strncmp(p1, "HTTP", 4)) 
    {
      //! Nice! The URL we found is in absolute path.
      strncpy(result, p1, (p2-p1));
//printf("\n%s",result);
      return  (int)(p2 - html + 1);
    } 
    else 
    {
      //! We find a URL. HTML is a terrible standard. So there are many ways to present a URL.
      if (p1[0] == '.') 
      {
        //! Some URLs are like <a href="../../../a.txt"> I cannot handle this. 
	return GetNextURL(html,urlofthispage,result,pos+1);
	// /NEW
      }
      if (p1[0] == '/') 
      {
        //! this means the URL is the absolute path
        for (i = 7; i < strlen(urlofthispage); i++)
          if (urlofthispage[i] == '/')
            break;
        strcpy(result, urlofthispage);
        result[i] = 0;
        strncat(result, p1, (p2 - p1));
//printf("\n%s",result);
        return (int)(p2 - html + 1);        
      } 
       else 
      {
        //! the URL is a absolute path.
        len = strlen(urlofthispage);
        for (i = (len - 1); i >= 0; i--)
          if (urlofthispage[i] == '/')
            break;
        for (j = (len - 1); j >= 0; j--)
          if (urlofthispage[j] == '.')
              break;
        if (i == (len -1)) 
	{
          //! urlofthis page is like http://www.abc.com/
            strcpy(result, urlofthispage);
            result[i + 1] = 0;
            strncat(result, p1, p2 - p1);
//printf("\n%s",result);
            return (int)(p2 - html + 1);
        }
        if ((i <= 6)||(i > j)) 
	{
          //! urlofthis page is like http://www.abc.com/~xyz
          //! or http://www.abc.com
          strcpy(result, urlofthispage);
          result[len] = '/';
          strncat(result, p1, p2 - p1);
//printf("\n%s",result);
          return (int)(p2 - html + 1);
        }
        strcpy(result, urlofthispage);
        result[i + 1] = 0;
        strncat(result, p1, p2 - p1);
//printf("\n%s",result);
        return (int)(p2 - html + 1);
      }
    }
  }    
  return -1;
}

//---------------------------------------------------------------------

int NormalizeURL(char* URL) 
{
  int len = strlen(URL);
  if (len <= 1 )
    return 0;
  //! Normalize all URLs.
  if (URL[len - 1] == '/') 
  {
    URL[len - 1] = 0;
    len--;
  }
  int i, j;
  len = strlen(URL);
  //! Safe check.
  if (len < 2)
    return 0;
  //! Locate the URL's suffix.
  for (i = len - 1; i >= 0; i--)
    if (URL[i] =='.')
      break;
  for (j = len - 1; j >= 0; j--)
    if (URL[j] =='/')
      break;
  //! We ignore other file types.
  //! So if a URL link is to a file that are not in the file type of the following
  //! one of four, then we will discard this URL, and it will not be in the URL list.
  if ((j >= 7) && (i > j) && ((i + 2) < len)) 
  {
    if ((!strncmp((URL + i), ".htm", 4))
        ||(!strncmp((URL + i), ".HTM", 4))
        ||(!strncmp((URL + i), ".php", 4))
        ||(!strncmp((URL + i), ".jsp", 4))
        ) 
    {
      len = len; // do nothing.
    } 
    else 
    {
      return 0; // bad type
    }
  }
  return 1;
}

//-------------------------------------------------------------

int is_already_present(char* temp,char** result,int l)
{
	int i;
	for(i=0;i<l;i++)	
	{
		if(strcmp(result[i],temp)==0)
		return 1;
	}
	
	return 0;
}

//--------------------------------------------------------------

void get_urls(char* url,char *copied,int file_size,int depth)
{
	int i,validity;
	int pos=0;
	char *result[25];
	char uotp[400]={0};
	int j=0,k=0;
	while(copied[j]!='\n')
	{
		uotp[k++]=copied[j];
		j++;
	}
	uotp[k]='\0';
//printf("\n%s",uotp);
	//char* temp=(char*)malloc(sizeof(char)*125);
	result[0]=uotp;
//printf("\n%s",result[0]);
	for(i=1;i<25 && pos<file_size;)
	{
		char* temp=(char*)calloc(125,sizeof(char));
		pos=GetNextURL(copied,uotp,temp,pos);
		validity=NormalizeURL(temp);
		if(validity==1)
		{
			if(!(is_already_present(temp,result,i)))
			{
				result[i]=temp;
				//printf("\n%d.%s",i,result[i]);
				i++;
			}
			else
				free(temp);
		}
	}
	put_links_in_list(result,i,depth);
}

//--------------------------------------------------------------------------

void copy_content(char* url,char* name,int depth)
{
	
	  //printf("\ncopy_content running\n");
	//char path[50];
	//strcat(path,"/home/hp/Documents/");
	//strcat(path,name);
	struct stat st; //variable which will count length of file.
        stat(name,&st); // temp.txt is the file where wget fetch the html
        int file_size=st.st_size;
//      printf("%d",file_size);
	int i=0;
	char ch1;
	char *html=(char*)calloc(1,file_size);
	FILE *ptr;
	ptr=fopen(name,"r");
	while((ch1=fgetc(ptr))!=EOF)
	{
		//fprintf(ptr2,"%s",p);
		//fgets(p,2,ptr1);
		html[i++]=ch1;
	}	
	html[i]='\0';
//      printf("%s",html);
        //printf("\nget_urls called\n");
	get_urls(url,html,file_size,depth);
	free(html);
}

//----------------------------------------------------------------------------

void shift_page(char* url,int depth)
{
	//printf("\nshift page running\n");
	static int c=1;
	char ch1;
	//int d=0;
	//char file_name[10],open[50];
	char file_name[20]={0};
	char open[100]={0};
	char ch[15]={0};
	//ch[0]=c+48;
	//ch[1]='\0';
	//strcpy(file_name,"/home/hp/Documents/");
	sprintf(ch, "%d" ,c);	
	strcat(file_name,ch);
	strcat(file_name,".txt");
	c++;
	strcat(open,"/home/hp/Documents/");
	strcat(open,file_name);
	printf("%s making\n",open);
	FILE *ptr1,*ptr2;
	ptr1=fopen("/home/hp/Documents/temp.txt","r");
	ptr2=fopen(open,"w");
	fprintf(ptr2,"%s\n",url);
	fprintf(ptr2,"%d\n",depth);
	//char p[3];
	//fgets(p,2,ptr1);
	while((ch1=fgetc(ptr1))!=EOF)
	{
		//fprintf(ptr2,"%s",p);
		//fgets(p,2,ptr1);
		putc(ch1,ptr2);
	}	
	fclose(ptr1);
	//fclose(ptr2);
	copy_content(url,open,depth);
}

//---------------------------------------------------------------------------------

void getpage(char *url,char* dir,int depth)
{

char urlbuffer[1000+300]={0}; 
strcat(urlbuffer,"wget -O ");
strcat(urlbuffer,dir);
strcat(urlbuffer,"/temp.txt ");
strcat(urlbuffer,url);
system(urlbuffer);
shift_page(url,depth);
}

//----------------------------------------------------------------

char* get_next_url_to_visit(int current_depth)
{
	//char* s=NULL;
	struct LINK* p;
	p=head;
	while(p!=NULL)
	{
		if(p->link_depth==current_depth && p->link_flag==0)
		{
			p->link_flag=1;
			return p->url;
		}
		p=p->next;
	}
	return NULL;
}

//---------------------------------------------------

int main(int argc,char *argv[])
{
	int current_depth=1;
	int depth=atoi(argv[2]);
	char ch;
  printf("Retrieve links from file or not?\n");
  scanf("%c",&ch);
  if(ch=='y')
  {
	retrieve_links_from_file();
  }
  else
 {

  	if(argc!=4)
  	{
  		printf("\nWrong arguments");
  		return 0;   
  	}
  
	 valid_url(argv[1]);
	compare_url(argv[1]);
  	check_depth(argv[2]);
	testDir(argv[3]);
	getpage(argv[1],argv[3],0);
 }
while(current_depth<=depth)
{
	char* next_url=NULL;
	
	//int depth=current_depth+1;
	next_url=get_next_url_to_visit(current_depth);
	if(next_url!=NULL)
	{
		getpage(next_url,argv[3],current_depth);
	
	}
	else
	{
		//free(next_url);
		current_depth++;
		
	}
	//system("sleep(5)");
	
}
display(head);
return 0;
}


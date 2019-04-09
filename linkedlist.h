#include<string.h>
#define BASE_URL "www.chitkara.edu.in"
struct LINK
{
char *url;
int link_key;
//struct LINK* pre;
struct LINK* next;
int link_depth;
int link_flag;
};

struct LINK* head=NULL;
//struct LINK* t=NULL,*node,*new_node;
//struct LINK* p=NULL;

struct Hash
{
struct LINK* first;
struct LINK* last;
int count;
};

struct Hash hash[50]={NULL};
//-----------------------------------------------------
void initialise()
{
	int i=0;
	for(i=0;i<50;i++)
	{
		hash[i].first=NULL;
		hash[i].last=NULL;
		hash[i].count=0;
	}
}
//----------------------------------------------------
void display(struct LINK* h)
{
	struct LINK* p;
	p=h;
	int i=0;
	while(p!=NULL)
	{
		printf("\n%d. key= %d link= %s depth= %d flag= %d\n",i,p->link_key,p->url,p->link_depth,p->link_flag);
		p=p->next;
		i++;
	}
}

//------------------------------------------------------------------

void save_links_in_file(struct LINK* head)
{
	FILE* ptr;
	ptr=fopen("/home/hp/Documents/links.txt","w");
	struct LINK* p;
	p=head;
	//char div[100]={0};
	while(p!=NULL)
	{
		/*
		strcat(div,p->url);
		strcat(div,",");
		strcat(div,p->link_key)
		*/
		fprintf(ptr,"%s ",p->url);
		fprintf(ptr,"%d ",p->link_key);
		fprintf(ptr,"%d ",p->link_depth);
		fprintf(ptr,"%d\n",p->link_flag);
		p=p->next;	
	}
}

int generate_key(char *url)
{
	int sum=0,i=0;
	while(url[i]!='\0')
	{
		sum=sum+(int)url[i];
		i++;	
	}
	int key=sum%50;
return key;
}

void retrieve_links_from_file()
{
	initialise();
	head=NULL;
	char ch;
	int i=0,j=0,k=0;
	char c[150]={0};
	char url_str[125]={0};
	char* URL=NULL;
	FILE* ptr=fopen("/home/hp/Documents/links.txt","r");
	struct LINK* temp=NULL,*pre=NULL,*p=NULL;
	//temp=(struct LINK*)calloc(1,sizeof(struct LINK));
	while((ch=fgetc(ptr))!=EOF)
	{
		if(ch=='\n')
		{
			c[i]='\0';
			i=0;
			j=0;
			k=0;
			temp=(struct LINK*)calloc(1,sizeof(struct LINK));
			URL=(char*)calloc(1,125);
			while(c[k]!=' ')
			{
				url_str[j]=c[k];
				j++;
				k++;
			}
			url_str[j]='\0';
			URL=(char*)calloc(1,125);
			strcpy(URL,url_str);
			temp->url=URL;
			//printf("%s\n",temp->url);
			temp->link_key=generate_key(url_str);
			int key=temp->link_key;
			j=0;
			k++;
			while(c[k]!=' ')
			{
				k++;
			}
			k++;
			while(c[k]!=' ')
			{
				url_str[j]=c[k];
				j++;
				k++;
			}
			url_str[j]='\0';
			temp->link_depth=atoi(url_str);	
			k++;
			j=0;
			while(c[k]!='\0')
			{
				url_str[j]=c[k];
				j++;
				k++;
			}
			url_str[j]='\0';
			temp->link_flag=atoi(url_str);
			k=0;
			j=0;

		if(head==NULL)	
		{
			temp->link_depth=1;
			temp->link_flag=1;
			head=temp;
			pre=temp;
			hash[key].first=temp;
			hash[key].last=temp;
                        hash[key].count=1;
                        continue;
		}
		else
		{
			if(hash[key].first==NULL)
			{
				p=head;
				while(p->next!=NULL)
					p=p->next;
				p->next=temp;
				temp->next=NULL;
				pre=temp;
                               hash[key].first=temp;
                               hash[key].last=temp;
                               hash[key].count=1;
			}
			else
			{
				p=hash[key].first;
				int f=0;
				while(p->next!=NULL && p->next->link_key==key)
				{
					if(strcmp(p->url,temp->url)==0)
					{
						free(temp);
						free(URL);
						f=1;
						break;
					}
					p=p->next;
				}
				if(f)
				continue;
				temp->next=p->next;
				p->next=temp;
				 hash[key].last=temp;
                                hash[key].count++;
			}
		}
		c[0]='\0';
		}
		else
		{
			c[i++]=ch;
		}
		
	}
	display(head);
	
}
void put_links_in_list(char **result,int l,int depth)
{
	
	//static int c=0;
        //c++; 	
	int i;
	struct LINK* temp,*pre=NULL,*p;
	for(i=0;i<l;i++)
	{
		temp=(struct LINK*)calloc(1,sizeof(struct LINK));
		temp->link_key=generate_key(result[i]);
		int key=temp->link_key;
		temp->link_flag=0;
		temp->url=result[i];
		temp->link_depth=depth+1;
		if(head==NULL)	
		{
			temp->link_depth=0;
			temp->link_flag=1;
			head=temp;
			pre=temp;
			hash[key].first=temp;
			hash[key].last=temp;
                        hash[key].count=1;
                        continue;
		}
		else
		{
			if(hash[key].first==NULL)
			{
				p=head;
				while(p->next!=NULL)
					p=p->next;
				p->next=temp;
				temp->next=NULL;
				pre=temp;
                               hash[key].first=temp;
                               hash[key].last=temp;
                               hash[key].count=1;
			}
			else
			{
				p=hash[key].first;
				int f=0;
				if((strcmp(hash[key].first->url,temp->url)==0)||(strcmp(hash[key].last->url,temp->url)==0))
				{
					free(temp);
					continue;
				}
				while(p->next!=NULL && p->next->link_key==key)
				{
					if(strcmp(p->url,temp->url)==0)
					{
						free(temp);
						f=1;
						break;
					}
					p=p->next;
				}
				if(f)
				continue;
				temp->next=p->next;
				p->next=temp;
				 hash[key].last=temp;
                                hash[key].count++;
			}
		}
	}
save_links_in_file(head);
//retrieve_links_from_file();
//display(head);
}







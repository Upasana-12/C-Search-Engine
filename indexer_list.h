#include<string.h>
#include<stdlib.h>

struct PAGE
{
	char* page_url;
	struct PAGE* next;
	int wcount;
};
struct LINK
{
	char* word;
	//int word_count;
	int link_key;
	struct LINK* next;
	struct PAGE* headpage;
};

struct LINK* head=NULL;

struct Hash
{
	struct LINK* first;
	struct LINK* last;
	//int count;
};

struct Hash hash[50]={NULL};

void initialise()
{
	int i=0;
	for(i=0;i<50;i++)
	{
		hash[i].first=NULL;
		hash[i].last=NULL;
		//hash[i].count=0;
	}
}

void display_vertical_nodes(struct LINK* h)
{
	struct LINK* p;
	struct PAGE* trav;
	p=h;
	int i=0;
	while(p!=NULL)
	{
		trav=p->headpage;
		while(trav!=NULL)
		{
			printf("%d. key=%d word=%s url=%s wc_on_url=%d\n",i,p->link_key,p->word,trav->page_url,trav->wcount);
			trav=trav->next;
		}
		p=p->next;
		i++;
	}
}


int generate_key(char *word)
{
	int sum=0,i=0;
	while(word[i]!='\0')
	{
		sum=sum+(int)word[i];
		i++;	
	}
	int key=sum%30;
return key;
}

void retrieve_from_file()
{
	initialise();
	struct LINK* temp,*pre=NULL,*p;
	struct PAGE* pnode,*trav;
	head=NULL;
	char ch;
	int i=0,j=0,k=0;
	char c[150]={0};
	char url_str[125]={0};
	char* URL=NULL;
	char* w=NULL;
	FILE* ptr=fopen("/home/hp/Documents/links.txt","r");
	while((ch=fgetc(ptr))!=EOF)
	{
		if(ch=='\n')
		{
			c[i]='\0';
			i=0;
			j=0;
			k=0;
			temp=(struct LINK*)calloc(1,sizeof(struct LINK));
			pnode=(struct PAGE*)calloc(1,sizeof(struct PAGE));
			while(c[k]!=' ')
			{
				url_str[j]=c[k];
				j++;
				k++;
			}
			url_str[j]='\0';
			w=(char*)calloc(100,1);
			strcpy(w,url_str);
			temp->word=w;
			printf("%s\n",temp->word);
			temp->link_key=generate_key(url_str);
			int key=temp->link_key;
			j=0;
			k++;
			while(c[k]!=' ')
			{
				url_str[j]=c[k];
				j++;
				k++;
			}
			url_str[j]='\0';
			URL=(char*)calloc(1,125);
			strcpy(URL,url_str);
			pnode->page_url=URL;
			printf("%s\n",pnode->page_url);
			k++;
			j=0;
			while(c[k]!='\0')
			{
				url_str[j]=c[k];
				j++;
				k++;
			}
			url_str[j]='\0';
			pnode->wcount=atoi(url_str);
			j=0;
			k=0;
			
		if(head==NULL)	
		{
			//temp->word_count=1;
			//pnode=(struct PAGE*)calloc(1,sizeof(struct PAGE));
			head=temp;
			pre=temp;
			hash[key].first=temp;
			hash[key].last=temp;
			//pnode->page_url=url;
			pnode->next=NULL;
			//pnode->wcount=1;
			temp->headpage=pnode;
                       // hash[key].count=1;
			//last=temp;
                        continue;
		}

		else
		{
			if(hash[key].first==NULL)
			{
				//temp->word_count=1;
				p=head;
				while(p->next!=NULL)
					p=p->next;
				p->next=temp;
				//temp->word_count=1;
				temp->next=NULL;
				pre=temp;
				//last->next=temp;
				//temp->next=NULL;
				//last=temp;
				//temp->word_count=1;
                               hash[key].first=temp;
                               hash[key].last=temp;
				//pnode->page_url=url;
				pnode->next=NULL;
				//pnode->wcount=1;
				temp->headpage=pnode;
                               //hash[key].count=1;
			}
			else
			{
				p=hash[key].first;
				int f=0;
				if(strcmp(hash[key].first->word,temp->word)==0)
				{
					//hash[key].first->word_count+=1;
					trav=hash[key].first->headpage;
					while(trav->next!=NULL)
					{
						trav=trav->next;
					}
					if(strcmp(trav->page_url,URL)==0)
					{
					//	trav->wcount+=1;
						free(pnode);
					}
					else
					{
					//	pnode->page_url=url;
						pnode->next=NULL;
					//	pnode->wcount=1;
						trav->next=pnode;
					}
					free(temp);
					continue;
				}
				if(strcmp(hash[key].last->word,temp->word)==0)
				{
					//hash[key].last->word_count+=1;
					trav=hash[key].last->headpage;
					while(trav->next!=NULL)
					{
						trav=trav->next;
					}
					if(strcmp(trav->page_url,URL)==0)
					{
					//	trav->wcount+=1;
						free(pnode);
					}
					else
					{
					//	pnode->page_url=url;
						pnode->next=NULL;
					//	pnode->wcount=1;
						trav->next=pnode;
					}
					free(temp);
					continue;
				}
				while(p->next!=NULL && p->next->link_key==key)
				{
					if(strcmp(p->word,temp->word)==0)
					{
						//p->word_count+=1;
						trav=hash[key].first->headpage;
						while(trav->next!=NULL)
						{
							trav=trav->next;
						}
						if(strcmp(trav->page_url,URL)==0)
						{
						//	trav->wcount+=1;
							free(pnode);
						}
						else
						{
						//	pnode->page_url=url;
							pnode->next=NULL;
						//	pnode->wcount=1;
							trav->next=pnode;
						}
						free(temp);
						f=1;
						break;
					}
					p=p->next;
				}
				if(f)
				continue;
				
					//temp->word_count=1;
					temp->next=p->next;
					p->next=temp;
				 	hash[key].last=temp;
				//	pnode->page_url=url;
					pnode->next=NULL;
				//	pnode->wcount=1;
					temp->headpage=pnode;
                                	//hash[key].count++;	
				
			}
		}		

		c[0]='\0';
		}
		
		else
		{
			c[i++]=ch;
		}
	}
	display_vertical_nodes(head);
}


void put_words_info_in_file(struct LINK* h)
{
	FILE* ptr;
	ptr=fopen("/home/hp/Documents/words_info.txt","w");
	struct LINK* p;
	struct PAGE* trav;
	p=h;
	//int i=0;
	while(p!=NULL)
	{
		trav=p->headpage;
		while(trav!=NULL)
		{
			//printf("%d. key=%d word=%s url=%s wc_on_url=%d\n",i,p->link_key,p->word,trav->page_url,trav->wcount);
			fprintf(ptr, "%s ",p->word);
			fprintf(ptr, "%s ",trav->page_url);
			fprintf(ptr, "%d\n",trav->wcount);
			trav=trav->next;
		}
		p=p->next;
		//i++;
	}
}

/*
void display_vertical_nodes(struct LINK* h)
{
	struct LINK* p;
	struct PAGE* trav;
	p=h;
	int i=0;
	while(p!=NULL)
	{
		trav=p->headpage;
		while(trav!=NULL)
		{
			printf("%d. key=%d word=%s url=%s wc_on_url=%d\n",i,p->link_key,p->word,trav->page_url,trav->wcount);
			trav=trav->next;
		}
		p=p->next;
		i++;
	}
}
*/

void display(struct LINK* h)
{
	struct LINK* p;
	p=h;
	int i=0;
	while(p!=NULL)
	{
		printf("%d. key=%d word=%s\n",i,p->link_key,p->word);
		p=p->next;
		i++;
	}
}
void put_words_in_list(char** result, int l,char* html)
{
	int i;
	char* url=(char*)calloc(400,1);
	int j=0,k=0;
	while(html[j]!='\n')
	{
		url[k++]=html[j];
		j++;
	}
	url[k]='\0';
	printf("\n\n%s\n\n",url);
	struct LINK* temp,*pre=NULL,*p;
	struct PAGE* pnode,*trav;
	for(i=0;i<l;i++)
	{
		temp=(struct LINK*)calloc(1,sizeof(struct LINK));
		pnode=(struct PAGE*)calloc(1,sizeof(struct PAGE));
		temp->link_key=generate_key(result[i]);
		int key=temp->link_key;
		temp->word=result[i];
		if(head==NULL)	
		{
			//temp->word_count=1;
			//pnode=(struct PAGE*)calloc(1,sizeof(struct PAGE));
			head=temp;
			pre=temp;
			hash[key].first=temp;
			hash[key].last=temp;
			pnode->page_url=url;
			pnode->next=NULL;
			pnode->wcount=1;
			temp->headpage=pnode;
                       // hash[key].count=1;
			//last=temp;
                        continue;
		}
		else
		{
			if(hash[key].first==NULL)
			{
				//temp->word_count=1;
				p=head;
				while(p->next!=NULL)
					p=p->next;
				p->next=temp;
				//temp->word_count=1;
				temp->next=NULL;
				pre=temp;
				//last->next=temp;
				//temp->next=NULL;
				//last=temp;
				//temp->word_count=1;
                               hash[key].first=temp;
                               hash[key].last=temp;
				pnode->page_url=url;
				pnode->next=NULL;
				pnode->wcount=1;
				temp->headpage=pnode;
                               //hash[key].count=1;
			}
			else
			{
				p=hash[key].first;
				int f=0;
				if(strcmp(hash[key].first->word,temp->word)==0)
				{
					//hash[key].first->word_count+=1;
					trav=hash[key].first->headpage;
					while(trav->next!=NULL)
					{
						trav=trav->next;
					}
					if(strcmp(trav->page_url,url)==0)
					{
						trav->wcount+=1;
						free(pnode);
					}
					else
					{
						pnode->page_url=url;
						pnode->next=NULL;
						pnode->wcount=1;
						trav->next=pnode;
					}
					free(temp);
					continue;
				}
				if(strcmp(hash[key].last->word,temp->word)==0)
				{
					//hash[key].last->word_count+=1;
					trav=hash[key].last->headpage;
					while(trav->next!=NULL)
					{
						trav=trav->next;
					}
					if(strcmp(trav->page_url,url)==0)
					{
						trav->wcount+=1;
						free(pnode);
					}
					else
					{
						pnode->page_url=url;
						pnode->next=NULL;
						pnode->wcount=1;
						trav->next=pnode;
					}
					free(temp);
					continue;
				}
				while(p->next!=NULL && p->next->link_key==key)
				{
					if(strcmp(p->word,temp->word)==0)
					{
						//p->word_count+=1;
						trav=hash[key].first->headpage;
						while(trav->next!=NULL)
						{
							trav=trav->next;
						}
						if(strcmp(trav->page_url,url)==0)
						{
							trav->wcount+=1;
							free(pnode);
						}
						else
						{
							pnode->page_url=url;
							pnode->next=NULL;
							pnode->wcount=1;
							trav->next=pnode;
						}
						free(temp);
						f=1;
						break;
					}
					p=p->next;
				}
				if(f)
				continue;
				
					//temp->word_count=1;
					temp->next=p->next;
					p->next=temp;
				 	hash[key].last=temp;
					pnode->page_url=url;
					pnode->next=NULL;
					pnode->wcount=1;
					temp->headpage=pnode;
                                	//hash[key].count++;	
				
			}
		}
	}
		
//display(head);		
}

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
/*
void unique_words(char** result,int count)
{
//printf("u_w running\n%d\n",count);

	char* unique[1000];
	int i,j=1;
	char* temp=(char*)calloc(100,sizeof(char));
	unique[0]=result[0];
	//printf("%s\n",unique[0]);
	for(i=1;i<count;i++)
	{
		char* temp=(char*)calloc(100,sizeof(char));
		strcpy(temp,result[i]);
		if(temp[0]!=' ' && temp[0]!='\n')
		{
			if(!(is_already_present(temp,unique,j)))
			{
				unique[j]=temp;
				//printf("\n%d.%s",j,unique[j]);
				j++;
			}
			else
				free(temp);
		}
		else
		{
			free(temp);
			//continue;
		}	
	}
//printf("\n%d",j);
	put_words_in_list(unique,j);
}
*/
















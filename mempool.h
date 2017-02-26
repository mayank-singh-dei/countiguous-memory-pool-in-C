#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

// pool head and link
struct pmlink
{
	void* next;
};
typedef struct pmlink pmlink;

struct plink
{
	int val;
	void* fsp; 
	void* next;
	size_t esize;
};
typedef struct plink plink;

//creating pool
/* To Create A Pool , a pointer for variable of plink has to be created.
For eg. to create a pool for storing integers following would be the syntax

plink* head;
head = createpool(sizeof(int));

*/
plink* createpool(size_t a)
{
	plink* head;
	head=(plink*)malloc(sizeof(plink));
	head->val=100000;
	head->fsp =malloc(100000*a);
	head->esize=a;
	head->next=NULL;
	return head;
}
//alloting space from pool
/* Syntax for alloting space
 
 int* p;
 p=allot(head);
 
 where "head" is pointer to variable of plink , whose significance has been 
 given while creating a pool
 */
void* allot(plink* head)
{
	void* asp;
  if(head->next==NULL)
  	{
  		if(head->val==0)
  		{
  			printf("No more memory left in this pool");
  			asp=NULL;
  		}
  		else 
		  {
		   asp=head->fsp;
		    (head->val)--;
		    //void* a = get_me_a_pointer();
            //void* b = (void*)((char*)a + some_number);
		    head->fsp=(void*)((char*)(head->fsp)+(head->esize));
		  }
  	}
  	else
  	{
  		asp=head->next;
  		head->next=((pmlink*)(head->next))->next;
  		memset(asp,0,sizeof(pmlink));
  	}

  	return asp;
}
//returning space to pool
/* Syntax for returning space to pool

int* p;
p = allot(head);
dele(p,head);

*/

void dele(void* spc,plink* head)
{
	pmlink* nde=NULL;

	memset(spc,0,head->esize);
	nde=(pmlink*)spc;
	nde->next=head->next;
	head->next=nde;
	
}

// This memory pool works only if you are storing the type of variables whose size is greater than that of a void pointer


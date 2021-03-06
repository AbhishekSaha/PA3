#include <stdio.h>
#include <stdlib.h>
#include "sl.h"
#include <string.h>
#include "recurse.h"

SortedListPtr SLCreate(CompareFuncT cf)
{
    SortedListPtr newPtr;
	newPtr = (SortedListPtr) malloc(sizeof(struct SortedList));
    
    newPtr->head = NULL;
    newPtr->compareTo = cf;
   
/*    newPtr->SortedListIteratorPtr = NULL;*/

	
 	return newPtr;
}
        
    
void SLDestroy(SortedListPtr list)
{
    Node *cur = list->head;
    
    while(cur != NULL)
    {
	list->head = list->head->next; /*Move the head forward*/
	cur->next = NULL; /*Disconnect cur*/
	NodeDestroy(cur); /*Destroy the disconnected node*/
	cur = list->head; /*point cur to the new head*/ 
    }
 
    free(list);

	
    return;
}

NodePtr NodeCreate(void *newObj, char*name)
{
    
	NodePtr newPtr = (NodePtr) malloc(sizeof(Node));
   
    newPtr->name = name;
	newPtr->data = newObj;
	newPtr->next = NULL;
	newPtr->refcount = 0;

	

	return newPtr;
}

void NodeDestroy(NodePtr myNode)
{
    
	free(myNode);
	

	return;
}




/* Inserts given object into the list while maintaining sorted order. Success returns 1,
	failure returns 0 */
    
int SLInsert(SortedListPtr list, void *newObj, char*key)
{
	if(list->head == NULL)
	{
		NodePtr newNode = NodeCreate(newObj, key);
		list->head = newNode;
		list->head->refcount += 1;
		
			

		return 1;
	}
	else if(list->head != NULL)
	{


		NodePtr cur = list->head;
		NodePtr prev = NULL;
        int comp = strcmp(cur->name, key);
        while (cur->next!=NULL && comp!=0) {
            prev = cur;
            cur = cur->next;
            comp = (int)strcmp(cur->name, key);
        }
		
        
        if (comp==0) {
           
            *((int*)cur->data) = *((int*)cur->data) + 1;
            
           
           SLRemove(list, key);
           Insert(list, cur->data , key);
            return 1;
        }
        else{
          
            NodePtr nu = NodeCreate(newObj, key);
            cur->next = nu;
        }


    }
    return 1;
}


int Insert(SortedListPtr list, void *newObj, char*key){
            if(list->head==NULL)
            {
                NodePtr newNode = NodeCreate(newObj, key);
                
                list->head = newNode;
                
                
                
                
                
                return 1;
            }
            else 
            {
                
                
                NodePtr cur = (NodePtr)malloc(sizeof(Node));
                cur = list->head;
                
               
                NodePtr prev = NULL;
                
                
                /*Move the cur and prev pointers until cur points to the node where the newObj
                 should be inserted and prev points to the node before that point. */
                
                CompareFuncT comp  = list->compareTo;
                int aa = comp(newObj, cur->data);
                if(aa < 0)
                {
                    
                    
                    NodePtr newNode = NodeCreate(newObj, key);
                    
                    newNode->next = cur;
                    
                    list->head = newNode;
                    newNode->refcount += 1;
                    
                    
                    
                    
                    return 1;
                }
                else
                {
                    
                    while((cur != NULL) && (list->compareTo(newObj,cur->data)) >= 0)
                    {
                        if(newObj == cur->data)
                        {
                            
                            return 1;
                        }
                        prev = cur;
                        cur = cur->next;
                    }
                    
                    
                    NodePtr newNode = NodeCreate(newObj, key);
                    /*Insert*/
                    
                    
                    prev->next = newNode;
                    
                    newNode->refcount += 1;
                    
                    newNode->next = cur;
                    
                    
                    
                    return 1;
                }
            }
                    }


int StringInsert(SortedListPtr list, void *newObj, char*key){
    if(list->head==NULL)
    {
        NodePtr newNode = NodeCreate(newObj, key);
        
        list->head = newNode;
        
        
        
        
        
        return 1;
    }
    else
    {
        
        
        NodePtr cur = (NodePtr)malloc(sizeof(Node));
        cur = list->head;
        
        
        NodePtr prev = NULL;
        
        
        /*Move the cur and prev pointers until cur points to the node where the newObj
         should be inserted and prev points to the node before that point. */
        
        CompareFuncT comp  = list->compareTo;
        int aa = strcmp(key, cur->name);
        if(aa < 0)
        {
            
            
            NodePtr newNode = NodeCreate(newObj, key);
            
            newNode->next = cur;
            
            list->head = newNode;
            newNode->refcount += 1;
            
            
            
            
            return 1;
        }
        else
        {
            
            while((cur != NULL) && (list->compareTo(newObj,cur->data)) >= 0)
            {
                if(newObj == cur->data)
                {
                    
                    return 1;
                }
                prev = cur;
                cur = cur->next;
            }
            
            
            NodePtr newNode = NodeCreate(newObj, key);
            /*Insert*/
            
            
            prev->next = newNode;
            
            newNode->refcount += 1;
            
            newNode->next = cur;
            
            
            
            return 1;
        }
    }
}






int SLRemove(SortedListPtr list, char * key)
{
	

	if(list->head==NULL)
	{
		
		return 0; // remove failed
	}
	else
	{
   
		NodePtr cur = list->head;
		NodePtr prev = NULL;
        int comp = strcmp(cur->name, key);
		while (cur->next!=NULL && comp!=0) {
            cur = cur->next;
            prev = cur;
            comp = (int)strcmp(cur->name, key);
        }

		if (comp==0 && prev!=NULL) {
            prev->next = NULL;
            prev->next = cur->next;
            cur->next = NULL;
            NodeDestroy(cur);
        }
        else{
            NodeDestroy(cur);
            list->head = NULL;
        }
    }
    return 1;
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
	

	SortedListIteratorPtr  init = (SortedListIteratorPtr) malloc(sizeof(SortedListIterator));

	init->current = list->head;

	if(init->current != NULL)
		init->current->refcount += 1;

	
	
	return init;
}


void SLDestroyIterator(SortedListIteratorPtr iter)
{
	
	iter->current->refcount -= 1;
	iter->current = NULL; 
	free(iter);
	
	return;
}



void *SNextItem(SortedListIteratorPtr iter)
{
	
	if (iter->current->next==NULL)
    	{
		void *temp = iter->current->data;
		iter->current = iter->current->next;	
		
	
		return temp;
   	} 
	void *temp = iter->current->data;

	iter->current->refcount -= 1;

	if(iter->current->refcount==0)
	{
		
		NodePtr tomp = iter->current;

		iter->current = iter->current->next;
		iter->current->refcount += 1;
		tomp->next = NULL;
		NodeDestroy(tomp);
		
		return temp;
	} 

	else if(iter->current->refcount >= 1)
	{
		

		iter->current = iter->current->next; // Move to the next node
		iter->current->refcount += 1;
		
		
		return temp;
	}
    return NULL;
}






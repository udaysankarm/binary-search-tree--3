#include<iostream>
using namespace std;

class Node
{
	public:
	int data;
	Node* Lft;
	Node* Rgt;
	Node* P; //pointer to parent
	Node()//constructor
	{
		Rgt=NULL;
		Lft=NULL;
	}
};
class tree		//class tree
{				
	public:				
	Node *root;		//root the main reference
	tree()			
	{			// default constructor
		root=NULL;
	}
	void Insert(int val)		// insert function
	{
		if(root==NULL)		//first insertion
		{			
		Node* temp=new Node;	/// creating new node
		temp->data=val;
		root=temp;		// assiging root to temp

		}
		else
		InsertH(root,val);	//  the insert function which actually does insertion
	}
	
	void InsertH(Node* current, int Val)		// actual insertion function which inserts elements
	{
		if(Val < current->data)		//if val is less than value of current node
		{
			if(current->Lft==NULL)		//if the left node is empty add the new node here
			{
				Node* temp=new Node;
				temp->data=Val;
				temp->P=current;
				current->Lft=temp;	
			}
			else		//else call the function again
			InsertH(current->Lft,Val);	// 	
		}
		else			// inserting on right side
		{
			if(current->Rgt==NULL)		// checking whether the left is empty or not
			{
				Node* temp=new Node;
				temp->data=Val;
				temp->P=current;
				current->Rgt=temp;	
			}
			else
			InsertH(current->Rgt,Val); //if left position is not empty call the function again
		}
			
	}
	void display()		//display function 
	{
		displayM(root);	//display main function call
	}
	void displayM(Node* current)
	{
		// base condition
		if(current==NULL)
		return;
		//display left
		displayM(current->Lft);
		//display centre
		cout<<current->data<<",";	
		//display right
		displayM(current->Rgt);
	}
	bool search(int E)		//helper search function
	{
		searchM(E,root);		//calling the maIN SEARCH FUNCTION
	}
	bool searchM(int V, Node* current)
	{
		if(current==NULL) //stopping condition
		return 0;
		else
		{
			if(current->data==V) //stopping condition
			return 1;	//returning 1
			if(V > current->data) //if the value is greater than current value 
			searchM(V,current->Rgt);
			else 		//if the v is less than current data go to the left side
			searchM(V,current->Lft); //search in the left position
		}
		
			
	}
	Node *find_min(Node* curr)	// code to find the minimum of a sub tree
	{			
		if(curr==NULL)
		return NULL;			// we are continously going from left to left brach
		else if(curr->Lft==NULL)	// check for the end of the left brached
		return curr;
		else
		find_min(curr->Lft);		// go on to the next left child 	
	}
	Node *find_max(Node* curr)
	{
		if(curr==NULL)			//stopping condition
		return NULL;			//returing nothing
		else if(curr->Rgt==NULL)	//if the right position is empty
		return curr;			//return the node 
		else
		find_max(curr->Rgt);
	}
	void replace_At_parent(Node *c,Node * d)	// replacing functing
	{
		Node *p=c->P;		//storing the parent node of first node 	
		Node *pa=d->P;		//storing the parent of second in a variable
		delete	c;
		if(p->Lft==c)		//check where the current node is
		p->Lft=d;		// modify the pointer(lft,Rgt of parent) to point to d 
		else
		p->Rgt=d;		// modify the pointer(lft,Rgt of parent) to point to d
		
		if(pa->Lft==d)		// check the position of second node respect to its parent 
		pa->Lft=NULL;		//modify the parent of second node
		else
		pa->Rgt=NULL;		//modify the parent of second node 	
		
		d->P=p;			// changing the parent of second node	
	}
	Node *searchP(int VL)		// function to find the position of needed node
	{
		if(search(VL))		// if the element is present
			{
				searchPM(VL,root);	// function doing the search	
			}
			else
			cout<<"\nThe element is not present\n";// element is absent
	}
	Node *searchPM(int VV,Node* curr)
	{
		if(curr==NULL)		//stopping condition
		{
		cout<<"end";
		}
		else if(curr->data==VV)	//needed condition
		return curr;
		if(VV < curr->data)
		searchPM(VV,curr->Lft);
		else
		searchPM(VV,curr->Rgt);
	}
	void Delete(int VAL)			//delete function
	{
			if(search(VAL))			//deletion should occur only if the element is present
			{
				Node *N=searchP(VAL);	//pointer to pointer to location to be deleted 
				if(N->Lft!=NULL)	//if the left location is not empty
				{
					if(N->Rgt!=NULL)		 //if right location is not empty both 
					{
						
						Node *M=find_min(N->Rgt);//pointer to minimum location
						N->data=M->data;	 // storing data in the current node
						if(M->P->Lft==M)
						M->P->Lft=NULL;		 // making the pointer to minimum null
						else
						M->P->Rgt=NULL;
						delete M;
					}
					else				 //only left side children are there
					{
						Node *M=find_max(N->Lft);//finding the maximum node 
						N->data=M->data;	 // storing data in the current node
						if(M->P->Lft==M)
						M->P->Lft=NULL;		 // making the pointer to maximum of right null
						else
						M->P->Rgt=NULL;
						delete M;
					}
					
				}
				else if(N->Rgt!=NULL)			//only right child is present
				{
					Node *M=find_min(N->Rgt);	// the minimum of right side
					N->data=M->data;		//storing the data
					if(M->P->Lft==M)		// checking the position of minimum with respect to its parent
					M->P->Lft=NULL;			// making the pointer to maximum of right null
					else
					M->P->Rgt=NULL;
					delete M;
					
				}
				else    				// no child is there
				{	
					if(N->P->Lft==N)		//check the position of current node with respect to its parent
					N->P->Lft=NULL;			//make the pointer to this node null
					else
					N->P->Rgt=NULL;			//make the pointer to this node null
					delete N;			//delete the node					
				}
				
			}
			else
			cout<<"\nThe element is not present in the current binary search tree\n";
	}
	int count()			//count function
	{
			int a=1;
			countM(root,&a);		//main counting function
			return a;			//printing a
	}
	int countM(Node* curr,int* i)			//function which actually does the counting
	{
		if(curr->Lft!=NULL)			// going to  left sub tree
		{
			countM(curr->Lft,i);
			(*i)++;				//increamenting i
		}
		if(curr->Rgt!=NULL)			//going to right sub tree
		{
			countM(curr->Rgt,i);
			(*i)++;				//increamenting i
		}	
	}
	int R_search(int a, int b)			//range search function
	{
		int c=0;					//variable to store the number of eleemnts
		cout<<endl;
		R_searchM(a,b,&c,root);			//calling  the fuction with all the needed arguments
		if(c==0)
		cout<<"\nThere are no elements in this range\n";	//information to user
		return c;						//returing the number of elements in between
	}
	void R_searchM(int x,int y, int * C, Node*curr)	//function which actually does the counting
	{	
		if(curr==NULL)				//stopping condition
		return;					//stopping at the neded point
		R_searchM(x,y,C,curr->Lft);		//	going to left side
		int V=curr->data;
		if(V>=x&&V<=y)				// condition to check and print value
		{
			(*C)++;
			cout<<V<<" ";
		}
		R_searchM(x,y,C,curr->Rgt);		//going tho righr side
	}
	int height()					//height function
	{
		int M=0;				// m is used to store the maximum height
							// th stores height of a particular path
		height_M(root,&M,0);			// calling height main function
		return M;
	}
	void height_M(Node *curr,int *m,int T)
	{
							// Tstores the number of levels for each path
		if(curr==NULL)
		{
			if(T>*m)			// if for any particular path T i higher than maximum path the maximum is modified
			*m=T;
			return;	
		}
		height_M(curr->Lft,m,T+1);		//going to left side
		height_M(curr->Rgt,m,T+1);		//going to right side
	}

};
int main()
{
	tree A;
	Node *b;
	int AR[10]={110,45,23,42,89,67,99,454,9,56};
	for(int i=0;i<10;i++)
	A.Insert(AR[i]);
	A.display();
	/*cout<<endl<<A.search(454)<<endl;
	//A.Delete(110);*/
	A.Insert(56);
	A.Insert(98);
	A.Insert(1000);
	A.Insert(2000);
	A.Insert(3000);
	A.Insert(4000);
	A.Insert(5000);
	A.Insert(6000);
	//A.Insert(7000);
	A.display();
	cout<<endl;
	A.Delete(0);
	cout<<A.count()<<endl;
	A.Delete(42);
	cout<<A.R_search(0,1);
	cout<<endl<<A.height()<<endl;
	return 0;
}


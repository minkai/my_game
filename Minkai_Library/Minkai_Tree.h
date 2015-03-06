//last complete check: 15th July 2010 (except for a few functions under construction)
//last complete test: none

#ifndef MINKAI_TREE
#define MINKAI_TREE

#include <vector>
#include <list>

//should put as inner class inside Minkai_Tree
template <class T>
class Minkai_Tree_Node
{
private:
	T value;

public:
	Minkai_Tree_Node<T>* parent;
	//pointers to child nodes. The pointers cannot be NULL
	vector< Minkai_Tree_Node<T>* > child;

	//constructor
	Minkai_Tree_Node( const T& value_para ) : child(0)
	{
		value = value_para;

		parent = NULL;
	}
};

//to be used in Minkai_Tree
template <class T>
class Minkai_Tree_Marker
{
private:
	//cannot be NULL unless Minkai_Tree is empty
	Minkai_Tree_Node<T>* ptr;

public:
	//constructor
	Minkai_Tree_Marker()
	{
		ptr = NULL;
	}
	//move to a child node at index
	//precondition: ptr != NULL && 0 <= index && index <= int(ptr->child.size())-1
	void move_forward( int index )
	{
		if( ptr != NULL )
		{
			if( 0 <= index && index <= int(ptr->child.size())-1 )
			{
				ptr = ptr->child[index];
			}
		}

	}
	//move to parent
	//precondition: ptr != NULL && ptr->parent != NULL
	void move_backward()
	{
		if( ptr != NULL )
		{
			if( ptr->parent != NULL )
			{
				ptr = ptr->parent;
			}
		}
	}
	//move to next node in middle, left, right order
	//precondition: ptr != NULL
	bool move_next()
	{
		if( ptr != NULL )
		{
			//if (*ptr) has child
			if( !(ptr->child).is_empty() )
			{
				ptr = (ptr->child)[0];
				return true;
			}
			else
			{
				Minkai_Tree_Node<T>* original_ptr = ptr;
				while( ptr->parent != NULL )
				{
					//if ptr can move to next sibling
					if( ptr.move_next_sibling() )
					{
						return true;
					}
					else
					{
						//move up
						ptr = ptr->parent;
					}
					
				}
				
				ptr = original ptr;
				return false;			
			}
		}
		else
		{
			return false;
		}
	}
	//move to prev node in middle, left, right order
	//precondition: ptr != NULL
	void move_prev()
	{
		if( ptr != NULL )
		{
			//if (*ptr) has parent
			if( ptr->parent != NULL )
			{
				//if can move left
				if( move_previous_sibling() )
				{
					//move to rightmost child
					move_back_leaf_node();
				}
				else
				{
					//move up
					ptr = ptr->parent;
				}
			}
			//else, ptr can't move to previous
		}
	}
	
	//move to the next node in left, right, middle order
	void move_next_LRM()
	{
		//if (*ptr) has parent
		if( ptr->parent != NULL )
		{
			//if can move right
			if( move_next_sibling() )
			{
				move_front_leaf_node();
			}
			else
				ptr = ptr->parent;
		}
		//else, can't move to next
	}

	//move to the next sibling
	//return true if current node has a next sibling and false otherwise
	bool move_next_sibling()
	{
		//if current node has parent
		if(ptr->parent != NULL)
		{
			Minkai_Tree_Node<T>* parent_node = ptr->parent;
			vector< Minkai_Tree_Node<T>* >::iterator iter;

			//search in the parent's child list the pointer to this node
			iter = find((parent_node->child).begin(), (parent_node->child).end(), ptr);

			//move to the next child
			iter++;

			//if current node is not the youngest sibling
			if( iter != (parent_node->child).end() )
			{
				//move ptr to next sibling
				ptr = *iter;

				return true;
			}
		}

		return false;

	}
	//move to the previous sibling
	//return true if current node has a previous sibling and false otherwise
	bool move_previous_sibling()
	{
		//if current node has parent
		if(node_para->parent != NULL)
		{
			Minkai_Tree_Node<T>* parent_node = node_para->parent;
			vector< Minkai_Tree_Node<T>* >::iterator iter;

			//search in the parent's child list the pointer to this node
			iter = find((parent_node->child).begin(), (parent_node->child).end(), ptr);

			//move to the previous child
			iter--;

			//if current node is not the oldest sibling
			if( iter != (parent_node->child).rend() )
			{
				//move ptr to previous sibling
				ptr = *iter;

				return true;
			}
		}

		return false;

	}
	
	//move to the backmost leaf node
	void move_back_leaf_node()
	{
		Minkai_Tree_Node<T>* traverser = ptr;

		//while the node pointed by traverser has a child
		while( !(traverser->child).is_empty() )
		{
			//move to the back child
			traverser = (traverser->child).back();
		}

		ptr = traverser;
	}

	//move to the frontmost leaf node
	void move_front_leaf_node()
	{
		Minkai_Tree_Node<T>* traverser = ptr;

		//while the node pointed by traverser has a child
		while( !(traverser->child).is_empty() )
		{
			//move to the front child
			traverser = (traverser->child).front();
		}

		ptr = traverser;
	}

	
	//precondition: ptr != NULL
	T& get_element()
	{
		if( ptr != NULL )
		{
			return ptr->value;
		}
		else
			throw "Error!";
	}
	friend Minkai_Tree;
};

template <class T>
class Minkai_Tree
{
private:
	Minkai_Tree_Node<T>* root;
	//size of the tree, should be 0 or more
	int size;

	//precondition: subtree_root != NULL
	//postcondition: size will change accordingly
	void delete_subtree_except_root( Minkai_Tree_Node<T>* subtree_root )
	{
		if( subtree_root != NULL )
		{
			Minkai_Tree_Node<T>* traverser = subtree_root;
			Minkai_Tree_Node<T>* to_be_deleted = NULL;

			/*the while loop will delete all nodes below the root*/
			//while the root still has child
			while( !(subtree_root->child).is_empty() )
			{
				//go to the back leaf node
				traverser = get_back_leaf_node( traverser );

				to_be_deleted = traverser;
				traverser = traverser->parent;
				(traverser->child).pop_back();
				delete to_be_deleted;
				
				size--;

			}
		}
		else
			throw "Error!";
	}

	//precondition: subtree_root != NULL
	//postcondition: if subtree_root is root, root will be set to null
	//               size will change accordingly
	void delete_subtree( Minkai_Tree_Node<T>* subtree_root )
	{
		if( subtree_root != NULL )
		{
			//pointer to the parent of the root, will be set to NULL if root does not have parent
			Minkai_Tree_Node<T>* subtree_root_parent = subtree_root->parent;

			delete_subtree_except_root( subtree_root );	

			//if the root has a parent
			if( subtree_root_parent != NULL )
			{
				// *remove parent's pointer to child*
				vector< Minkai_Tree_Node<T>* >::iterator iter = (subtree_root_parent->child).begin();
				bool loop = true;

				//use a while loop to search for the pointer to the root
				while( loop )
				{
					//if the current element points to the root
					if( *iter == subtree_root )
					{
						(subtree_root_parent->child).erase( iter );
						loop = false;
					}

					iter++;
				}

			} //end if( subtree_root_parent != NULL )

			//delete the root
			delete subtree_root;
			size--;

			if(subtree_root = root)
				root = NULL;
		}
		else
			throw "Error!";
	}
	//precondition: parent_node != NULL
	//postcondition: size++
	void add_child_node( Minkai_Tree_Node<T>* parent_node, const T& value )
	{
		if( parent_node != NULL )
		{
		Minkai_Tree_Node<T>* new_node = new Minkai_Tree_Node<T>(value);
		new_node->parent = parent_node;

		parent_node->child.push_back( new_node );

		size++;
		}
	}
	//copy another tree. This will be called by copy constructor and = operator
	void copy( const Minkai_Tree<T>& obj )
	{
		root = NULL;
		size = 0;

		//copy the root node
		add_root_node( (obj.root)->value );

		Minkai_Tree_Node<T>* obj_traverser = obj.root;
		Minkai_Tree_Node<T>* this_traverser = root;

		while( obj_traverser != obj.root || (obj_traverser->child).size() != (this_traverser->child).size() )
		{
			if( (obj_traverser->child).size() != (this_traverser->child).size() )
			{
				//move obj_traverser to the first child that this_traverser doesn't have 
				obj_traverser = obj_traverser->child[(this_traverser->child).size()];
				add_child_node(this_traverser, obj_traverser->value);
				this_traverser = (this_traverser->child).back();

				/*this while loop will copy down the front child*/
				//while obj_traverser has child
				while( !(obj_traverser->child).is_empty() )
				{
					//move to the front child
					obj_traverser = obj_traverser->child[0];
					add_child_node(this_traverser, obj_traverser->value);
					this_traverser = this_traverser->child[0];
				}
			}

			obj_traverser = obj_traverser->parent;
			this_traverser = this_traverser->parent;

		}
	}
	//return a list of pointer to child of the node
	//precondition: node_ptr != NULL
	list< Minkai_Tree_Node<T>* > get_child( Minkai_Tree_Node<T>* node_ptr ) const
	{
		if( node_ptr != NULL )
		{
			//the list to be returned
			list< Minkai_Tree_Node<T>* > child_list;
			
			//loop through the vector and push each pointer into child_list
			//if node_ptr has no child then child_list will be empty
			FOR_LOOP_VECTOR( node_ptr->child )
			{
				child_list.push_back( (node->child)[index] );
			}

			return child_list;
		}
		else
			throw "Error!";
	}
	//return a list of pointer to the children of the list of node
	list< Minkai_Tree_Node<T>* > get_child( const list< Minkai_Tree_Node<T>* >& list_para ) const
	{
		list< Minkai_Tree_Node<T>* > answer;
		list< Minkai_Tree_Node<T>* >::const_iterator iter;

		for( iter = list_para.begin(); iter != list_para.end(); iter++)
		{
			//get the children of *iter and insert to the back of answer
			answer.splice( answer.end(), get_child( *iter ));
		}

		return answer;

	}
	//precondition: 1 <= level
	list< Minkai_Tree_Node<T>* > get_nodes_at_level( int level ) const
	{
		if( 1 <= level )
		{
			//holds the pointers to nodes at a level
			list< Minkai_Tree_Node<T>* > list_ptr_node(1, root);
			list< Minkai_Tree_Node<T>* > temp;
			int current_level = 1;

			//loop until reached wanted level
			while( current_level != level )
			{
				temp.clear();

				FOR_LOOP_LIST( Minkai_Tree_Node<T>*, list_ptr_node )
				{
					merge( temp, get_child( *iter ) );
				}

				list_ptr_node = temp;

				current_level++;
			}

			return list_ptr_node;
		}
		else
			throw "Error!";


		/*
		list< Minkai_Tree_Node<T>* > answer;
		Minkai_Tree_Node<T>* traverser = root;
		Minkai_Tree_Node<T>* next_sibling;
		int current_level = 1;

		traverser = get_front_leaf_node( traverser );

		while(next_sibling != NULL)
		{
		next_sibling = get_next_sibling( traverser );
		}

		if( current_level == level )
		{
		answer.push_back( traverser );
		}
		*/
	}

public:
	//auto initialize to root node
	Minkai_Tree_Marker marker;

	//constructor
	Minkai_Tree() : marker()
	{
		root = NULL;
		size = 0;
	}
	//copy constructor
	Minkai_Tree( const Minkai_Tree& obj ) : marker()
	{
		copy( obj );
	}
	//destructor
	~Minkai_Tree()
	{
		clear();
	}
	//precondition: tree is empty
	void add_root_node( const T& value )
	{
		if( root == NULL )
		{
			root = new Minkai_Tree_Node<T>( value );

			marker.ptr = root;

			size++;
		}
	}

	//precondition: tree is not empty
	void add_child_node_at_marker( const T& value )
	{
		if( !is_empty() )
		{
			add_child_node( marker.ptr, value );
		}
	}
	
	//precondition: tree is not empty
	//postcondition: subtree at marker will be deleted and 
	//marker moves to parent of the root of the subtree
	void delete_subtree_at_marker()
	{
		if( !is_empty() )
		{
			Minkai_Tree_Node<T>* temp = marker.ptr;
			marker.ptr = (marker.ptr)->parent;

			delete_subtree( temp );
		}
	}
	
	//empties the tree
	//marker is set to NULL
	void clear()
	{
		delete_subtree( root );

		marker.ptr = NULL;
	}
	
	Minkai_Tree operator=( const Minkai_Tree& obj )
	{
		copy( obj );

		return (*this);
	}

	int get_size() const
	{
		return size;
	}
	//get the deepest level
	//returns 0 is tree is empty
	int get_deepest_level() const
	{
		//if this tree is empty
		if( is_empty() )
		{
			return 0;
		}
		else
		{
			//create a list with one element(pointing to the root node)
			list< Minkai_Tree_Node<T>* > list_ptr_node(1, root);
			int current_level = 1;

			do
			{
				//move to the next level
				list_ptr_node = get_child( list_ptr_node );

				current_level++;
			}while( !(list_ptr_node.empty()) );

			//last level is empty, so return current_level-1
			return current_level-1;
		}
	}
	bool is_empty() const
	{
		if( size == 0 )
			return true;
		else
			return false;
	}
	
	
	
	//display the tree but does not show the parent-child relationship
	//under construction!
	void display() const
	{
		Minkai_Table<T> obj( );

	}

	
	
};

#endif
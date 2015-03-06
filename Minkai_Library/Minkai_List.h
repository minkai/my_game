//base class for Minkai_List_Node1 and Minkai_List_Node2
template <class T>
class Minkai_List_Node
{
public:
	//constructor
	Minkai_List_Node()
	{
	}
	virtual ~Minkai_List_Node()
	{
	}

	//pure virtual function
	virtual void set_value(const T& value_para) = 0;
};

template <class T>
class Minkai_List_Node1 : public Minkai_List_Node<T>
{
private:
	T value;
	
public:
	Minkai_List_Node1* previous;
	Minkai_List_Node1* next;

	//constructor
	Minkai_List_Node1(const T& value_para)
	{
		previous = NULL;
		next = NULL;

		value = value_para;
	}
	virtual void set_value(const T& value_para)
	{
		value = value_para;
	}
};

//similar to Minkai_List_Node1, except that value is dynamically created
template <class T>
class Minkai_List_Node2 : public Minkai_List_Node<T>
{
private:
	//a pointer to the value (dynamically created)
	T* value_ptr;

public:
	Minkai_List_Node2* previous;
	Minkai_List_Node2* next;

	//constructor
	Minkai_List_Node2(const T& value_para)
	{
		previous = NULL;
		next = NULL;

		value_ptr = new T(value_para);
	}

	//destructor
	~Minkai_List_Node2()
	{
		delete value_ptr;
		value_ptr = NULL;
	}
	virtual void set_value(const T& value_para)
	{
		value = value_para;
	}
};

//Minkai's list class
//class N must be Minkai_List_Node1<T> or Minkai_List_Node2<T>
template <class N, class T>
class Minkai_List
{
private:
	N* head;
	N* tail;

	int size;

	//assume the list is empty and add the first node
	void add_first_node(const T& value)
	{
		N* new_node = new N(value);

		head = tail = new_node;

		//set the new node's next and previous pointers
		new_node->previous = NULL;
		new_node->next = NULL;

		size++;
	}

	//copy the contents of another Minkai_List
	//called by the copy constructor and operator= only
	void copy( const Minkai_List<N, T>& obj )
	{
		clear();

		//push back the contents of obj
		for(int count = 1; count <= obj.get_size(); count++)
		{
			push_back( obj[count-1] );
		}
	}

public:
	//constructor
	//precondition: 0 <= size
	Minkai_List( int size_para = 0, const T& value = T() )
	{
		if( 0 <= size_para )
		{
			head = NULL;
			tail = NULL;

			//add node to the back of the list
			for(int count = 1; count <= size_para; count++)
			{
				push_back(value);
			}

			//initialize size
			size = size_para;
		}
		else
			throw "Error!";
	}
	//copy constructor
	Minkai_List( const Minkai_List<N, T>& obj )
	{
		head = NULL;
		tail = NULL;

		size = 0;

		copy( obj );
		
	}
	//destructor
	~Minkai_List()
	{
		clear();
	}
	//push a new node to the front of the list
	void push_front(const T& value)
	{
		//if the list is empty
		if( head == NULL )
		{
			add_first_node(value);	
		}
		else
		{
			N* new_node = new N(value);

			head->previous = new_node;

			//set the new node's next and previous pointers
			new_node->previous = NULL;
			new_node->next = head;

			head = new_node;

			size++;
		}
	}
	//add a new node to the end of the list
	void push_back(const T& value)
	{
		//if the list is empty
		if( tail == NULL )
		{
			add_first_node(value);	
		}
		else
		{
			N* new_node = new N(value);

			tail->next = new_node;

			//set the new node's next and previous pointers
			new_node->previous = tail;
			new_node->next = NULL;

			//the new node becomes the tail
			tail = new_node;

			size++;
		}
	}
	//delete the first element
	void pop_front()
	{
		if( !is_empty() )
		{
			N* to_be_deleted = head;

			//move head forward
			head = head->next;

			delete to_be_deleted;

			//if list is not empty
			if( head != NULL )
				head->previous = NULL;
			else
				tail = NULL;

			//update size
			size--;
		}
	}
	//delete the last element
	void pop_back()
	{
		if( !is_empty() )
		{
			N* to_be_deleted = tail;

			//move tail back one step
			tail = tail->previous;

			delete to_be_deleted;

			//if list is not empty
			if( tail != NULL )
				tail->next = NULL;
			else
				head = NULL;

			//update size
			size--;
		}
	}
	bool is_empty() const
	{
		if( size == 0 )
			return true;
		else
			return false;
	}
	int get_size() const
	{
		return size;
	}
	//access the front element
	//precondition: list is not empty
	T& front()
	{
		if( head != NULL )
		{
			return head->value;
		}
		else
			throw "Error!";
	}
	//access the back element
	//precondition: list is not empty
	T& back()
	{
		if( tail != NULL )
		{
			return tail->value;
		}
		else
			throw "Error!";
	}
	Minkai_List<N, T> operator=(const Minkai_List<N, T>& obj)
	{
		copy(obj);

		return (*this);
	}
	//precondition: 0 <= index <= size-1
	T& operator[](int index)
	{
		if( 0 <= index && index <= size-1 )
		{
			N* traverser = head;

			//move forward by index
			for(int count = 1; count <= index; count++)
			{
				traverser = traverser->next;
			}

			return traverser->value;
		}
		else
			throw "Error!";
	}
	const T& operator[](int index) const
	{
		if( 0 <= index && index <= size-1 )
		{
			N* traverser = head;

			//move forward by index
			for(int count = 1; count <= index; count++)
			{
				traverser = traverser->next;
			}

			return traverser->value;
		}
		else
			throw "Error!";
	}
	//empty the entire list
	void clear()
	{
		//use the tail pointer and work backwards
		while( tail != NULL )
		{
			N* to_be_deleted = tail;

			//move tail back
			tail = tail->previous;

			//for debugging purpose
			//cout << "Deleting list node with element: " << to_be_deleted->value << endl;
			
			delete to_be_deleted;
		}
	}
	//display content of the list using cout
	void display() const
	{
		for(int count = 1; count <= size; count++)
		{
			cout << operator[](count-1) << " ";
		}
	}
};

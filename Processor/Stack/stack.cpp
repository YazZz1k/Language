#include"stack.hpp"


Stack::Stack()
{
    size = STACK_SIZE;
    ptr  = 0;

    arr  = (int*)malloc(sizeof(int)*size);
    if(!arr){printf("Memmory Error\n"); exit(1);}
}


Stack::Stack(int len, ...)
{
    size = STACK_SIZE;
    ptr  = 0;

    arr  = (int*)malloc(sizeof(int)*size);
    if(!arr){printf("Memmory Error\n"); exit(1);}

    int* arr = &len;
    for(int i=0; i<len; i++)
    {
        arr++;
        push(*arr);
    }
}


Stack::Stack(const Stack& st)
{
    ptr  = st.ptr;
    size = st.size;

    arr = (int*)malloc(sizeof(int)*size);

    for(int i=0; i<ptr+1; i++)
        arr[i] = st.arr[i];
}


Stack::Stack(int* get_arr, int len)
{
    size = STACK_SIZE;
    ptr  = 0;

    arr  = (int*)malloc(sizeof(int)*size);
    if(!arr){printf("Memmory Error\n"); exit(1);}

    for(int i=0; i<len; i++)
        push(get_arr[i]);
}

Stack::~Stack()
{
    free(arr);
    size = 0;
}


void Stack::push(int new_el)
{
    if(size == ptr+1)
    {
        size = 2*size;
        arr  = (int*)realloc(arr, size*sizeof(int));

        if(!arr){printf("Memmory Error\n"); exit(1);}
    }

    arr[ptr++] = new_el;
}


int Stack::get()
{
    if(ptr)
        return arr[ptr];
    else
    {
        printf("Empty Stack function get() return -1\n");
        return -1;
    }

}


int Stack::pop()
{
    if(ptr)
        return arr[--ptr];
    else
    {
        printf("Empty Stack function pop() return -1\n");
        return -1;
    }
}


bool Stack::is_empty()
{
    return !ptr;
}


int Stack::get_size()
{
    return ptr;
}


void Stack::do_empty()
{
    ptr = 0;

    if(size!=STACK_SIZE)
    {
        size = STACK_SIZE;
        free(arr);
        arr = (int*)malloc(sizeof(int)*size);
    }
}


bool Stack::pop_two_elements(int& fi, int& se)
{
    if(!is_empty())
    {
        fi = pop();
        if(!is_empty())
        {
            se = pop();
            return true;
        }
        else
        {
            printf("There are not enough items in the stack\n");
            assert(0);
        }
    }
    else
    {
        printf("There are not enough items in the stack\n");
        assert(0);
    }

    return false;
}


void Stack::sub()
{
    int fi,se;
    if(pop_two_elements(fi,se))
        push(se-fi);
}


void Stack::add()
{
    int fi,se;
    if(pop_two_elements(fi,se))
        push(fi+se);
}


void Stack::mul()
{
    int fi,se;
    if(pop_two_elements(fi,se))
        push(fi*se);
}


void Stack::div()
{
    int fi,se;
    if(pop_two_elements(fi,se))
        push(fi/se);
}


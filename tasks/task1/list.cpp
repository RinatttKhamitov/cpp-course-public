#include "list.h"


List::List()
{
    first = nullptr;
    last = nullptr;
}


bool
List::is_empty()
{
    return (first == nullptr);
}


void
List::clear()
{
    if(is_empty())
        return;
    while(first != nullptr){
        remove_back();
    }
}



void
List::push_front(int _val)
{
    Node* newNode = new Node(_val);
    if(is_empty()){
        first = newNode;
        last = newNode;
        return;
    }
    newNode->next = first;
    first = newNode;
}


void
List::push_back(int _val)
{
    Node* newNode = new Node(_val);
    if(is_empty()){
        first = newNode;
        last = newNode;
        return;
    }
    last->next = newNode;
    last = newNode;
}


Node*
List::find(int _val)
{
    if (is_empty()){
        return;
    }
    Node* current = first;
    while (current != nullptr){
        if(current->val == _val){
            return current;
        }
        current = current->next;
    }
    return current;
}


void
List::remove_front()
{
    if (is_empty()){
        return;
    }
    if (first == last){
        first = nullptr;
        last = nullptr;
        return;
    }
    Node* del = first;
    first = first->next;
    delete del;

}


void
List::remove_back()
{
    if (is_empty())
        return;
    if(first == last){
        first = nullptr;
        last = nullptr;
        return;
    }
    Node* current = first; 
    
    while (current->next->next != nullptr)
        current = current->next;

    current->next = nullptr;
    last = current;
}


bool
List::remove(const Node* _node)
{
    if(is_empty() || _node == nullptr || find(_node->val) == nullptr)
        return false;
        
    if(_node == first){ 
        remove_front();
        return true;
    }
    if(_node == last){
        remove_back();
        return true;
    } 
    Node* current = first;
    Node* foundNode = current->next;
    while(current->next != _node)
        current = current->next;
        
    current->next = _node->next;
    delete foundNode;
    return true;
}

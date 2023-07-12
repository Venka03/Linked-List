#include <iostream>
#include <type_traits>
#include <list>
#include <vector>

using namespace std;

template <typename T>
struct Node {
    T value;
    Node<T>* next;
};

template <typename T>
class LinkedList{
private:
    Node<T> *first;
public:
    LinkedList(){
        first = NULL;
    }
    LinkedList(list<T> lst){
        first = NULL;
        for (T el: lst)
            push_back(el);
    }
    LinkedList(vector<T> vec){
        first = NULL;
        for (int i=0; i<vec.size(); i++)
            push_back(vec[i]);
    }
    void set_first(T element){
        // give memory position to the first element and set it's value
        if (is_empty()){
            first = new Node<T>;
            first->value = element;
        }  
    }
    T get_first(){ return first->value;} // return first element
    void push_front(T element){
        // add element at the beginning of linked list and move all elements by one
        if (!first)
            set_first(element);
        else {
            Node<T> *tmp = new Node<T>;
            T val = first->value;
            T val_tmp;
            first->value = element;
            tmp = first;
            while (tmp->next){
                tmp = tmp->next;
                val_tmp = tmp->value;
                tmp->value = val;
                val = val_tmp;
            }
            Node<T> *last = new Node<T>;
            last->value = val;
            tmp->next = last;
        }
        
    }
    void push_back(T element) {
        // add element to the end of linked list
        if (!first)
            set_first(element);
            
        else {
            Node<T> *tmp = new Node<T>;
            tmp = first;
            while (tmp->next)
                tmp = tmp->next;
            Node<T> *last = new Node<T>;
            last->value = element;
            tmp->next = last;
        }
    }
    void print_all(){
        // print all elements of linked list separating them with whitespace
        if (!is_empty()){
            Node<T> *tmp = new Node<T>;
            tmp = first;
            cout << tmp->value << ' ';
            while (tmp->next){
                tmp = tmp->next;
                cout << tmp->value << ' ';
            }
        }
    }
    int size(){
        // return number of elements in linked list
        if (is_empty()) return 0;
        int c = 1;
        Node<T> *tmp = new Node<T>;
        tmp = first;
        while (tmp->next){
            c++;
            tmp = tmp->next;
        }
        return c;
    }
    void delete_first(T element){
        // delete first appearance of certain element
        if (!is_empty() && contain(element)){
            Node<T> *tmp = new Node<T>;
            tmp = first;
            bool found = false;
            while (tmp->next){
                if (found || tmp->value == element){
                    found = true;
                    tmp->value = tmp->next->value;
                    if (!tmp->next->next){
                        tmp->next = NULL;
                        break;
                    }
                }
                if (tmp->next->value == element && !tmp->next->next){
                    tmp->next = NULL;
                    break;
                }
                tmp = tmp->next;
            }
            if (!first->next && first->value==element){
                first = NULL;
            }
        }
    }
    void delete_last(T element){
        // delete last appearance of a certain element
        if (!is_empty() && contain(element)){
            Node<T> *tmp = new Node<T>;
            tmp = first;
            Node<T> *last = new Node<T>;
            if (tmp->value == element) last = tmp;
            if (first->next){
                while (tmp->next->next){
                    tmp = tmp->next;
                    if (tmp->value == element) last = tmp;
                }
                if (tmp->next->value == element){
                    tmp->next = NULL;
                }
                else if (last){
                    tmp = last;
                    tmp->value = tmp->next->value;
                    while (tmp->next->next){
                        tmp = tmp->next;
                        tmp->value = tmp->next->value;
                    }
                    tmp->next = NULL;
                }
            }
            else if (first->value == element) first = NULL;
        }
    }
    void delete_all(T element){
        // delete all appearances of a certain element
        while (contain(element))
            delete_first(element);
    }
    int count(T element){
        // return number of appearances of a certain element
        int c = 0;
        Node<T> *tmp = new Node<T>;
        tmp = first;
        if (first->value == element) c++;
        while (tmp->next){
            tmp = tmp->next;
            if (tmp->value == element)
                c++;
        }
        return c;
    }
    bool is_empty(){ return !first;} // return true if linked list has no elements, otherwise true
    bool contain(T element){ return count(element);} // state if linked list contains a certain element
    void concatenate(LinkedList<T> lst){
        // add to the end of current linked list, elements of a given one
        Node<T> *tmp1 = new Node<T>;
        tmp1 = first;
        while (tmp1->next)
            tmp1 = tmp1->next;
        Node<T> *tmp2 = lst.first;
        push_back(tmp2->value);
        while (tmp2->next){
            tmp2 = tmp2->next;
            push_back(tmp2->value);
        }
    }
    void delete_it(){
        Node<T> *tmp1 = first;
        Node<T> *tmp2 = new Node<T>;
        tmp2 = tmp1->next;
        while (tmp1->next){
            delete tmp1;
            Node<T> *tmp1 = tmp2;
            tmp2 = tmp1->next;
        }
        delete tmp1;
        delete tmp2;
    }
};

int main(){
    try {
        LinkedList<int> lst;
        {
            lst.set_first(2);
            lst.push_back(1);
            lst.push_front(7);
            lst.push_back(-1);
            lst.push_back(-21);
            lst.push_front(22);
            lst.push_front(13);
            lst.push_back(-1);
            lst.push_back(0);
            lst.push_front(2);
            lst.push_back(8);
            lst.push_back(7);
            lst.push_front(0);
            lst.push_back(-1);
            lst.push_front(121);
            lst.push_front(39);
            lst.push_front(4);
        }
        
        cout << "All elements of this linked list:\n";
        lst.print_all();
        cout << "\nThere are " << lst.count(-1) << " elements -1 in this linked list\n";

        lst.delete_first(7);
        cout << "After deleting first appearance of 7:\n";
        lst.print_all();
        lst.delete_last(0);
        cout << "\nAfter deleting last appearance of 0:\n";
        lst.print_all();
        lst.delete_all(-1);
        cout << "\nAfter deleting all appearances of -1:\n";
        lst.print_all();
        cout << endl;
        
        list<int> test_list;
        test_list.push_back(-1);
        test_list.push_back(2);
        test_list.push_front(9);
        test_list.push_back(4);
        LinkedList<int> lst2 (test_list);
        cout << "Linked list from list:\n";
        lst2.print_all();
        cout << endl;
        
        vector<int> test_vec;
        test_vec.push_back(13);
        test_vec.push_back(-12);
        test_vec.push_back(-23);
        test_vec.push_back(1);
        LinkedList<int> lst3 (test_vec);
        cout << "Linked list from vector:\n";
        lst3.print_all();
        cout << endl;

        lst2.concatenate(lst3);
        lst.concatenate(lst2);
        cout << "Concatenation of linked lists:\n";
        lst.print_all();
        cout << endl;

        lst.delete_all(2);
        cout << "After deleting all appearances of 2:\n";
        lst.print_all();
        cout << endl;
        
    }
    catch (exception *e){
        cout << e->what();
    }
    
    
    
    return 0;
}
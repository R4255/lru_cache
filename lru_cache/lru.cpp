#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;
//node to store the data(linked list)
class Node{
    public:
        string key;
        int value;
        Node(string key,int value){
            this->key=key;
            this->value=value;
        }
};
//LRU Cache data structure
class LRUCache{
public:
    int maxsize;
    list<Node> l;//list mean doubly list and forward list mean linked list in cpp
    unordered_map<string,list<Node>::iterator>m;
    LRUCache(int maxsize){
        this->maxsize=maxsize>1?maxsize:1;  
    }
    void insertkeyvalue(string key,int value){
        //2 case
        if(m.count(key)!=0){
            //replace the old value with the new one
            auto it=m[key];
            it->value=value;
        }
        else{
            //check if cache is full or not
                //then remove the least recently used item from the cache
            if (l.size()==maxsize){
                Node last=l.back();
                m.erase(last.key);//remove from hashmap
                l.pop_back();//remove from ll 
            }
            Node n(key,value);
            l.push_front(n);
            m[key]=l.begin();
        }
    }
    int *getvalue(string key){
        if(m.count(key)!=0){
            auto it=m[key];
            int value=it->value;
            l.push_front(*it);//* pointer gives us the value in it (bucket)
            l.erase(it);
            m[key]=l.begin();
            return &l.begin()->value;
        }
        return NULL;
    }
    string mostrecentkey(){
        return l.front().key;
    }
};
int main(){
    LRUCache lru(3);
    lru.insertkeyvalue("mango",10);
    lru.insertkeyvalue("apple",20);
    lru.insertkeyvalue("guava",30);
    cout<<lru.mostrecentkey()<<endl;
    lru.insertkeyvalue("mango",40);
    cout<<lru.mostrecentkey()<<endl;
    lru.insertkeyvalue("banana",20);
    cout<<lru.mostrecentkey()<<endl;
    if(lru.getvalue("apple")==NULL){
        cout<<"apple doesnot exist";
    }
    if(lru.getvalue("guava")==NULL){
        cout<<"guava doesnot exist";
    }
    if(lru.getvalue("mango")==NULL){
        cout<<"mango doesnot exist";
    }
    return 0;
}
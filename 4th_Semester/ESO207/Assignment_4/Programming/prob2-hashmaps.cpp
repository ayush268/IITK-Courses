#include <iostream>
#include <string>
using namespace std;

class node
{
    private:
        string str;
        unsigned count;
        node *next;
        friend class hashTable;

    public:
        node(string key)
        {
            str = key;
            count = 1;
            next = NULL;
        }
};

class hashTable
{
    private:
        unsigned size;
        node *max;
        node **table;

        unsigned hashFunction(string str)
        {
            unsigned hash = 5381; // Initial integer

            for(int i=0; str[i] != '\0'; i++)
                hash = hash * 33 + str[i];        // The magic of number 33 makes it a good hash function.
            
            return hash % 100003;
        }


    public:
        hashTable()
        {
            size = 100003;
            max = NULL;
            table = new node* [size];
            for(unsigned i=0;i<size;i++)
                table[i] = NULL;
        }

        ~hashTable()
        {
            node *curr;
            node *next;
            for(unsigned i=0;i<size;i++)
            {
                curr = table[i];
                while(curr != NULL)
                {
                    next = curr->next;
                    delete curr;
                    curr = next;
                }
            }
            delete [] table;
        }

        void add(string key)
        {
            unsigned hash = hashFunction(key);
            if(table[hash] == NULL)
            {
                table[hash] = new node(key);
                if(max == NULL)
                    max = table[hash];
            }
            else
            {
                node *curr = table[hash];
                while(curr->next != NULL && curr->str != key)
                    curr = curr->next;
                if(curr->str == key)
                {
                    curr->count += 1;
                    if(max == NULL || max->count < curr->count)
                        max = curr;
                }
                else
                {
                    node* tmp = new node(key);
                    if(max == NULL)
                        max = tmp;
                    curr->next = tmp;
                }
            }
        }

        string getMax()
        {
            if(max == NULL)
                return "No element!";
            return max->str;
        }

};

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n;
    string str;
    cin >> n;
    hashTable *t = new hashTable();
    while(n--)
    {
        cin >> str;
        t->add(str);
    }
    cout << t->getMax() << endl;
    delete t;
    return 0;
}

#include <string>
#include <functional>
using namespace std;

//typedef void (* consumer)(string args);
//typedef void (* pairconsumer)(string args, int gen);

typedef std::function< void(string) > consumer;
typedef std::function< void(string, int) > pairconsumer;

class BinarySearchTree {
   friend std::ostream &operator<<(std::ostream &, const BinarySearchTree &);
    public:
        using Key = int;
        using Item = std::string;
        void insert(Key, Item); 
        Item* lookup(Key);
        BinarySearchTree();
        void preOrder(pairconsumer);
        void inOrder(consumer);
        void postOrder(consumer);

    private:
        class StreamHelper;
        struct Node;
        Node* root;
        static void insertRecursive(Key, Item, Node*);
        static Item* lookupRecursive(Key, Node*);
        static void preOrderRecursive(pairconsumer con, Node* nodePtr, int);
        static void inOrderRecursive(consumer, Node*);
        static void postOrderRecursive(consumer, Node*);
};

std::ostream &operator<<(std::ostream &, const BinarySearchTree &);

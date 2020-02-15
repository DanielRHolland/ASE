#ifndef ASECOURSEWORK_DICTIONARY_H
#define ASECOURSEWORK_DICTIONARY_H

#include <functional>

namespace Containers {
    template <class K, class I>
    class Dictionary {
    public:
        using Key = K;// ... must support at least std::string
        using Item = I;// ... must support at least std::string
        typedef std::function<bool(K)> Predicate;
        Dictionary();

        bool insert(Key, Item);

        Item *lookup(Key);

        bool remove(Key);

        int removeIf(Predicate);

    private:

    };

    template <class K, class I>
    Dictionary<K,I>::Dictionary(){

    }

    template<class K, class I>
    bool Dictionary<K, I>::insert(Key, Item) {
        return false;
    }

    template<class K, class I>
    I* Dictionary<K, I>::lookup(Key) {
        return nullptr;
    }

    template<class K, class I>
    bool Dictionary<K, I>::remove(Key) {
        return false;
    }

    template<class K, class I>
    int Dictionary<K, I>::removeIf(Predicate) {
        return 0;
    }
}


#endif //ASECOURSEWORK_DICTIONARY_H

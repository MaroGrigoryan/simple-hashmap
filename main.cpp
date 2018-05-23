#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

unsigned int myhash(const string& key) {
    int h = 0;
    for (int i = 0; i < key.size(); ++i) {
        h = 257 * h + key[i];
    }
    return h;
}

unsigned int myhash(const int& key) {
    return key * 10000001;
}

template<class Key, class Value>
class HashMap {
public:

    HashMap() {
        H.resize(2003);
    }

    void insert(const Key& key, const Value& value) {
        int h = myhash(key) % H.size();

        while (H[h] != nullptr) {
            h = myhash(h) % H.size();
        }
        ++size;
        H[h] = make_shared<pair<Key, Value>>(key, value);

        if (H.size() / size < 3) {
            // rehash everything.
            // 1 point for implementing the re-hashing, hash table expansion.

            int prev_size = H.size();
            H.resize(prev_size * 3);      // resize it
            for (int i = 0; i < prev_size; ++i) {  // transfer the  neccessary elemets from the initial hashtable
                int check = myhash(H[i]->first) % H.size();
                while (H[check] != nullptr) {
                    check = myhash(check) % H.size();
                    H[check] = make_shared<pair<Key, Value>>(H[i]->first, H[i]->second);
                }
            }

        }
    }

    // Returns value in out parameter value_out
    bool find(Key key, Value* value_out) {
        int h = myhash(key) % H.size();

        while (H[h] != nullptr) {
            if (H[h]->first == key) {
                *value_out = H[h]->second;
                return true;
            }
            h = myhash(h) % H.size();
        }
        return false;
    }

    // Returns true if found.
    bool erase(const Key& key) {
        // 1 point for implementing this function correctly. NOTE: you can not actually just set the item to null,
        // because the item must be replaced by the last item in the chain.

        int h = myhash(key) % H.size();

        while (H[h] != nullptr) {
            if(H[h]->first == key){
                int found = h;
                int last = myhash(h) % H.size();
                while (H[last] != nullptr) {
                    h = last;
                    last = myhash(last) % H.size();
                }
                H[found] = H[h];
                H[h] = nullptr;
                size--;

                return true;
            }
        }
        return false;
    }

private:

    int size; // N
    // The hashmap.
    vector<shared_ptr<pair<Key, Value>>> H;
};


int main() {
    HashMap<string, string> M;
    M.insert("AH051463", "Martun");
    M.insert("AK051483", "Valod_2");
    string valod_str;
    if (M.find("AK051483", &valod_str)) {
        cout << "Valod was found, here he is: "
             << valod_str << endl;
    }
    M.erase("AK051483");
    if (!M.find("AK051483", &valod_str)) {
        cout <<valod_str<< "  is dead." << endl;
    }
    return 0;
}
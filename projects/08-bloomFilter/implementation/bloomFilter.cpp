#include <iostream>
#include <vector>

uint64_t FNV_prime = 0x100000001b3;
// Typically the seed is 0xcbf29ce484222325, but for our purposes it should be ok to be custom values?
// Should verify this
uint64_t fnv1a_hash(std::string data, uint64_t seed) {
    uint64_t hash = seed;
    for (char c : data) {
        hash = hash ^ c; // xor
        hash = hash * FNV_prime; // multiply by the FNV prime
    }

    return hash;
}

class BloomFilter {
    std::vector<bool> bit_array;
    int hash_functions;
    uint64_t seed1 = 0xcbf29ce484222325; // FNV-1a seed
    uint64_t seed2 = 0xdeadbeef; // kekw

public:
    BloomFilter(int bits, int hash_functions) {
        this->bit_array = std::vector(bits, false);
        this->hash_functions = hash_functions;
    }

    void add(const std::string& str) {
        uint64_t hash1 = fnv1a_hash(str, seed1);
        uint64_t hash2 = fnv1a_hash(str, seed2);

        // Double hashing to generate more hash functions
        for (uint64_t i = 0; i < hash_functions; i++) {
            uint64_t index = (hash1 + i * hash2) % bit_array.size();
            bit_array[index] = true;
        }
    }

    // Checks if an element is possibly in the set
    bool contains(const std::string& element) const {
        uint64_t hash1 = fnv1a_hash(element, seed1);
        uint64_t hash2 = fnv1a_hash(element, seed2);

        for (uint32_t i = 0; i < hash_functions; ++i) {
            size_t index = (hash1 + i * hash2) % bit_array.size();
            if (!bit_array[index]) {
                return false;
            }
        }
        return true; // could be a false positive though
    }


};

int main() {
    // Example: 1000 bits, 7 hash functions
    BloomFilter filter(1000, 7);

    filter.add("hello");
    filter.add("world");

    std::cout << std::boolalpha;
    std::cout << "Contains 'hello': " << filter.contains("hello") << std::endl;
    std::cout << "Contains 'amogus': " << filter.contains("amogus") << std::endl;

    filter.add("amogus");
    std::cout << "Contains 'amogus': " << filter.contains("amogus") << std::endl;

    filter.add("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    std::cout << "Contains the lorem ipsum stuff: " << filter.contains("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.") << std::endl;

    std::cout << "Contains 'Lorem': " << filter.contains("Lorem") << std::endl;

    return 0;
}
#include <string>
#include <random>

namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________Hashable

    template<>
    class Hashable<int> {

        public:
        
            ulong operator()(const int& d) const noexcept { return d * d; }
    };




    template<>
    class Hashable<double> {

        public:
        
            ulong operator()(const double& d) const noexcept {

                long intg = floor(d);
                long frct = pow(2, 24) * (d - intg);
                return intg * frct;
            }
    };




    template<>
    class Hashable<std::string> {

        public:
        
            ulong operator()(const std::string& d) const noexcept {

                ulong encashed = 5381;
                
                for (ulong i = 0; i < d.length(); i++) {
                    
                    encashed = (encashed << 5) + d[i];
                }
                
                return encashed;
            }
    };





//_________________________________________________________________________
//_________________________________________________________________________HashTable

    template <typename Data>
    HashTable<Data>& HashTable<Data>::operator=(const HashTable& ht) {

        size = ht.size;
        htsize = ht.htsize;
        acff = ht.acff;
        bcff = ht.bcff;
        
        return *this;
    }


    template <typename Data>
    HashTable<Data>& HashTable<Data>::operator=(HashTable&& ht) noexcept {

        std::swap(size, ht.size);
        std::swap(acff, ht.acff);
        std::swap(bcff, ht.bcff);
        std::swap(htsize, ht.htsize);

        return *this;
    }




    template <typename Data>
    ulong HashTable<Data>::HashKey(const Data& d) const noexcept {

        return ((
            
            acff * (encash(d)) + bcff
            
        ) % prime) % htsize;
    }



    template <typename Data>
    void HashTable<Data>::setRandCff() {

        std::default_random_engine rand = std::default_random_engine(std::random_device{}());
        std::uniform_int_distribution<ulong> rangea = std::uniform_int_distribution<ulong>(1, prime - 1);
        std::uniform_int_distribution<ulong> rangeb = std::uniform_int_distribution<ulong>(0, prime - 1);

        acff = rangea(rand);
        bcff = rangeb(rand);
    }



    template <typename Data>
    ulong HashTable<Data>::rup2(ulong n) noexcept {

        ulong msb = 0;

        if ((n & (n - 1)) == 0) { return n; }

        while (n != 0) {

            n >>= 1;
            msb++;
        }

        return 1 << msb;
    }
}
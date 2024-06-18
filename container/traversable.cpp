namespace lasd {

//_________________________________________________________________________
//_________________________________________________________________________TraversableContainer

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const {
        
        Traverse([fun, &acc](const Data& d) {  acc = fun(d, acc); });
        return acc;
    }



    template <typename Data>
    inline bool TraversableContainer<Data>::Exists(const Data& val) const noexcept {
        
        bool exists = false;
        Traverse([val, &exists](const Data& d) { exists |= (d == val); });
        return exists;
    }
    
    



//_________________________________________________________________________
//_________________________________________________________________________X-TraversableContainer

    template<typename Data>
    template<typename Accumulator>
    inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
        
        PreOrderTraverse([fun, &acc](const Data& d) { acc = fun(d, acc); });
        return acc;
    }

    

    template<typename Data>
    template<typename Accumulator>
    inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
        
        PostOrderTraverse([fun, &acc](const Data& d) { acc = fun(d, acc); });
        return acc;
    }

    

    template<typename Data>
    template<typename Accumulator>
    inline Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
        
        InOrderTraverse([fun, &acc](const Data & d) { acc = fun(d, acc); });
        return acc;
    }

    

    template<typename Data>
    template<typename Accumulator>
    inline Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> fun, Accumulator acc) const {
        
        BreadthTraverse([fun, &acc](const Data & d) { acc = fun(d, acc); });
        return acc;
    }
}
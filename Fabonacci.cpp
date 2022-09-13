#include <iostream>
template<std::size_t ...Index> struct Content{};

template<std::size_t Count, class T>
struct FibonacciSequence{
    using type = typename FibonacciSequence<Count - 1, Content<1,0>>::type;
};
template<std::size_t Count, std::size_t N,std::size_t N2, std::size_t ...Index>
struct FibonacciSequence<Count, Content<N, N2, Index...>>{
    using type = typename FibonacciSequence<Count - 1, Content<N + N2, N,N2, Index...>>::type;
};
template<std::size_t N,std::size_t N2, std::size_t ...Index>
struct FibonacciSequence<0, Content<N, N2, Index...>>{
    using type = Content<N, N2, Index...>;
};
template<class T, class New>
struct RevertContent;
template<std::size_t N, std::size_t N1,std::size_t...Index, std::size_t...Index2>
struct RevertContent<Content<N,N1, Index...>, Content<Index2...>>{
    using type = typename RevertContent<Content<Index...>, Content<N1,N,Index2...>>::type;
};
template<std::size_t...Index2>
struct RevertContent<Content<>,Content<Index2...>>{
    using type = Content<Index2...>;
};
int main(){
    using t = FibonacciSequence<5,Content<>>::type;
    using r = RevertContent<t,Content<>>::type;
    std::cout<< typeid(r).name();
}

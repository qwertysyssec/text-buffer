#ifndef UUID_FE4B06CE_C7FC_43E5_B16B_1D9575193170
#define UUID_FE4B06CE_C7FC_43E5_B16B_1D9575193170

#include <cstddef>
#include <iterator>
namespace tb {

 template<typename T>
    class text_buffer {

      public:

        void LEFT();

        void RIGHT();

        void DELETE();

        void INSERT(typename T::value_type in);

        std::size_t SIZE();

    private:

        T structure_;
        typename T::iterator iter=structure_.begin();
    };


/**************IMPLEMENTATION**************/


    template<typename T>
    inline void text_buffer<T>::LEFT(){
         if (iter!=structure_.begin()) --iter;
    };

    template<typename T>
    inline void text_buffer<T>::RIGHT(){
        if (iter!=structure_.end()) ++iter;
    };

    template<typename T>
    inline void text_buffer<T>::DELETE(){
        if (iter!=structure_.end()) iter=structure_.erase(iter);
    };

    template<typename T>
    inline void text_buffer<T>::INSERT(typename T::value_type in){
        iter=std::next(structure_.emplace(iter, in));

    };

    template<typename T>
    inline std::size_t text_buffer<T>::SIZE(){
        return structure_.size();

    };
}


#endif // TEXT_BUFFER_HPP

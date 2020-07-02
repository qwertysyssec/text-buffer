
#include "text_buffer.hpp"
#include <benchmark/benchmark.h>
#include <cstddef>
#include <random>
#include <deque>
#include <list>

//Lizgin Vsevolod, SCS181, Containers, Ex. 3

    class RAII_benchmark{

        benchmark::State& state_;

    public:

        explicit RAII_benchmark (benchmark::State& state):state_(state){
            state_.ResumeTiming();
        }

        ~RAII_benchmark (){

            state_.PauseTiming();
        }
    };

    template<typename not_benchmarked, typename benchmarked>
    void TIMER(benchmark::State& state, std::size_t n, not_benchmarked lambda_1, benchmarked lambda_2){
        for(std::size_t i=0; i<n; ++i){
        lambda_1();
        RAII_benchmark on(state);
        lambda_2();
        }
    }




    template<typename T>
        static void BM_TEST(benchmark::State& state){

            std::mt19937_64 prng;
            std::uniform_int_distribution<unsigned char> ch_dist(0, 255);
            std::uniform_int_distribution<bool> b_dist(0,1);
            std::uniform_int_distribution<double>d_dist(0.01 , 0.5);
            T t;
            unsigned char s;



            for(std::size_t i=0; i<state.range(); ++i){
                t.INSERT(ch_dist(prng));

            }

            for(int j=0; j<state.range()/2; ++j){
                t.LEFT();

            }


            for (auto _ : state) {
                state.PauseTiming();



                if(b_dist(prng)){

                     TIMER(state, state.range(1), [&s, &ch_dist, &prng]()mutable{s=ch_dist(prng);}, [&s,&t]()mutable{t.INSERT(s);});

                }
                else {

                    TIMER(state, state.range(1), /*no_lambda*/[]{} , [&t]()mutable{t.DELETE();});

                }



                if(b_dist(prng)){

                    TIMER(state, static_cast<std::size_t>(d_dist(prng)*t.SIZE()), /*no_lambda*/[]{} , [&t]()mutable{t.LEFT();});

                }
                else {

                    TIMER(state, static_cast<std::size_t>(d_dist(prng)*t.SIZE()), /*no_lambda*/[]{} , [&t]()mutable{t.RIGHT();});

                }

              benchmark::DoNotOptimize(t);
              benchmark::DoNotOptimize(s);

            }
    }


        BENCHMARK_TEMPLATE(BM_TEST, tb::text_buffer<std::deque<unsigned char>>)->RangeMultiplier(2)->Ranges({{2,2<<16},{10, 30}});

        BENCHMARK_TEMPLATE(BM_TEST, tb::text_buffer<std::list<unsigned char>>)->RangeMultiplier(2)->Ranges({{2,2<<16},{10,30}});

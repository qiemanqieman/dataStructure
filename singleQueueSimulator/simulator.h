//
// Created by q on 3/21/21.
//

#ifndef SINGLEQUEUESIMULATOR_SIMULATOR_H
#define SINGLEQUEUESIMULATOR_SIMULATOR_H


#include <random>
#include <chrono>
#include "../linkqueue.h"


class simulator{
    struct custom{
        int arrival_time;
        int service_time;
        explicit custom(int at = 0, int st = 0) {arrival_time = at; service_time = st;};
    };
private:
    int arrival_time_low;
    int arrival_time_high;
    int service_time_low;
    int service_time_high;
    int custom_no;

public:
    simulator();
    simulator(int al, int ah, int sl, int sh, int cn) :arrival_time_low(al), arrival_time_high(ah),
        service_time_low(sl), service_time_high(sh),custom_no(cn){}
    [[nodiscard]] int average_wait_time() const;
};


simulator::simulator() {
    std::cout << "Please input lower and upper bound of arrival time: ";
    std::cin >> arrival_time_low >> arrival_time_high;
    std::cout << "Please input lower and upper bound of service time: ";
    std::cin >> service_time_low >> service_time_high;
    std::cout << "Please input total custom number: ";
    std::cin >> custom_no;
}

int simulator::average_wait_time() const {
    int current_time = 0, total_wait_time = 0, time = 0;
    linkQueue<custom> que;
    simulator::custom current_custom;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> arrival_time(arrival_time_low,arrival_time_high);
    std::uniform_int_distribution<int> service_time(service_time_low, service_time_high);
//    std::normal_distribution<double> arrival_time(5, 2);
//    std::normal_distribution<double> service_time(4, 2);
    for (int i = 0; i < custom_no; ++i){
//        int tmp = arrival_time(generator);
//        if (tmp < arrival_time_low)  tmp = arrival_time_low;
//        if (tmp > arrival_time_high) tmp = arrival_time_high;
//        time += tmp;
//        tmp = service_time(generator);
//        if (tmp < service_time_low) tmp = service_time_low;
//        if (tmp > service_time_high) tmp = service_time_high;
        time += arrival_time(generator);
        simulator::custom cus(time, service_time(generator));
        que.push(cus);
    }

    while(!que.empty()){
        current_custom = que.pop();
        if (current_time >  current_custom .arrival_time) total_wait_time += (current_time -  current_custom .arrival_time);
        else current_time =  current_custom.arrival_time;
        current_time +=  current_custom.service_time;
    }

    return total_wait_time / custom_no;
}

#endif //SINGLEQUEUESIMULATOR_SIMULATOR_H

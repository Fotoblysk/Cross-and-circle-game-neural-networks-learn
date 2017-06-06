#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include "tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;

double odStatndard(std::vector<vec_t> result, std::vector<vec_t> wannedResult, int pow) {
    double res = 0;
    std::vector<double> loss(result.size());
    for (auto i = 0; i < result.size(); ++i)
        loss[i] = std::pow(std::abs(result[i][0] * 10 - wannedResult[i][0] * 10), pow)
                  + std::pow(std::abs(result[i][1] * 10 - wannedResult[i][1] * 10), pow);
    for (auto i : loss)
        res += loss[i];
    res /= loss.size();
    return res;
}

int loadData2(std::string str, std::vector<vec_t> &data,
              std::vector<vec_t> &movesData, bool ignore = false) {
    std::ifstream file;
    file.open("/home/fotoblysk/git-projects/Cross-and-circle-game/dupa/" + str);
    char trash_buffer;
    char turn = 'O';
    while (file.good()) {
        data.push_back(vec_t(100));
        for (auto i = 0; i < 100; ++i) {
            char tmp = 0;
            file >> tmp;
            if (tmp == '.' || tmp == 'O' || tmp == 'X')
                if (tmp == '.')
                    data.back()[i] = float(0);
                else if (tmp == 'O')
                    data.back()[i] = (turn == 'O') ? float(1.0) : float(-1.0);
                else if (tmp == 'X')
                    data.back()[i] = (turn == 'X') ? float(1.0) : float(-1.0);
        }

        trash_buffer = 0;
        file >> trash_buffer;
        long long x, y;
        file >> x;
        file >> y;;
        movesData.push_back({x / 10.0, y / 10.0});
        turn = (turn == 'O') ? 'X' : 'O';
    }
    data.pop_back();
    data.erase(data.begin());
    std::cout << "loaded /home/fotoblysk/git-projects/Cross-and-circle-game/dupa/" + str << std::endl;
}

int loadData(std::string str, std::vector<vec_t> &data,
             std::vector<vec_t> &movesData) {
    std::ifstream file;
    file.open("/home/fotoblysk/git-projects/Cross-and-circle-game/" + str);
    char trash_buffer;
    while (file.good()) {
        data.push_back(vec_t(100));
        for (auto i = 0; i < 100; ++i) {
            char tmp = 0;
            file >> tmp;
            if (tmp == '.' || tmp == 'O' || tmp == 'X')
                if (tmp == '.')
                    data.back()[i] = float(0);
                else if (tmp == 'O')
                    data.back()[i] = float(std::numeric_limits<int>::max());
                else if (tmp == 'X')
                    data.back()[i] = float(std::numeric_limits<int>::min());
        }

        trash_buffer = 0;
        file >> trash_buffer;
        long long x, y;
        file >> x;
        file >> y;;
        movesData.push_back({float(x), float(y)});
    }


    data.pop_back();

    for (auto k = 0; k < data.size(); ++k) {
        for (auto i = 0; i < 100; ++i) {
            //std::cout << data[k][i] << std::endl;
        }
        //std::cout << std::endl;
        //std::cout << movesData[k][0] << ' ' << movesData[k][1] << std::endl;
        //std::cout << std::endl;
    }
}


int main() {
    std::vector<vec_t> data;
    std::vector<vec_t> movesData;
    loadData2("example0_0", data, movesData);
    loadData2("example0_1", data, movesData);
//    loadData2("example0_2", data, movesData);
    loadData2("example0_3", data, movesData);
    loadData2("example0_4", data, movesData);
    loadData2("example0_5", data, movesData);
    loadData2("example0_6", data, movesData);
    loadData2("example0_7", data, movesData);
    loadData2("example0_8", data, movesData);
    loadData2("example0_9", data, movesData);
    loadData2("example1_0", data, movesData);
    loadData2("example1_1", data, movesData);
    loadData2("example1_2", data, movesData);
    loadData2("example1_3", data, movesData);
    loadData2("example1_4", data, movesData);
    loadData2("example1_5", data, movesData);
    loadData2("example1_6", data, movesData);
    loadData2("example1_7", data, movesData);
    std::vector<vec_t> data2;
    std::vector<vec_t> movesData2;
    loadData2("example0_2", data2, movesData2);
    network<sequential> net;
//    gradient_descent opt;
    adagrad opt;
    net
            << layers::conv(10, 10, 5, 1, 1)
            << activation::tanh()
            //            << layers::conv(6, 6,3,1,1)//4
            //           << activation::tanh()
            << layers::fc( 36, 100)//20
            << activation::tanh()
            //  << layers::fc(36, 36)
            //  << activation::tanh()
            << layers::fc(100, 2)
            << activation::tanh();
/*    net
            << layers::fc(100, 100)
            << activation::tanh()
            << layers::fc(100, 100)
            << activation::tanh()
            << layers::fc(100, 100)
            << activation::tanh()
            << layers::fc(100, 100)
            << activation::tanh();
            */
/*    net << layers::conv(10, 10, 5, 1, 1)
        << activation::tanh()
        << layers::conv(6, 6, 2, 1, 1)
        << activation::tanh()
        << layers::conv(5, 5, 2, 1, 1)
        << activation::tanh()
        << layers::conv(4, 4, 2, 1, 1)
        << activation::tanh()
        << layers::conv(3, 3, 2, 1, 1)
        << activation::tanh()
        << layers::fc(4, 100)
        << activation::tanh();
*/
/*    net << fc(10* 10, 25)
        << activation::tanh()
        << layers::fc(25, 100)
        << activation::tanh();
        */
    //     << layers::fc(25, 100)
//        << activation::tanh();
//    net << layers::conv(10, 10, 5, 1, 4) << activation::tanh() << max_pooling_layer(6, 6, 4, 2)
//       << activation::tanh() << layers::fc((6/2) * (6/2) * 4, 100) << activation::tanh();

    size_t epochs = 1000000;

    std::vector<vec_t> input_data{data};
    std::vector<vec_t> desired_out{movesData};
//    size_t batch_size = input_data.size();
    size_t batch_size = 100;


    net.fit<mse>(opt, input_data, desired_out, 10, 100);

    auto result = net.test(data);

    std::cout << odStatndard(result, movesData,1) << "\n";
    auto result1 = net.test(data2);
    std::cout << odStatndard(result1, movesData2,1) << "\n";

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int counter = -20;
    double lastProggres = 0;
    timer t;
    auto on_enumerate_epoch = [&]() {
        static int count = 0;
        if (count % 20 == 0) {
            count = 1;
            auto result = net.test(data);

            std::cout <<  "pow1 \n";
            std::cout << odStatndard(result, movesData,1) << "\n";
            auto result1 = net.test(data2);
            std::cout << odStatndard(result1, movesData2,1) << "\n";
            std::cout <<  "pow2 \n";
            std::cout << odStatndard(result, movesData,2) << "\n";
            std::cout << odStatndard(result1, movesData2,2) << "\n";
            std::cout << t.elapsed() << "s elapsed. \n";
            t.restart();
        }
        ++count;
    };
    auto on_enumerate_mb = [&]() {
    };

    while (true) {
        net.fit<mse>(opt, input_data, desired_out, batch_size, epochs, on_enumerate_mb, on_enumerate_epoch);
        //result = net.test(data, movesData);
        //std::cout << result.accuracy() << std::endl;
        std::cout << "0 0 0aaaaaaaaaaaaaaaa" << std::endl;
        //result1 = net.test(data2, movesData2);
        //std::cout << result1.accuracy() << std::endl;
        //epochs *= 2;
//        ++counter;
/*        if (counter >= 10) {
            counter = 0;
            if (result.accuracy() - lastProggres <= 0.0) {
                std::cout << "size++ = " << ++batch_size << std::endl;
                std::cout << "rep++ = " << ++epochs << std::endl;
                counter = -20;
                lastProggres = 0;
            }
        } else if (counter>=0)
            lastProggres = result.accuracy();
            */
    }
/*
    epochs = 100 * 16;
    batch_size = input_data.size() / 10;
    net.fit<mse>(opt, input_data, desired_out, batch_size, epochs);

    result = net.test(data, movesData);
    std::cout << result.accuracy() << std::endl;
    result = net.test(data2, movesData2);
    std::cout << result.accuracy() << std::endl;

    epochs = 100 * 100;
    batch_size = input_data.size();
    net.fit<mse>(opt, input_data, desired_out, batch_size, epochs);

    result = net.test(data, movesData);
    std::cout << result.accuracy() << std::endl;
    result = net.test(data2, movesData2);
    std::cout << result.accuracy() << std::endl;
*/
    return 0;
}
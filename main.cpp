#define CNN_USE_DOUBLE ON
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
    std::cout << result.size()<< "size of test" <<std::endl;
    res /= loss.size();
    return res;
}

int loadData2(std::string str, std::vector<vec_t> &data,
              std::vector<vec_t> &movesData, bool ignore = false) {
    std::ifstream file;
    file.open("/home/lukaszk/Desktop/Cross-and-circle-game/cpccc/" + str);
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
    file.open("/home/lukaszk/Desktop/Cross-and-circle-game/cpccc/" + str);
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
    loadData2("example1_8", data, movesData);
    loadData2("example1_9", data, movesData);
    loadData2("example2_0", data, movesData);
    loadData2("example2_1", data, movesData);
    loadData2("example2_2", data, movesData);
    loadData2("example2_3", data, movesData);
    loadData2("example2_4", data, movesData);
    loadData2("example2_5", data, movesData);
    loadData2("example2_6", data, movesData);
    loadData2("example2_7", data, movesData);
    loadData2("example2_8", data, movesData);
    loadData2("example2_9", data, movesData);
    loadData2("example3_0", data, movesData);
    loadData2("example3_1", data, movesData);
    loadData2("example3_2", data, movesData);
    loadData2("example3_3", data, movesData);
    loadData2("example3_4", data, movesData);
    loadData2("example3_5", data, movesData);
    loadData2("example3_6", data, movesData);
    loadData2("example3_7", data, movesData);
    loadData2("example3_8", data, movesData);
    loadData2("example3_9", data, movesData);
    loadData2("example4_0", data, movesData);
    loadData2("example4_1", data, movesData);
    loadData2("example4_2", data, movesData);
    loadData2("example4_3", data, movesData);
    loadData2("example4_4", data, movesData);
    loadData2("example4_5", data, movesData);
    loadData2("example4_6", data, movesData);
    loadData2("example4_7", data, movesData);
    loadData2("example4_8", data, movesData);
    loadData2("example4_9", data, movesData);
    loadData2("example5_0", data, movesData);
    loadData2("example5_1", data, movesData);
    loadData2("example5_2", data, movesData);
    loadData2("example5_3", data, movesData);
    loadData2("example5_4", data, movesData);
    loadData2("example5_5", data, movesData);
    loadData2("example5_6", data, movesData);
    loadData2("example5_7", data, movesData);
    loadData2("example5_8", data, movesData);
    loadData2("example5_9", data, movesData);
    loadData2("example6_0", data, movesData);
    loadData2("example6_1", data, movesData);
    loadData2("example6_2", data, movesData);
    loadData2("example6_3", data, movesData);
    loadData2("example6_4", data, movesData);
    loadData2("example6_5", data, movesData);
    loadData2("example6_6", data, movesData);
    loadData2("example6_7", data, movesData);
    loadData2("example6_8", data, movesData);
    loadData2("example6_9", data, movesData);
    loadData2("example7_0", data, movesData);
    loadData2("example7_1", data, movesData);
    loadData2("example7_2", data, movesData);
    loadData2("example7_3", data, movesData);
    loadData2("example7_4", data, movesData);
    loadData2("example7_5", data, movesData);
    loadData2("example7_6", data, movesData);
    loadData2("example7_7", data, movesData);
    loadData2("example7_8", data, movesData);
    loadData2("example7_9", data, movesData);
    loadData2("example8_0", data, movesData);
    loadData2("example8_1", data, movesData);
    loadData2("example8_2", data, movesData);
    loadData2("example8_3", data, movesData);
    loadData2("example8_4", data, movesData);
    loadData2("example8_5", data, movesData);
    loadData2("example8_6", data, movesData);
    loadData2("example8_7", data, movesData);
    loadData2("example8_8", data, movesData);
    loadData2("example8_9", data, movesData);
    loadData2("example9_0", data, movesData);
    loadData2("example9_1", data, movesData);
    loadData2("example9_2", data, movesData);
    loadData2("example9_3", data, movesData);
    loadData2("example9_4", data, movesData);
    loadData2("example9_5", data, movesData);
    loadData2("example9_6", data, movesData);
    loadData2("example9_7", data, movesData);
    loadData2("example9_8", data, movesData);
    loadData2("example9_9", data, movesData);
    std::vector<vec_t> data2;
    std::vector<vec_t> movesData2;
    loadData2("example0_2", data2, movesData2);
    network<sequential> net = make_mlp<activation::tanh>({100, 300, 200, 100, 2});
//    gradient_descent opt;
    adagrad opt;
//    net.load("AI-NN2", content_type::weights_and_model , file_format::json);
/*    net
//            << layers::conv(10, 10, 5, 1, 1)
 //           << activation::tanh()
            << layers::fc( 100, 1000)//20
            << activation::tanh()
            << layers::fc( 1000, 200)//20
            << activation::tanh()
            << layers::fc( 200, 100)//20
            << activation::tanh()
            << layers::fc(100, 2)
            << activation::tanh();
            */

    std::vector<vec_t> input_data{data};
    std::vector<vec_t> desired_out{movesData};

    size_t batch_size = input_data.size();
    size_t epochs = 1200;











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
        if (count % 100 == 0) {
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
            net.save("AI-NN3", content_type::weights_and_model , file_format::json);
            t.restart();
        }
        ++count;
        
    };
    auto on_enumerate_mb = [&]() {
    };
    epochs = 10000;
        net.fit<mse>(opt, input_data, desired_out, batch_size, epochs, on_enumerate_mb, on_enumerate_epoch);
        net.save("AI-NN3", content_type::weights_and_model , file_format::json);
    return 0;
}

#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include "tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;

int loadData2(std::string str, std::vector<vec_t> &data,
              std::vector<label_t> &movesData) {
    std::ifstream file;
    file.open("/home/fotoblysk/git-projects/Cross-and-circle-game/" + str);
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
                    data.back()[i] = (turn == 'O') ? float(2.0) : float(-2.0);
                else if (tmp == 'X')
                    data.back()[i] = (turn == 'X') ? float(2.0) : float(-2.0);
        }

        trash_buffer = 0;
        file >> trash_buffer;
        long long x, y;
        file >> x;
        file >> y;;
        movesData.push_back(x * 10 + y);
        turn = (turn == 'O') ? 'X' : 'O';
    }
    data.pop_back();
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
    std::vector <vec_t> data;
    std::vector <label_t> movesData;
    loadData2("example0_0", data, movesData);
    loadData2("example0_1", data, movesData);
//    loadData2("example0_2", data, movesData);
    loadData2("example5_5", data, movesData);
    std::vector <vec_t> data2;
    std::vector <label_t> movesData2;
    loadData2("example0_2", data2, movesData2);
    network <sequential> net;
    adagrad opt;
    net << layers::conv(10, 10, 5, 1, 25)
        << activation::tanh()
        << layers::fc(6 * 6 * 25, 100)
        << activation::tanh();
    //     << layers::fc(25, 100)
//        << activation::tanh();
//    net << layers::conv(10, 10, 5, 1, 4) << activation::tanh() << max_pooling_layer(6, 6, 4, 2)
//       << activation::tanh() << layers::fc((6/2) * (6/2) * 4, 100) << activation::tanh();

    size_t batch_size = 1;
    size_t epochs = 100;

    std::vector <vec_t> input_data{data};
    std::vector <label_t> desired_out{movesData};


    net.fit<mse>(opt, input_data, desired_out, batch_size, epochs);
    auto result = net.test(input_data, desired_out);
    result = net.test(data, movesData);
    std::cout << result.accuracy() << std::endl;
    result = net.test(data2, movesData2);
    std::cout << result.accuracy() << std::endl;

    batch_size = input_data.size() / 10;
    net.fit<mse>(opt, input_data, desired_out, batch_size, epochs);

    result = net.test(data, movesData);
    std::cout << result.accuracy() << std::endl;
    result = net.test(data2, movesData2);
    std::cout << result.accuracy() << std::endl;

    batch_size = input_data.size();
    net.fit<mse>(opt, input_data, desired_out, batch_size, epochs);

    result = net.test(data, movesData);
    std::cout << result.accuracy() << std::endl;
    result = net.test(data2, movesData2);
    std::cout << result.accuracy() << std::endl;

    return 0;
}
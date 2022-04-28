#include <torch/torch.h>
#include <iostream>
#define PART 4

struct Net : torch::nn::Module
{
    Net(int64_t N, int64_t M) : linear(register_module("linear", torch::nn::Linear(N, M)))
    {
        another_bias = register_parameter("b", torch::randn(M));
    }
    torch::Tensor forward(torch::Tensor input)
    {
        return linear(input) + another_bias;
    }

    torch::nn::Linear linear;
    torch::Tensor another_bias;
};

int main()
{
    //exp_1
#if PART==1
    torch::Tensor tensor = torch::eye(3);
    std::cout << tensor << std::endl;


    //exp_2
#elif PART==2
    Net net(4, 5);
    for(const auto& p : net.parameters())
    {
        std::cout << p << std::endl;
    }


    //exp_3
#elif PART==3
    Net net(4, 5);
    for(const auto& pair : net.named_parameters())
    {
        std::cout << pair.key() << ": " << pair.value() << std::endl;
    }

    //exp_4
#elif PART==4
    Net net(4, 5);
    std::cout << net.forward(torch::ones({2, 4})) << std::endl;
#endif

    return 0;
}
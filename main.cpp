#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_NAME "windows"
#else
#define PLATFORM_NAME "linux"
#endif

#include <iostream>
#include <stdlib.h>

const int maxQtdProduto = 10;

struct produto
{
    int qtdProduto;
    float precoProduto;
    char *nomeProduto;

    produto() : qtdProduto(0), precoProduto(0), nomeProduto("produto") {}
};

int main() {

    return 0;
}

// Misc functions
void CleanScreen()
{
    if (PLATFORM_NAME == "windows")
    {
        std::system("cls");
    }
    else
    {
        std::system("clear");
    }
}
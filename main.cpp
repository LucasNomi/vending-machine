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

    produto() : qtdProduto(1), precoProduto(1), nomeProduto("produto") {}

    // User functions
    float Purchase(float dinheiro)
    {
        float troco;

        if (dinheiro >= precoProduto)
        {
            qtdProduto--;
            troco = dinheiro - precoProduto;
            return troco;
        }
        else
        {
            std::cout << "Nao foi possivel comprar o produto! \n";
            return dinheiro;
        }
    }

    // Adm functions
    void Restock()
    {
        qtdProduto = maxQtdProduto;
    }

    float Faturamento()
    {
        float faturamento = 0;
        faturamento = (maxQtdProduto - qtdProduto) * precoProduto;

        return faturamento;
    }

    float FaturamentoFuturo()
    {
        float faturamentoFuturo;
        float faturamentoTotal = maxQtdProduto * precoProduto;
        float faturamentoAtual = Faturamento();

        faturamentoFuturo = faturamentoTotal - faturamentoAtual;

        return faturamentoFuturo;
    }
};

int main()
{
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
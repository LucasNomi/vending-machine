#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_NAME "windows"
#else
#define PLATFORM_NAME "linux"
#endif

#include <iostream>
#include <stdlib.h>

const int maxQty = 10;

struct produto
{
    int qty;
    float price;
    char *name;

    produto() : qty(1), price(1), name("produto") {}

    // User functions
    float Purchase(float money)
    {
        if (money >= price)
        {
            qty--;
            money = money - price;
            return money;
        }
        else
        {
            std::cout << "Nao foi possivel comprar o produto! \n";
            return -1;
        }
    }

    // Adm functions
    void Restock()
    {
        qty = maxQty;
    }

    float Sales()
    {
        float faturamento = (maxQty - qty) * price;

        return faturamento;
    }

    float UpcomingSales()
    {
        float upcomingSales;
        float totalSales = maxQty * price;
        float currentSales = Sales();

        upcomingSales = totalSales - currentSales;

        return upcomingSales;
    }
};

int VendingMachine(int size, produto *vendingMachine);
void CleanScreen();

int main()
{

    float money;
    do
    {
        std::cout << "Insira uma quantia em dinheiro para comecar a compra...\n";
        std::cin >> money;

        if (money <= 0)
        {
            CleanScreen();
            std::cout << "Quantia inserida invalida.\n";
        }

    } while (money <= 0);

    produto vendingMachine[16];
    int qtyItem = sizeof vendingMachine / sizeof vendingMachine[0];
    int idProd;

    idProd = VendingMachine(qtyItem, vendingMachine);

    float change;
    change = vendingMachine[idProd].Purchase(money);

    std::cout << "Troco: " << change << "\n";

    return 0;
}

// User Screen
int VendingMachine(int qty, produto *vendingMachine)
{
    produto selectedProd;
    char ans;
    int idProd;
    do
    {
        std::cout << "*---MAQUINA DE VENDA---*\n";
        for (int i = 0; i < qty; i++)
        {
            selectedProd = vendingMachine[i];
            if (selectedProd.qty > 0)
            {
                std::cout << "(" << i + 1 << ")";
                std::cout << selectedProd.name << "\n";
                std::cout << "Preco: " << selectedProd.price << "\n\n";
            }
        }

        std::cout << "Qual produto deseja comprar? \n";
        std::cout << "--> ";
        std::cin >> idProd;

        std::cout << "CONFIRMAR COMPRA? [s/n]", std::cin >> ans;

        if (ans == 'n')
        {
            CleanScreen();
        }
        else
        {
            CleanScreen();
            std::cout << "Processando compra...\n";
        }

    } while (ans == 'n');

    idProd--;
    if (idProd < qty)
    {
        return idProd;
    }
    else
    {
        return -1;
    }
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
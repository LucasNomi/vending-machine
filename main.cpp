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

    produto() : qty(0), price(1), name("produto") {}

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
        float sales = (maxQty - qty) * price;

        return sales;
    }

    float UpcomingSales()
    {
        float upcomingSales;
        float totalSales = maxQty * price;
        float currentSales = Sales();

        upcomingSales = totalSales - currentSales;

        return upcomingSales;
    }

    void AddProduto(float newPrice, char *newName)
    {
        qty = maxQty;
        price = newPrice;
        name = newName;
    }
};

void ShowVendingMachine(bool isAdm, int qty, produto *vendingMachine);
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

    if (change == -1)
    {
        std::cout << "Dinheiro nao suficiente para comprar o produto\n";
        std::cout << "Retornando seu dinheiro...\n";
        std::cout << "Compre outro produto ou insira mais dinheiro.\n\n";
        std::cout << "Troco: " << money << "\n";
    }
    else
    {
        std::cout << "Produto adquirido: " << vendingMachine[idProd].name << "\n";
        std::cout << "Troco: " << change << "\n";
    }

    return 0;
}

// Show vendingmachine
void ShowVendingMachine(bool isAdm, int qty, produto *vendingMachine)
{
    produto selectedProd;
    std::cout << "*---MAQUINA DE VENDA---*\n";
    for (int i = 0; i < qty; i++)
    {
        selectedProd = vendingMachine[i];
        if (isAdm)
        {
            std::cout << "(" << i + 1 << ")";
            std::cout << selectedProd.name << "\n";
            std::cout << "Qty: " << selectedProd.qty << "\n\n";
        }
        else
        {
            if (selectedProd.qty > 0)
            {
                std::cout << "(" << i + 1 << ")";
                std::cout << selectedProd.name << "\n";
                std::cout << "Preco: " << selectedProd.price << "\n\n";
            }
        }
    }
}

// User Screen
int VendingMachine(int qty, produto *vendingMachine)
{
    char ans;
    int idProd;
    do
    {
        ShowVendingMachine(false, qty, vendingMachine);

        std::cout << "Qual produto deseja comprar? \n";
        std::cout << "--> ";
        std::cin >> idProd;
        idProd--;

        std::cout << "CONFIRMAR COMPRA? [s/n] \n";
        std::cin >> ans;

        if (ans == 'n')
        {
            CleanScreen();
        }
        else if (idProd >= qty || idProd <= 0 || vendingMachine[idProd].qty == 0)
        {
            CleanScreen();
            std::cout << "Codigo do produto invalido! \n";
        }
        else
        {
            CleanScreen();
            std::cout << "Processando compra...\n";
        }

    } while (ans == 'n' || idProd >= qty || idProd <= 0 || vendingMachine[idProd].qty == 0);

    return idProd;
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
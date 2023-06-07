#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_NAME "windows"
#else
#define PLATFORM_NAME "linux"
#endif

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

const int maxQty = 10;

struct produto
{
    int qty;
    float price;
    const char *name;

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
        float maxPossibleSales = maxQty * price;
        float upcomingSales;
        float currentSales;

        currentSales = Sales();

        upcomingSales = maxPossibleSales - currentSales;
        return upcomingSales;
    }
};

void ShowVendingMachine(bool isAdm, int qty, produto *vendingMachine);
void UserVendingMachine(int size, produto *vendingMachine);
void ControlVendingMachine(int qty, produto *vendingMachine);
void CleanScreen();

int main()
{
    produto vendingMachine[16] = {
        {maxQty, 6.5, "Pepsi-Cola"},
        {maxQty, 7.5, "Coca-Cola"},
        {maxQty, 5.5, "Delvalle Kapo"},
        {maxQty, 3.7, "Agua"},
        {maxQty, 9.9, "Doritos"},
        {maxQty, 11.8, "Cheetos"},
        {maxQty, 8.9, "Fandangos"},
        {maxQty, 3, "Trofeu"},
        {maxQty, 4, "Snickers"},
        {maxQty, 6.6, "Pipoca Doce"},
        {maxQty, 2.5, "Bombom"},
        {maxQty, 3, "Amendoim"},
        {maxQty, 14, "Guarda-chuva"},
        {maxQty, 8.7, "Dorflex"},
        {maxQty, 20, "Chip Claro (Pre-pago)"},
        {maxQty, 50.5, "Havaianas"}};

    int qtyItem = sizeof vendingMachine / sizeof vendingMachine[0];

    int choice;
    do
    {
        std::cout << "[1] Entrar como usuario [2] Entrar como administrador [3] Sair \n";
        std::cout << "--> ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            CleanScreen();
            UserVendingMachine(qtyItem, vendingMachine);
            break;
        case 2:
            CleanScreen();
            ControlVendingMachine(qtyItem, vendingMachine);
            break;
        default:
            CleanScreen();
            break;
        }
        
    } while (choice != 3);

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
void UserVendingMachine(int qty, produto *vendingMachine)
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

    char ans;
    int idProd;

    do
    {
        CleanScreen();
        ShowVendingMachine(false, qty, vendingMachine);

        std::cout << "Qual produto deseja comprar? \n";
        std::cout << "--> ";
        std::cin >> idProd;
        idProd--;

        std::cout << "CONFIRMAR COMPRA? [s/n] \n";
        std::cin >> ans;

        if (idProd >= qty || idProd < 0 || vendingMachine[idProd].qty == 0)
        {
            std::cout << "Codigo do produto invalido! \n";
            std::cout << "Reiniciando sua compra... \n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else
        {
            CleanScreen();
            std::cout << "Processando compra...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

    } while (ans == 'n' || idProd >= qty || idProd < 0 || vendingMachine[idProd].qty == 0);

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
}

// Adm Screen

void ControlVendingMachine(int qty, produto *vendingMachine)
{
    int choice;
    int idProd;
    do
    {
        ShowVendingMachine(true, qty, vendingMachine);

        std::cout << "-*MODO ADMINISTRADOR*-\n";
        std::cout << "[1] Restock de produto [2] Faturamento [3] Faturamento futuro \n";
        std::cout << "--> ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Selecione o produto para fazer restock";
            std::cout << "--> ";
            CleanScreen();
            std::cin >> idProd;
            std::cout << "Qty antiga: " << vendingMachine[idProd].qty << "\n";
            vendingMachine[idProd].Restock();
            std::cout << "Qty nova: " << vendingMachine[idProd].qty << "\n";
            break;
        case 2:
            CleanScreen();
            float totalSales;
            totalSales = 0;

            for (int i = 0; i < qty; i++)
            {
                totalSales += vendingMachine[i].Sales();
            }

            std::cout << "Faturamento: RS" << totalSales << "\n";
            break;
        case 3:
            CleanScreen();
            float totalUpcomingSales;
            totalUpcomingSales = 0;

            for (int i = 0; i < qty; i++)
            {
                totalUpcomingSales += vendingMachine[i].UpcomingSales();
            }

            std::cout << "Faturamento futuro: RS" << totalUpcomingSales << "\n";
            break;
        default:
            CleanScreen();
            std::cout << "Codigo de funcao invalido";
            break;
        }

    } while (choice <= 0 || choice > 3);
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
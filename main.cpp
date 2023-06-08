// Detecta o sistema operacional do usuario

#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_NAME "windows"
#else
#define PLATFORM_NAME "linux"
#endif

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

// Define a quantidade maxima de entidades para um produto.
const int maxQty = 10;

// estrutura para um produto
struct produto
{
    // cada produto possui uma quantidade, um preco e um nome
    int qty;
    float price;
    std::string name;

    // User functions

    // Funcao para comprar um produto
    // Recebe uma quantia em dinheiro, se esse dinheiro for suficiente para
    // comprar o produto, entao a quantidade do produto e reduzida
    // e o preco do produto e subtraido do dinheiro, retornando como um troco
    // Caso nao for suficiente retorna -1 para simbolizar um erro.
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

    // Funcao para fazer o restock do produto
    // define a quantidade do produto como sua quantidade maxima
    void Restock()
    {
        qty = maxQty;
    }

    // Funcao para verificar o faturamento do produto
    // O calculo do faturamento e feito subtraindo a quantidade atual
    // do produto de sua quantidade maxima, achando assim quantos produtos
    // foram vendidos, o resultado e entao multiplicado pelo preco do produto
    float Sales()
    {
        float sales = (maxQty - qty) * price;

        return sales;
    }

    // Funcao para verificar o faturamento futuro do produto
    // O calculo do faturamento futuro e feito primeiro achando o
    // faturamento total possivel do produto, entao o faturamento atual
    // e depois subtrai o faturamento atual do faturamento possivel
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
    // Inicializacao de uma maquina de vendas padrao
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

    // Calcula a quantidade de produtos da maquina de vendas
    // o tamanho total da maquina de vendas (16 * tmn de cada produto)
    // e dividido pelo tamanho do seu primeiro produto
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

// funcao utilizada para mostrar os produtos da maquina de vendas
// Recebe como parametros um booleano para saber se e um adm
// a quantidade de itens da maquina de vendas para iteracao
// e a propria maquina de vendas
void ShowVendingMachine(bool isAdm, int qty, produto *vendingMachine)
{
    produto selectedProd;
    std::cout << "*---MAQUINA DE VENDA---*\n";
    for (int i = 0; i < qty; i++)
    {
        selectedProd = vendingMachine[i];
        if (isAdm)
        {
            // se for um adm ira mostrar a quantidade atual de cada item
            std::cout << "(" << i + 1 << ")";
            std::cout << selectedProd.name << "\n";
            std::cout << "Qty: " << selectedProd.qty << "\n\n";
        }
        else
        {
            // se o produto existir (tiver quantidade maior que zero)
            // ele ira ser mostrado para o usuario, junto com seu preco  
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

// Funcao utilizada pelo usuario para fazer sua compra
// recebe quantidade de itens na maquina de venda para iteracao
// recebe a propria maquina de vendas
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
    // nao permite o usuario comprar produtos que nao existam (id > qtytotal)
    // nao permite o usuario comprar produtos que nao estao disponiveis (qty < 0)
    } while (ans == 'n' || idProd >= qty || idProd < 0 || vendingMachine[idProd].qty == 0);

    float change;
    change = vendingMachine[idProd].Purchase(money);

    // manipula o erro de retorno -1 da funcao purchase
    if (change == -1)
    {
        std::cout << "Dinheiro insuficiente para comprar o produto\n";
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

// Funcao utilizada pelo adm para manipular a maquina
// recebe quantidade de itens na maquina de venda para iteracao
// recebe a propria maquina de vendas
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

            // calcula o total de faturamento da maquina fazendo uma iteracao
            // por cada produto e achando seu faturamento atual
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

            // calcula o faturamento futuro da maquina fazendo uma iteracao
            // por cada produto e achando seu faturamento futuro
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

// Limpa a tela de acordo com o comando utilizado em cada OS
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
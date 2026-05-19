#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>

using namespace std;

// --- ESTRUTURAS (Simulação de Arquivos Sequenciais) ---
struct Cidades {
    int codigo;
    char nome[30];
    char uf[3];
};

struct Clientes {
    int codigo;
    char nome[30];
    char endereco[35];
    char telefone[15];
    int codigo_cidade;
};

struct Veiculos {
    char placa[10];
    char modelo[20];
    char marca[20];
    int ano;
    int codigo_cliente;
};

struct Servicos {
    int codigo;
    char descricao[40];
    float valor_mao_obra;
};

struct Pecas {
    int codigo;
    char descricao[40];
    int quant_estoque;
    int estoque_minimo;
    int estoque_maximo;
    float preco_unitario;
};

struct Mecanicos {
    int codigo;
    char nome[30];
    char especialidade[30];
    char telefone[15];
};

struct OrdensServico {
    int codigo;
    char placa_veiculo[10];
    int codigo_mecanico;
    char data[11];
    int codigo_servico;
    int codigo_peca;
    int quantidade_peca;
};

//--------------------1-------------------------

void leitura_cidades(struct Cidades x[], int &tam) {
    cout << "\nQuantas cidades cadastrar? ";
    cin >> tam;
    for (int i = 0; i < tam; i++) {
        cout << "\nCodigo " << i+1 << ": " << endl;    
        cin >> x[i].codigo;
        cin.ignore();
        cout << "Nome: ";
        cin >> x[i].nome;
        cout << "Estado: ";
        cin >> x[i].uf;
    }
}

void leitura_servicos(struct Servicos x[], int &tam) {
    cout << "\nQuantas Serviços cadastrar? ";
    cin >> tam;
    for (int i = 0; i < tam; i++) {
        cout << "\nCodigo " << i+1 << ": " << endl;    
        cin >> x[i].codigo;
        cin.ignore();
        cout << "\nDescrição: ";
        cin >> x[i].descricao;
        cout << "Valor da mão de obra: ";
        cin >> x[i].valor_mao_obra;
    }
}

void leitura_pecas(struct Pecas x[], int &tam) {
    cout << "\nQuantas peças cadastrar: ";
    cin >> tam;
    for (int i = 0; i < tam; i++) {
        cout << "\nCodigo " << i+1 << ": " << endl;    
        cin >> x[i].codigo;
        cin.ignore();
        cout << "\nDescrição: ";
        cin >> x[i].descricao;
        cout << "Quantidade em estoque: ";
        cin >> x[i].quant_estoque;
        cout << "Qual é o estoque minimo: ";
        cin >> x[i].estoque_minimo;
        cout << "Qual é o estoque maximo: ";
        cin >> x[i].estoque_maximo;
        cout << "Qual o valor da peça: ";
        cin >> x[i].preco_unitario;
    }
}

//--------------------2-------------------------

void inclusaoClientes(struct Clientes cli[], int &contCli, struct Cidades cid[], int contCid){
    
    int cod; 
    int posCid;
    
    cout << "\n----INCLUSÃO DE CLIENTES----" << endl;
    cout << "Informe o código do cliente: ";
    cin >> cod;

//-------------2.1------------------------------
    int i = 0, f = contCli - 1, posCli = -1;
    int m = (i + f) / 2;

    for (; f >= i && cod != cli[m].codigo; m = (i + f) / 2){
        if(cod > cli[m].codigo){
            i = m + 1;
         }    
        else {
            f = m - 1;    
        }
    }

// se o codigo for igual a meio, significa que o cliente existe.

    if (contCli > 0 && cod == cli[m].codigo){
        cout << "\nCliente ja cadastrado!";
        getch();
        return;
    }

// se não existe, realiza a inclusão
    cli[contCli].codigo = cod;
    cin.ignore();

    cout << "Nome: ";
    cin.getline(cli[contCli].nome,30);

    cout << "Endereco: ";
    cin.getline(cli[contCli].endereco,40);

    cout << "Telefone: ";
    cin.getline(cli[contCli].telefone,35);

//Digitar codigo da cidade e verificar se ela existe na tabela clientes

    int codCid;
    cout << "Digite o codigo da cidade: ";
    cin >> codCid;

//busca sequencial simples
 
    int achouCid = 0;
    int j;

    for (j = 0; j < contCid; j++){
        if(codCid == cid[j].codigo){
            achouCid = 1;
            posCid = j;
            break;
        }
    }
    if (achouCid == 1){
        cout << "\nCidade: " << cid[posCid].nome;
        cout << "\nEstado: " << cid[posCid].uf;

        cli[contCli].codigo_cidade = codCid;

        contCli++;
        cout << "Cliente cadastrado com sucesso!";
    }else{
        cout << "\nCidade não encontrada! cadastro cancelado.";
    }
}

int main(){
    struct Clientes arqClientes[100];
    struct Cidades arqCidades[100];
    int contCli = 0;
    int contCid = 0;

    inclusaoClientes (arqClientes, contCli, arqCidades, contCid);

    return 0;
}
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

//------------------------3-------------------------------------

void inclusaoVeiculos(struct Veiculos vei[], int &contVei, struct Clientes cli[], int contCli){
    char novaPlaca[10];
    cout << "Inclusao de veiculos: ";
    cout << "Digite a placa do veiculo: ";
    cin >> novaPlaca;

//--------------------3.1-----------------BUSCA ALEATORIA
    int i = 0, f = contVei - 1;
    int m = (i + f) / 2;

    for (; f >= i && strcmp(novaPlaca, vei[m].placa) != 0; m = (i + f) / 2){
        if(strcmp(novaPlaca, vei[m].placa) > 0){
            i = m + 1;
        }
        else {
            f = m - 1;
        }
    }

    if (contVei > 0 && strcmp(novaPlaca, vei[m].placa) == 0){
        cout << "\nVeiculo ja cadastrado!";
        getch();
        return;
    }

    int codigoCliente;
    cout <<"Digite o codigo do cliente: ";
    cin >> codigoCliente;

    int i = 0, f = contCli - 1, posCli = -1;
    int m = (i + f) / 2;

    for(;f >= i && codigoCliente != cli[m].codigo; m = (i + f) / 2){
        if(codigoCliente > cli[m].codigo){
            i = m + 1;
        }
        else{
            f = m - 1;
        }
    }

    if(contCli > 0 && codigoCliente == cli[m].codigo){
        cout <<"Cliente encontrado: " << cli[m].codigo << endl;
    

    strcpy(vei[m].placa, novaPlaca);
    vei[m].codigo_cliente = codigoCliente;

    cin.ignore();
    cout << "Modelo do veiculo: ";
    cin.getline(vei[m].modelo, 20);

    cout << "Qual a marca do veiculo: ";
    cin.getline(vei[m].marca, 20);

    cout << "Qual o ano do veiculo: ";
    cin >> vei[m].ano;

    contVei++;
    cout << "Veiculo cadastrado com sucesso!";
    getch();
   
   }else{
    cout <<"Cliente não encontrado.";
    getch();
   }

}

//---------------------4-------------------------------------

void inclusaoMecanicos(struct Mecanicos mec[], int &contMec){
    int codMec;
    cout <<"Digite o codigo do mecanico: ";
    cin >> codMec;

    int i = 0, f = contMec - 1;
    int m = (i + f) / 2;

    for(; f >= i && codMec != mec[m].codigo; m = (i + f) / 2){
        if(codMec > mec[m].codigo){
            i = m + 1;
        }
        else{
            f = m - 1;
        }
    }

    if(contMec > 0 && codMec == mec[m].codigo){
        cout <<"Mecanico ja cadastrado!";
        getch();
        return;
    }

    mec[contMec].codigo = codMec;
    cin.ignore();

    cout <<"Digite o nome do mecanico: ";
    cin.getline(mec[contMec].nome, 30);

    cout <<"Digite sua especialidade: ";
    cin.getline(mec[contMec].especialidade, 30);

    cout <<"Digite o numero do celular: ";
    cin.getline(mec[contMec].telefone, 15);

    cout <<"Cadastro realizado com sucesso: ";
}

void aberturaOrdemServico(
    struct Veiculos vei[], int contVei,
    struct Clientes cli[], int contCli,
    struct Mecanicos mec[], int contMec,
    struct Servicos ser[], int contSer,
    struct Pecas pec[], int contPec,
    struct OrdemServico os[], int contOs) {

        cout << "Abertura de ordem de serviço!";
        
        int numOS;
        cout <<"Numero da O.S: "; cin >> numOS;

        //----------5.1------------------
        //ENCONTRAR VEICULO
        char placaBusca[10];
        cout <<"Placa do veiculo: "; cin >> placaBusca;
        
        int posVei = -1;
        int i = 0, f = contVei - 1;
        int m = (i + f) / 2;

        for(; f >= i && strcmp(placaBusca, vei[m].placa) != 0; m = (i + f) / 2){
            if(strcmp(placaBusca, vei[m].placa) > 0){
                i = m + 1;
            }
            else {
                f = m - 1;
            }
        }
        
        if (contVei > strcmp(placaBusca, vei[m].placa) == 0){
            posVei = m;
        }
        else{
            cout <<"Veiculo nao encontrado: ";
        }

        //ENCONTRAR CLIENTE DONO DO VEICULO
        int codCliBusca = vei[posVei].codigo_cliente;
        int posCli = -1;
        int i = 0, f = contCli - 1;
        int m = (i + f) / 2;

        for(; i >= f && codCliBusca != cli[m].codigo; m = (i + f) / 2){
            if(codCliBusca > cli[m].codigo){
                i = m + 1;
            }
            else{
                f = m - 1;
            }
        }
        if(contCli > 0 && codCliBusca == cli[m].codigo){
            posCli = m;
        }
        cout <<"Modelo: " << vei[posVei].modelo << "Cliente: " << cli[posCli].nome << "/n/n";

        //----------------5.2---------------------
        int codMec;
        cout <<"Codigo do mecanico: "; cin >> codMec;
        
        int posMec = -1;
        int i = 0, f = contMec - 1;
        int m = (i + f) / 2;

        for(; f >= i && codMec != mec[m].codigo; m = (i + f) / 2){
            if(codMec > mec[m].codigo){
                i = m + 1;
            }
            else {
                f = m - 1;
            }
        }
        
        if (contMec > 0 && codMec == mec[m].codigo){
            posMec = m;
        }
        else{
            cout <<"Mecanico nao encontrado: ";
            getch(); return;
        }
        cout <<"Mecanico: " << mec[posMec].nome <<"Especialidade: " << mec[posMec].especialidade <<"/n/n";

        //--------------------5.3----------------------
        int codSer;
        cout <<"Codigo do Servcico: "; cin >> codSer;
        
        int posSer = -1;
        int i = 0, f = contSer - 1;
        int m = (i + f) / 2;

        for(; f >= i && codSer != ser[m].codigo; m = (i + f) / 2){
            if(codSer > ser[m].codigo){
                i = m + 1;
            }
            else {
                f = m - 1;
            }
        }
        
        if (contSer > 0 && codSer == ser[m].codigo){
            posMec = m;
        }
        else{
            cout <<"Servico nao encontrado: ";
            getch(); return;
        }
        cout <<"Servico: " << ser[posSer].descricao <<"Valor da mão de obra: R$ " << ser[posSer].valor_mao_obra <<"/n/n";

        //--------------5.4-----------------------------
        int codPec;
        cout <<"Codigo da peça: "; cin >> codPec;
        
        int posPec = -1;
        int i = 0, f = contPec - 1;
        int m = (i + f) / 2;

        for(; f >= i && codPec != pec[m].codigo; m = (i + f) / 2){
            if(codPec > pec[m].codigo){
                i = m + 1;
            }
            else {
                f = m - 1;
            }
        }
        
        if (contPec > 0 && codPec == pec[m].codigo){
            posPec = m;
        }
        else{
            cout <<"Peça não encontrada: ";
            getch(); return;
        }
        cout <<"Peça: " << pec[posPec].descricao <<"/n/n";

        //--------------5.5------------------------
        int qtd;
        cout <<"Digite a quantidade de pecas";
        cin >> qtd;

        if(qtd > pec[posPec].quant_estoque){
            cout <<"Estoque insuficiente: ";
            getch(); return;
        }

        pec[posPec].quant_estoque = pec[posPec].quant_estoque - qtd;
    }

int main(){
    
    struct Pecas arqPecas[100];
    struct Servicos arqServicos[100];
    struct Clientes arqClientes[100];
    struct Cidades arqCidades[100];
    struct Veiculos arqVeiculos[100];
    struct Mecanicos arqMecanicos[100];
    
    int contPec = 0;
    int contSer = 0;
    int contCli = 0;
    int contCid = 0;
    int contVei = 0;
    int contMec = 0;

    leitura_cidades(arqCidades, contCid);
    leitura_servicos(arqServicos, contSer);
    leitura_pecas(arqPecas, contPec);
    inclusaoClientes (arqClientes, contCli, arqCidades, contCid);
    inclusaoVeiculos (arqVeiculos, contVei, arqClientes, contCli);
    inclusaoMecanicos (arqMecanicos, contMec);

    return 0;
}
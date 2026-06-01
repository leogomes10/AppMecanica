#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>

using namespace std;

// --- ESTRUTURAS
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
        cout << "\nNome: ";
        cin >> x[i].nome;
        cout << "\nEstado: ";
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
        cout << "\nValor da mão de obra: ";
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
        cout << "\nQuantidade em estoque: ";
        cin >> x[i].quant_estoque;
        cout << "\nQual é o estoque minimo: ";
        cin >> x[i].estoque_minimo;
        cout << "\nQual é o estoque maximo: ";
        cin >> x[i].estoque_maximo;
        cout << "\nQual o valor da peça: ";
        cin >> x[i].preco_unitario;
    }
}

//--------------------2-------------------------

void inclusaoClientes(struct Clientes cli[], int &contCli, struct Cidades cid[], int contCid){
    
    int cod; 
    int posCid;
    
    cout << "\nINCLUSÃO DE CLIENTES" << endl;
    cout << "\nInforme o código do cliente: ";
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
    cin.getline(cli[contCli].telefone, 15);

//Digitar codigo da cidade e verificar se ela existe na tabela clientes

    int codCid;
    cout << "\nDigite o codigo da cidade: ";
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
        cout << "\nCliente cadastrado com sucesso!";
    }else{
        cout << "\nCidade não encontrada! cadastro cancelado.";
    }
}

//------------------------3-------------------------------------

void inclusaoVeiculos(struct Veiculos vei[], int &contVei, struct Clientes cli[], int contCli){
    char novaPlaca[10];
    cout << "Inclusao de veiculos, ";
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
    cout <<"\nDigite o codigo do cliente: ";
    cin >> codigoCliente;
     
    int posCli = -1;
    i = 0, f = contCli - 1; 
    m = (i + f) / 2;

    for(;f >= i && codigoCliente != cli[m].codigo; m = (i + f) / 2){
        if(codigoCliente > cli[m].codigo){
            i = m + 1;
        }
        else{
            f = m - 1;
        }
    }

    if(contCli > 0 && codigoCliente == cli[m].codigo){
        cout <<"\nCliente encontrado: " << cli[m].codigo << endl;
    

    strcpy(vei[m].placa, novaPlaca);
    vei[m].codigo_cliente = codigoCliente;

    cin.ignore();
    cout << "\nModelo do veiculo: ";
    cin.getline(vei[m].modelo, 20);

    cout << "\nQual a marca do veiculo: ";
    cin.getline(vei[m].marca, 20);

    cout << "\nQual o ano do veiculo: ";
    cin >> vei[m].ano;

    contVei++;
    cout << "\nVeiculo cadastrado com sucesso!";
    getch();
   
   }else{
    cout <<"\nCliente não encontrado.";
    getch();
   }

}

//---------------------4-------------------------------------

void inclusaoMecanicos(struct Mecanicos mec[], int &contMec){
    int codMec;
    cout <<"\nDigite o codigo do mecanico: ";
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
        cout <<"\nMecanico ja cadastrado!";
        getch();
        return;
    }

    mec[contMec].codigo = codMec;
    cin.ignore();

    cout <<"\nDigite o nome do mecanico: ";
    cin.getline(mec[contMec].nome, 30);

    cout <<"\nDigite sua especialidade: ";
    cin.getline(mec[contMec].especialidade, 30);

    cout <<"\nDigite o numero do celular: ";
    cin.getline(mec[contMec].telefone, 15);

    cout <<"\nCadastro realizado com sucesso: ";
}

void aberturaOrdemServico(
    struct Veiculos vei[], int contVei,
    struct Clientes cli[], int contCli,
    struct Mecanicos mec[], int contMec,
    struct Servicos ser[], int contSer,
    struct Pecas pec[], int contPec,
    struct OrdensServico os[], int &contOS) {

        cout << "\nAbertura de ordem de serviço!";
        
        int numOS;
        cout <<"\nNumero da O.S: "; cin >> numOS;

        //----------5.1------------------
        //ENCONTRAR VEICULO
        char placaBusca[10];
        cout <<"\nPlaca do veiculo: "; cin >> placaBusca;
        
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
        
        if (contVei > 0 && strcmp(placaBusca, vei[m].placa) == 0){
            posVei = m;
        }
        else{
            cout <<"\nVeiculo nao encontrado: ";
        }

        //ENCONTRAR CLIENTE DONO DO VEICULO
        int codCliBusca = vei[posVei].codigo_cliente;
        int posCli = -1;
        i = 0, f = contCli - 1;
        m = (i + f) / 2;

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
        cout <<"\nModelo: " << vei[posVei].modelo << "\nCliente: " << cli[posCli].nome << "/n/n";

        //----------------5.2---------------------
        int codMec;
        cout <<"\nCodigo do mecanico: "; cin >> codMec;
        
        int posMec = -1;
        i = 0, f = contMec - 1;
        m = (i + f) / 2;

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
            cout <<"\nMecanico nao encontrado: ";
            getch(); return;
        }
        cout <<"\nMecanico: " << mec[posMec].nome <<"\nEspecialidade: " << mec[posMec].especialidade <<"/n/n";

        //--------------------5.3----------------------
        int codSer;
        cout <<"\nCodigo do Servcico: "; cin >> codSer;
        
        int posSer = -1;
        i = 0, f = contSer - 1;
        m = (i + f) / 2;

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
            cout <<"\nServico nao encontrado: ";
            getch(); return;
        }
        cout <<"\nServico: " << ser[posSer].descricao <<"\nValor da mão de obra: R$ " << ser[posSer].valor_mao_obra <<"/n/n";

        //--------------5.4-----------------------------
        int codPec;
        cout <<"\nCodigo da peça: "; cin >> codPec;
        
        int posPec = -1;
        i = 0, f = contPec - 1;
        m = (i + f) / 2;

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
            cout <<"\nPeça não encontrada: ";
            getch(); return;
        }
        cout <<"\nPeça: " << pec[posPec].descricao <<"/n/n";

        //--------------5.5------------------------
        int qtd;
        cout <<"\nDigite a quantidade de pecas";
        cin >> qtd;

        if(qtd > pec[posPec].quant_estoque){
            cout <<"Estoque insuficiente: ";
            getch(); return;
        }

        pec[posPec].quant_estoque = pec[posPec].quant_estoque - qtd;

        os[contOS].codigo = numOS;
        strcpy(os[contOS].placa_veiculo, placaBusca);
        os[contOS].codigo_mecanico = codMec;
        os[contOS].codigo_servico = codSer;
        os[contOS].codigo_peca = codPec;
        os[contOS].quantidade_peca = qtd;

        contOS++;
        cout << "/nOrdem de serviço cadastrada!";
        getch();   
}

//-----------------6----------------------
void consultarPeca(struct Pecas pec[], int contPec){
    
    int codPec;
    cout <<"\nDigite o código da peça: ";
    cin >> codPec;
    
    float valorTotalEstoque;
    int PosPec = -1;
    int i = 0, f = contPec - 1;
    int m = (i + f) / 2;

    for(;f >= i && codPec != pec[m].codigo; m = (i + f) / 2){
        if(codPec > pec[m].codigo){
            i = m + 1;
        }
        else{
            f = m - 1;
        }
    }
    if(contPec > 0 && codPec == pec[m].codigo){
        PosPec = m;
    }else{
        cout <<"\nPeça não encontrada!";
        getch(); return;
    }

    valorTotalEstoque = pec[PosPec].preco_unitario * pec[PosPec].quant_estoque;

    cout <<"\nDescricao da peca: " << pec[PosPec].descricao;
    cout <<"\nQuantidade em estoque: " << pec[PosPec].quant_estoque;
    cout <<"\nEstoque Minimo: " << pec[PosPec].estoque_minimo;
    cout <<"\nEstoque maximo: " << pec[PosPec].estoque_maximo;
    cout <<"\nPreço Unitario: R$ " << pec[PosPec].preco_unitario;
    cout <<"\nValor total em estoque: " << valorTotalEstoque;

    getch();
}

//------------------7------------------------

void exibirEstoque(struct Pecas pec[], int contPec){
    cout <<"\nRelatório de peças que estão abaixo do estoque minimo: ";

    float valorTotalCompra = 0;
    int achouPec = 0;

    for(int i = 0; i < contPec; i++){
        if(pec[i].quant_estoque < pec[i].estoque_minimo){
            achouPec = 1; 

            int qtdComprar = pec[i].estoque_maximo - pec[i].quant_estoque;

            float valorTotPeca = pec[i].preco_unitario * qtdComprar;

            valorTotalCompra += valorTotPeca;

            cout <<"\nCodigo: " << pec[i].codigo;
            cout <<"\nDescricao: " << pec[i].descricao;
            cout <<"\nQuantidade em estoque: " << pec[i].quant_estoque;
            cout <<"\nEstoque Maximo: " << pec[i].estoque_maximo;
            cout <<"\nQuantidade a ser comprada: " << qtdComprar;
            cout <<"\nValor total da compra " << valorTotPeca;

        }
    }
    if(achouPec == 0){
        cout <<"\nNão há pecas com estoque minimo abaixo...";
    }
    else{
        cout <<"\nValor total a ser gasto: " << valorTotalCompra << endl;
    }

    getch();
}

void exibirTotArrecadado(struct OrdensServico os[], int contOS,
                         struct Servicos ser[], int contSer,
                         struct Pecas pec[], int contPec) {
    cout <<"\nValor total arrecadado: ";
    float totalArrecadado = 0;

    // Se não houver nenhuma O.S. aberta, avisa e sai
    if (contOS == 0) {
        cout << "\nNenhuma Ordem de Servico foi aberta ate o momento.";
        getch();
        return;
    }

    // Percorre todas as Ordens de Serviço cadastradas
    for (int i = 0; i < contOS; i++) {
        float valorMaoObra = 0;
        float precoPeca = 0;

        // 1) Encontrar o valor da Mão de Obra do Serviço correspondente
        for (int j = 0; j < contSer; j++) {
            if (os[i].codigo_servico == ser[j].codigo) {
                valorMaoObra = ser[j].valor_mao_obra;
                break;
            }
        }

        // 2) Encontrar o preço unitário da Peça correspondente
        for (int k = 0; k < contPec; k++) {
            if (os[i].codigo_peca == pec[k].codigo) {
                precoPeca = pec[k].preco_unitario;
                break;
            }
        }

        // 8.1) Calcular o valor desta Ordem de Serviço específica
        float valorDestaOS = valorMaoObra + (os[i].quantidade_peca * precoPeca);

        // Mostra na tela o detalhe de cada O.S. (Opcional, mas os professores adoram)
        cout << "\nO.S. Numero: " << os[i].codigo 
             << " | Placa: " << os[i].placa_veiculo 
             << " | Valor: R$ " << valorDestaOS;

        // Acumula no faturamento geral da oficina
        totalArrecadado += valorDestaOS;
    }

    // 8.2) Exibe o valor total arrecadado ao final
    cout << "\n\n==============================================";
    cout << "\n>>> FATURAMENTO TOTAL DA OFICINA: R$ " << totalArrecadado << " <<<";
    cout << "\n==============================================\n";

    getch(); // Pausa a tela abaixo do menu para leitura
}

int main(){
    
    struct Pecas arqPecas[100];
    struct Servicos arqServicos[100];
    struct Clientes arqClientes[100];
    struct Cidades arqCidades[100];
    struct Veiculos arqVeiculos[100];
    struct Mecanicos arqMecanicos[100];
    struct OrdensServico arqOS[100];
    
    int contPec = 0;
    int contSer = 0;
    int contCli = 0;
    int contCid = 0;
    int contVei = 0;
    int contMec = 0;
    int contOS = 0;

    leitura_cidades(arqCidades, contCid);
    leitura_servicos(arqServicos, contSer);
    leitura_pecas(arqPecas, contPec);
    
    int op; // Variável para ler a opção do menu
    
    // --- INÍCIO DO MENU ---
    do {
        system("clear"); // Limpa a tela a cada volta do menu (ou "cls" se for no Windows direto)
        cout << "\n================ MENU OFICINA ================";
        cout << "\n2 - Inclusao de Clientes";
        cout << "\n3 - Inclusao de Veiculos";
        cout << "\n4 - Inclusao de Mecanicos";
        cout << "\n5 - Abertura de Ordem de Servico";
        cout << "\n6 - Consultar Dados de uma Peca";
        cout << "\n7 - Relatorio de Estoque Baixo";
        cout << "\n8 - Faturamento Total das O.S.";
        cout << "\n0 - Sair do Programa";
        cout << "\n==============================================";
        cout << "\nEscolha uma opcao: ";
        cin >> op;

        switch(op) {
            case 2:
                inclusaoClientes(arqClientes, contCli, arqCidades, contCid);
                break;
                
            case 3:
                inclusaoVeiculos(arqVeiculos, contVei, arqClientes, contCli);
                break;
                
            case 4:
                inclusaoMecanicos(arqMecanicos, contMec);
                break;
                
            case 5:
                aberturaOrdemServico(arqVeiculos, contVei, arqClientes, contCli, arqMecanicos, contMec, arqServicos, contSer, arqPecas, contPec, arqOS, contOS);
                break;
                
            case 6:
                consultarPeca(arqPecas, contPec);
                break;
                
            case 7:
                exibirEstoque(arqPecas, contPec); // (ou relatorioEstoqueBaixo, o nome que deu à função do item 7)
                break;
            
            case 8:
                exibirTotArrecadado(arqOS, contOS, arqServicos, contSer, arqPecas, contPec);
                break;

            case 0:
                cout << "\nSaindo do sistema... Obrigado!";
                getch();
                break;

            default:
                cout << "\nOpcao invalida! Tente novamente.";
                getch();
                break;
        }

    } while (op != 0); // O loop continua rodando até o usuário digitar 0

    return 0;
}
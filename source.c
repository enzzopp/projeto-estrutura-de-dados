#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## FORM SETTINGS ##
// ESTRUTURAS DOS REGISTROS

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Form {
    char name[50];
    int age;
    char id[20];
    Date entry;
} Form;


// FUNCAO QUE FAZ INPUT DOS DADOS
Form create_form(){
    Form data;

    printf("Digite o nome: ");
    scanf(" %[^\n]", data.name);

    printf("Digite a idade: ");
    scanf("%d", &data.age);

    printf("Digite o ID: ");
    scanf("%s", data.id);

    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &data.entry.day, &data.entry.month, &data.entry.year);

    return data;

}


// FUNCAO QUE MOSTRA OS DADOS
void show_form(Form data){
    printf("\n");
    
    printf("\x1b[33m--------------------------------------\x1b[0m\n");
    printf("Nome: %s\n", data.name);
    printf("Idade: %d\n", data.age);
    printf("ID: %s\n", data.id);
    printf("Data de entrada: %d/%d/%d\n", data.entry.day, data.entry.month, data.entry.year);
    printf("\x1b[33m--------------------------------------\x1b[0m\n");
    printf("\n");
}

// ## SUBSCRIBE SETTINGS ##
// ESTRUTURAS DA LISTA ENCADEADA

typedef struct Cell {
    Form data;
    struct Cell* next;
} Cell;

typedef struct DLL {
    Cell* first;
    int len;
} DLL; 

DLL* create_list(){
    DLL* list = malloc(sizeof(DLL));
    list->first = NULL;
    list->len = 0;
    return list;
}

Cell* create_cell(){
    Form data = create_form();
    
    Cell* node = malloc(sizeof(Cell));
    node->data = data;
    node->next = NULL;
    return node;
}


// FUNCAO QUE FAZ INPUT DO ID
void input_id(char id[]){
    printf("Digite o ID: ");
    scanf("%s", id);
}

// FUNCAO QUE VERIFICA SE O ID JA EXISTE
int id_exists(char id[], DLL* list){

    if(list->len == 0){
        return 0;
    }

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){

        if (strcmp(current->data.id, id) == 0){
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// FUNCAO QUE INSERE NA LISTA ENCADEADA
int insertDLL(DLL* list){
    Cell* new = create_cell();

    if(id_exists(new->data.id, list)){
        printf("\n\x1b[31mPaciente já cadastrado.\x1b[0m\n");
        return 0;
    }
    
    new->next = list->first;
    list->first = new;
    list->len++;
    
    system("clear");

    show_form(new->data);
    
    printf("\n\x1b[32mFicha cadastrada com sucesso!\x1b[0m\n");

    return 1;
}

// FUNCAO QUE MOSTRA A LISTA ENCADEADA
void showDLL(DLL* list){

    if (list->len == 0){
        printf("\n\x1b[31mNenhuma ficha cadastrada.\x1b[0m\n");
        return;
    }

    Cell* current = list->first;

    system("clear");

    printf("\n\x1b[34mHá \x1b[0m\x1b[33m%d\x1b[0m \x1b[34mFicha(s) cadastrada(s):\x1b[0m\n", list->len);

    for (int i = 0; i < list->len; i++){
        show_form(current->data);
        current = current->next;
    }
}

// FUNCAO QUE CONSULTA UM REGISTRO NA LISTA ENCADEADA
int consultDLL(DLL* list){

    char id[20];
    input_id(id);

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){

        if (strcmp(current->data.id, id) == 0){
            system("clear");
            printf("\n\x1b[32mFicha encontrada com sucesso!\x1b[0m\n");
            show_form(current->data);
            return 1;
        }
        current = current->next;
    }
    printf("\n\x1b[31mPaciente não encontrado.\x1b[0m\n");
    return 0;
    
}

// FUNCAO QUE ATUALIZA UM REGISTRO NA LISTA ENCADEADA
int update_form(DLL* list){

    char id[20];
    input_id(id);

    system("clear");

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){

        if (strcmp(current->data.id, id) == 0){
            show_form(current->data);

            printf("Deseja alterar essa ficha? (\x1b[32m1 - Sim\x1b[0m | \x1b[31m0 - Não\x1b[0m): ");
            int option;
            scanf("%d", &option);

            if (option == 0){
                return 0;
            }

            printf("\n\x1b[33mDigite os novos dados:\x1b[0m\n\n");

            Form data = create_form();
            current->data = data;

            printf("\n\x1b[32mFicha atualizada com sucesso!\x1b[0m\n");
            show_form(current->data);
            return 1;
        }
        current = current->next;
    }
    printf("\n\x1b[31mPaciente não encontrado.\x1b[0m\n");
    return 0;
}

// FUNCAO QUE REMOVE UM REGISTRO NA LISTA ENCADEADA
int removeDLL(DLL* list){

    char id[20];
    input_id(id);

    system("clear");

    Cell* current = list->first;
    Cell* previous = NULL;

    for (int i = 0; i < list->len; i++){

        if (strcmp(current->data.id, id) == 0){
            show_form(current->data);

            if (previous == NULL){
                list->first = current->next;
            }
            else{
                previous->next = current->next;
            }

            free(current);
            list->len--;

            printf("\n\x1b[32mFicha removida com sucesso!\x1b[0m\n");
            return 1;
        }
        previous = current;
        current = current->next;
    }
    printf("\n\x1b[31mPaciente não encontrado.\x1b[0m\n");

    return 0;
}

// ## QUEUE SETTINGS ##
// ESTRUTURAS DA FILA

typedef struct Element {
    Form data;
    struct Element* next;
    struct Element* previous;
} Element;

typedef struct Queue {
    Element* head;
    Element* tail;
    int len;
} Queue;

Queue* create_queue(){
    Queue* queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->len = 0;
    return queue;
}

Element* create_element(DLL* list){

    Element* element = malloc(sizeof(Element));

    char id[20];
    input_id(id);

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){

        if (strcmp(current->data.id, id) == 0){
            element->data = current->data;
            return element;
        }
        current = current->next;
    }
    return NULL;
    
}

// FUNCAO QUE ENFILEIRA UM REGISTRO NA FILA
void enqueue(DLL* list, Queue* queue){

    Element* new = create_element(list);

    system("clear");

    if (new == NULL){
        printf("\n\x1b[31mPaciente não encontrado.\x1b[0m\n");
        return;
    }

    if (queue->len == 0){
        queue->head = new;
        queue->tail = new;
        queue->len++;
    }
    else{
        queue->tail->next = new;
        new->previous = queue->tail;
        queue->tail = new;
        queue->len++;
    }

    printf("\n\x1b[32mPaciente enfileirado com sucesso!\x1b[0m\n");
    printf("\n\x1b[34mHá \x1b[0m\x1b[33m%d\x1b[0m \x1b[34mpaciente(s) a frente de %s\x1b[0m\n", queue->len-1, new->data.name);
}

// FUNCAO QUE DESENFILEIRA UM REGISTRO NA FILA NO CASO O PRIMEIRO
void dequeue(Queue* queue){

    system("clear");

    if (queue->len > 0){
        Element* aux = queue->head;

        show_form(aux->data);

        printf("Deseja atender o(a) paciente \x1b[33m%s\x1b[0m? (\x1b[32m1 - Sim\x1b[0m | \x1b[31m0 - Não\x1b[0m): ", aux->data.name);
        int option;
        scanf("%d", &option);

        if (option == 0){
            return;
        }

        if (queue->len == 1){
            queue->head = NULL;
            queue->tail = NULL;
            queue->len--;
            printf("\n\x1b[32mPaciente atendido com sucesso!\x1b[0m\n");
            free(aux);
            return;
        }

        queue->head = aux->next;
        queue->head->previous = NULL;
        queue->len--;

        printf("\n\x1b[32mPaciente atendido com sucesso!\x1b[0m\n");

        free(aux);
    }
    else{
        printf("\n\x1b[31mA fila está vazia.\x1b[0m\n");
    }
}

// FUNCAO QUE MOSTRA A POSICAO DE UM REGISTRO NA FILA PELO ID
void show_position(Queue* queue){

    system("clear");

    if (queue->len == 0){
        printf("\n\x1b[31mNenhum paciente na fila.\x1b[0m\n");
        return;
    }

    char id[20];
    input_id(id);

    Element* current = queue->head;

    for (int i = 0; i < queue->len; i++){

        if (strcmp(current->data.id, id) == 0){
            printf("\n\x1b[34mHá \x1b[0m\x1b[33m%d\x1b[0m \x1b[34mpaciente(s) a frente de %s\x1b[0m\n", i, current->data.name);
            return;
        }
        current = current->next;
    }
    printf("\n\x1b[31mPaciente não encontrado.\x1b[0m\n");
}

// FUNCAO QUE MOSTRA A FILA
void show_queue(Queue* queue){

    system("clear");

    if (queue->len == 0){
        printf("\n\x1b[31mNenhum paciente na fila.\x1b[0m\n");
        return;
    }
    
    Element* current = queue->head;

    printf("\n\x1b[34mHá \x1b[0m\x1b[33m%d\x1b[0m \x1b[34mpaciente(s) na fila de atendimento:\x1b[0m\n\n", queue->len);

    printf("Deseja listar a fila? (\x1b[32m1 - Sim\x1b[0m | \x1b[31m0 - Não\x1b[0m): ");

    int option;
    scanf("%d", &option);

    if (option == 0){
        return;
    }

    for (int i = 0; i < queue->len; i++){

        show_form(current->data);

        current = current->next;
    }
}

// ## SEARCH SETTINGS BINARY TREE ##
// ESTRUTURAS DA ARVORE BINARIA

typedef struct Node{
	Form data;
    int value;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} Node;

typedef struct Tree{
	Node* root;
	int len;
} Tree;

Node* create_node(Tree* tree, Form data, int value){
	Node* new = malloc(sizeof(Node));
	new->right = NULL;
	new->left = NULL;
	new->parent = NULL;
    new-> value = value;
	new->data = data;
	
	return new;
}

Tree* create_tree(){
	Tree* tree = malloc(sizeof(Tree));
	tree->root = NULL;
	tree->len = 0;

	return tree;
}

// FUNCAO QUE INSERE NA ARVORE BINARIA UM VALOR DE ACORDO COM O FILTRO ESCOLHIDO
void insertTree(Tree* tree, Form data, int value){

    // CADA NÓ ARMAZENA UM VALOR E O REGISTRO QUE CONTEM ESSE VALOR
    Node* new = create_node(tree, data, value);

	if (tree->len == 0){
        tree->root = new;
        tree->len++;
        return;
    }

    Node* current = tree->root;
    Node* previous = NULL;

    while(current != NULL){
        previous = current;

        if(value < current->value){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }

    (value < previous->value) ? (previous->left = new) : (previous->right = new);
    new->parent = previous;

    tree->len++;
}

// FUNCAO QUE LIMPA A ARVORE BINARIA PARA CADA FILTRAGEM FEITA
void clearTree(Node* root){
    if (root != NULL){
        clearTree(root->left);
        clearTree(root->right);
        free(root);
    }
}

// FUNCAO QUE MOSTRA A ARVORE BINARIA CRESCENTE
void showTree(Node* root){
    if (root != NULL){
        showTree(root->left);
        show_form(root->data);
        showTree(root->right);
    }
}

// FUNCAO QUE CRIA UMA ARVORE BINARIA FILTRADA PELO DIA
void search_by_day(Tree* tree, DLL* list){

    if (list->len == 0){
        printf("\n\x1b[31mNenhuma ficha cadastrada.\x1b[0m\n");
        return;
    }

    clearTree(tree->root);
    tree->len = 0;

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){
        insertTree(tree, current->data, current->data.entry.day);
        current = current->next;
    }
    showTree(tree->root); 
}

// FUNCAO QUE CRIA UMA ARVORE BINARIA FILTRADA PELO MES
void search_by_month(Tree* tree, DLL* list){

    if (list->len == 0){
        printf("\n\x1b[31mNenhuma ficha cadastrada.\x1b[0m\n");
        return;
    }

    clearTree(tree->root);
    tree->len = 0;

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){
        insertTree(tree, current->data, current->data.entry.month);
        current = current->next;
    }
    showTree(tree->root);
}

// FUNCAO QUE CRIA UMA ARVORE BINARIA FILTRADA PELO ANO
void search_by_year(Tree* tree, DLL* list){

    if (list->len == 0){
        printf("\n\x1b[31mNenhuma ficha cadastrada.\x1b[0m\n");
        return;
    }

    clearTree(tree->root);
    tree->len = 0;

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){
        insertTree(tree, current->data, current->data.entry.year);
        current = current->next;
    }
    showTree(tree->root); 
}

// FUNCAO QUE CRIA UMA ARVORE BINARIA FILTRADA PELA IDADE
void search_by_age(Tree* tree, DLL* list){

    if (list->len == 0){
        printf("\n\x1b[31mNenhuma ficha cadastrada.\x1b[0m\n");
        return;
    }

    clearTree(tree->root);
    tree->len = 0;

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){
        insertTree(tree, current->data, current->data.age);
        current = current->next;
    }
    showTree(tree->root); 
}

// FUNCAO QUE CRIA UMA ARVORE BINARIA FILTRADA PELA ORDEM ALFABETICA
void search_by_alphabet(Tree* tree, DLL* list){

    if (list->len == 0){
        printf("\n\x1b[31mNenhuma ficha cadastrada.\x1b[0m\n");
        return;
    }

    clearTree(tree->root);
    tree->len = 0;

    Cell* current = list->first;

    int letter;

    for (int i = 0; i < list->len; i++){
        letter = current->data.name[0];
        insertTree(tree, current->data, letter);
        current = current->next;
    }
    showTree(tree->root); 
}

// ## READ AND WRITE SETTINGS ##

// FUNCAO QUE TRANFORMA O REGISTRO LIDO DO ARQUIVO BIN PARA UM REGISTRO DA LISTA ENCADEADA
void push_forms_in_list(DLL* list, Form data){

    Cell* new = malloc(sizeof(Cell));

    new->data = data;
    new->next = list->first;

    list->first = new;
    list->len++;
}

// FUNCAO QUE LIMPA A LISTA
void clear_list(DLL* list){

    Cell* current = list->first;

    for (int i = 0; i < list->len; i++){
        Cell* aux = current;
        current = current->next;
        free(aux);
    }
    list->first = NULL;
    list->len = 0;
}

// FUNCAO QUE ESCREVE NO ARQUIVO BIN OS REGISTROS DA LISTA ENCADEADA
void write_bin(DLL* list) {

    system("clear");

    int len = list->len;

    Cell* current = list->first;

    FILE *arq = fopen("forms.bin", "wb");

    if (arq){
        for (int i = 0; i < len; i++){
            fwrite(&current->data, sizeof(Form), 1, arq);
            current = current->next;
        }
        fclose(arq);
        printf("\n\x1b[32mArquivo salvo com sucesso!\x1b[0m\n");
        printf("\n\x1b[34mForam adicionados \x1b[0m\x1b[33m%d\x1b[0m \x1b[34mregistro(s) em \x1b[0m\x1b[33m./forms.bin\x1b[0m\x1b[0m\n", len);
    }
    else{
        printf("\x1b[31mErro ao salvar arquivo\x1b[0m\n");
    }
}

// FUNCAO QUE LE DO ARQUIVO BIN E CONVERTE PARA UMA LISTA ENCADEADA
void read_bin(DLL* list) {

    system("clear");
    
    clear_list(list);
    
    FILE *arq = fopen("forms.bin", "rb");

    if (arq) {
        Form form;
        while (fread(&form, sizeof(Form), 1, arq) == 1) {
            push_forms_in_list(list, form);
        }
        fclose(arq);
        printf("\n\x1b[32mArquivo carregado com sucesso!\x1b[0m\n");
        printf("\n\x1b[34mForam adicionados \x1b[0m\x1b[33m%d\x1b[0m \x1b[34mregistro(s)\x1b[0m\n", list->len);

    } else {
        printf("\x1b[31mErro ao carregar arquivo\x1b[0m\n");
    }
}


// ## MENU SETTINGS ##
// ITENS DE EXIBICAO DOS MENUS

void show_subscribe_menu(){
    system("clear");
    printf("\n");
    printf("-----------------------------------\n");
    printf("\x1b[36m%12sCadastro\x1b[0m\n", "");
    printf("-----------------------------------\n");
    printf("\n");
    printf("1 - Cadastrar\n");
    printf("2 - Consultar\n");
    printf("3 - Atualizar\n");
    printf("4 - Remover\n");
    printf("5 - Listar\n");
    printf("0 - Voltar\n");
    printf("\n");
}

void show_save_load_menu(){
    system("clear");
    printf("\n");
    printf("-----------------------------------\n");
    printf("\x1b[36m%9sCarregar/Salvar\x1b[0m\n", "");
    printf("-----------------------------------\n");
    printf("\n");
    printf("1 - Carregar\n");
    printf("2 - Salvar\n");
    printf("3 - Limpar\n");
    printf("0 - Voltar\n");
    printf("\n");
}

void show_service_menu(){
    system("clear");
    printf("\n");
    printf("-----------------------------------\n");
    printf("\x1b[36m%12sAtendimento\x1b[0m\n", "");
    printf("-----------------------------------\n");
    printf("\n");
    printf("1 - Enfileirar paciente\n");
    printf("2 - Atender paciente\n");
    printf("3 - Posição do paciente na fila\n");
    printf("4 - Listar fila de atendimento\n");
    printf("0 - Voltar\n");
    printf("\n");
}

void show_search_menu(){
    system("clear");
    printf("\n");
    printf("-----------------------------------\n");
    printf("\x1b[36m%12sPesquisa\x1b[0m\n", "");
    printf("-----------------------------------\n");
    printf("\n");
    printf("1 - Filtrar por dia\n");
    printf("2 - Filtrar por mês\n");
    printf("3 - Filtrar por ano\n");
    printf("4 - Filtrar por idade\n");
    printf("5 - Filtrar por ordem alfabética\n");
    printf("0 - Voltar\n");
    printf("\n");
}

void show_about_menu(){
    system("clear");
    printf("\n");
    printf("-----------------------------------\n");
    printf("\x1b[36m%14sSobre\x1b[0m\n", "");
    printf("-----------------------------------\n");
    printf("\n");
    printf("Desenvolvido por:\n");
    printf("\x1b[33mEnzo Pacheco Porfirio\x1b[0m\n");
    printf("\x1b[33mAna Beatriz de Souza\x1b[0m\n");
    printf("\n");
    printf("Ciclo: \x1b[33mVespertino\x1b[0m\n\n");
    printf("Curso: \x1b[33mCiência da Computação\x1b[0m\n\n");
    printf("Disciplina: \x1b[33mEstrutura de Dados\x1b[0m\n\n");
    printf("Data: \x1b[33m10/11/2023\x1b[0m\n\n");
}

void show_main_menu(){
    system("clear");
    printf("\n");
    printf("-----------------------------------\n");
    printf("\x1b[36m%3sSistema de Gestão Hospitalar\x1b[0m\n", "");
    printf("-----------------------------------\n");
    printf("\n");
    printf("1 - Cadastro\n");
    printf("2 - Atendimento\n");
    printf("3 - Pesquisa\n");
    printf("4 - Carregar/Salvar\n");
    printf("5 - Sobre\n");
    printf("0 - Sair\n");
    printf("\n");
}

void input_option(int option){
    printf("Digite a opção: ");
    scanf("%d", &option);
}

void press_to_continue(){
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

// ## MAIN ##

// FUNCAO PRINCIPAL QUE PRINTA OS MENUS E CHAMA AS FUNCOES DE ACORDO COM A OPCAO ESCOLHIDA
int main(){

    // INICIALIZACAO DAS ESTRUTURAS
    DLL* list = create_list();
    Queue* queue = create_queue();
    Tree* tree = create_tree();

    while(1){

        show_main_menu();

        int option;

        printf("Digite a opção: ");
        scanf("%d", &option);

        system("clear");

        switch (option){
            case 1:
                while(option != 0){

                    show_subscribe_menu();

                    printf("\nDigite a opção: ");
                    scanf("%d", &option);

                    switch (option){
                        case 1:
                            insertDLL(list);
                            press_to_continue();
                            break;
                        case 2:
                            consultDLL(list);
                            press_to_continue();
                            break;
                        case 3:
                            update_form(list);
                            press_to_continue();
                            break;
                        case 4:
                            removeDLL(list);
                            press_to_continue();
                            break;
                        case 5:
                            showDLL(list);
                            press_to_continue();
                            break;
                        case 0:
                            break;
                        default:
                            printf("\n\x1b[31mOpção Inválida\x1b[0m\n");
                            press_to_continue();
                            break;
                    }
                }
                break;

            case 2:
                while(option != 0){

                    show_service_menu();

                    printf("\nDigite a opção: ");
                    scanf("%d", &option);


                    switch (option){
                        case 1:
                            enqueue(list, queue);
                            press_to_continue();
                            break;
                        case 2:
                            dequeue(queue);
                            press_to_continue();
                            break;
                        case 3:
                            show_position(queue);
                            press_to_continue();
                            break;
                        case 4:
                            show_queue(queue);
                            press_to_continue();
                            break;
                        case 0:
                            break;
                        default:
                            printf("\n\x1b[31mOpção Inválida\x1b[0m\n");
                            press_to_continue();
                            break;
                    }
                }
                break;

            case 3:
                while(option != 0){

                    show_search_menu();

                    printf("\nDigite a opção: ");
                    scanf("%d", &option);

                    switch (option){
                        case 1:
                            search_by_day(tree, list);
                            press_to_continue();
                            break;
                        case 2:
                            search_by_month(tree, list);
                            press_to_continue();
                            break;
                        case 3:
                            search_by_year(tree, list);
                            press_to_continue();
                            break;
                        case 4:
                            search_by_age(tree, list);
                            press_to_continue();
                            break;
                        case 5:
                            search_by_alphabet(tree, list);
                            press_to_continue();
                            break;
                        case 0:
                            break;
                        default:
                            printf("\n\x1b[31mOpção Inválida\x1b[0m\n");
                            press_to_continue();
                            break;
                    }
                }
                break;
            
            case 4:
                show_save_load_menu();

                printf("\nDigite a opção: ");
                scanf("%d", &option);

                switch (option){
                    case 1:
                        read_bin(list);
                        press_to_continue();
                        break;
                    case 2:
                        write_bin(list);
                        press_to_continue();
                        break;
                    case 3:
                        remove("forms.bin");
                        printf("\n\x1b[32mArquivo apagado com sucesso!\x1b[0m\n");
                        press_to_continue();
                        break;
                    case 0:
                        break;
                    default:
                        printf("\n\x1b[31mOpção Inválida\x1b[0m\n");
                        press_to_continue();
                        break;
                }
                break;
            
            case 5:
                show_about_menu();
                press_to_continue();
                break;

            case 0:
                printf("\nPrograma Finalizado!\n");
                return 0;

            default:
                printf("\n\x1b[31mOpção Inválida\x1b[0m\n");
                press_to_continue();
                break;
        }
    }
    return 0;
}
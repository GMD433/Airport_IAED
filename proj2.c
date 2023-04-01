/*
    * File: proj2.c
    * Autor: Gustavo Manuel Cabral de Mascarenhas Diogo
    * Descricao: Programa que simula um gestor de aeroportos que pode adicionar e listar aeroportos,voo e reservas, sendo 
    * que os ultimos dois podem tambem ser eliminados, num espaço de dois anos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj2.h"

/* Funcao que adiciona aeroportos ao sistema 
    * airport *airports - vetor de structs que armazena os aeroportos
    * int *i - numero de aeroportos na struct nao vazios
    * A funcao verifica se atingiu o numero de aeroportos maximo no sistema,se o codigo doaeroporto e valido e imprime o codigo
    * do aeroporto no caso de o conseguir adicionar ao vetor
*/
void add_airport(airport *airports,int *i){ 
    int n,k;
    
    scanf("%s %s %[^\n]s",airports[*i].id, airports[*i].country,airports[*i].city);
    
    if(strlen(airports[*i].id) < 3){
        printf("invalid airport ID\n");
        return;  
        }

    if(*i == MAX_AIRPORTS-1){
        printf("too many airports\n");
        return;
    }
    
    for (n = 0; n <= *i; n++){
        for (k = n + 1; k <= *i; k++){
            if (strcmp(airports[n].id,airports[k].id) == 0){
                printf("duplicate airport\n");
                return;
            }
        }
    }
    printf("airport %s\n",airports[*i].id);
    (*i)++;
}
/* Funcao que lista todos aeroportos no sistema por ordem alfabetica de codigo ou lista os aeroportos pedidos
    * flight *flights - vetor de structs que armazena os voos
    * airport *airports - vetor de structs que armazena os aeroportos
    * int *j - numero de voos no vetor nao vazios
    * int *i - numero de aeroportos no vetor nao vazios
    * A funcao verifica ,se dado o input, se o aeroporto esta registado e verfica tambem se ha voos que partem dos aeroportos
    * registados, regista o seu numero  no vetor de aeroportos e lista-os conjuntamente com o resto da informacao do aeroporto
    * em questao
*/
void list_airports(flight *flights,airport *airports,int *j,int*i){
    int n,k,m,elem;
    char l,line[50];
    char *str;
    airport temp;
    copy_id copy[MAX_AIRPORTS] = {{{' '}}};

    for (n = 0;n < *i; n++){
        for(k = 0; k < *j; k++){
            if (strcmp(airports[n].id,flights[k].out_ap_id) == 0){
                airports[n].n_flight += 1;
            }
        }
    } 
    
    l = getchar();
    
    if(l == '\n'){
        for(n = 0;n < *i-1;n++){
            for (k = n+1; k <= *i-1; k++){ 
                if (airports[n].id[0] > airports[k].id[0]){
                    temp = airports[n];
                    airports[n] = airports[k];
                    airports[k] = temp;
                }
                else if (airports[n].id[0] == airports[k].id[0] && airports[n].id[1] > airports[k].id[1]){
                            temp = airports[n];
                            airports[n] = airports[k];
                            airports[k] = temp;
                }
                else if (airports[n].id[0] == airports[k].id[0] && airports[n].id[1] == airports[k].id[1] && airports[n].id[2] > airports[k].id[2]){
                                temp = airports[n];
                                airports[n] = airports[k];
                                airports[k] = temp;
                }
            }
        }
        
        for(n = 0;n <= *i-1;n++){
            printf("%s %s %s %d\n",airports[n].id, airports[n].city,airports[n].country,airports[n].n_flight);
        }
    }
    else if(l == ' '){
        fgets(line,50,stdin);
        line[strcspn(line,"\n")] = 0;
        str = strtok(line," ");
        n = 0;
        while(str != NULL){
            strcpy(copy[n].c_id,str);
            str = strtok(NULL," ");
            n++;
        }
        for (k = 0; k < n; k++){
            elem = 0;
            for (m= 0; m < *i; m++){ 
                if(strcmp(airports[m].id,copy[k].c_id) == 0){
                    elem = 1;
                    printf("%s %s %s %d\n",airports[m].id, airports[m].city,airports[m].country,airports[n].n_flight);
                }
                else if ( m == *i-1 && strcmp(airports[m].id,copy[k].c_id) != 0 && elem == 0){
                    printf("%s: no such airport ID\n",copy[k].c_id);
                }
            }
        }
    
    }
    
}

/*Funcao que adiciona voos ao sistema ou lista-os
    * flight *flights - vetor de structs que armazena os voos
    * airport *airports - vetor de structs que armazena os aeroportos
    * int *j - numero de voos no vetor nao vazios
    * int *i - numero de aeroportos no vetor nao vazios
    * char date[] - data atual do sistema
    * A funcao verifica se o id do voo e valido,se ela ja existe no sistema, se o sistema ja tem o maximos de voos
    * permitidos, se a data e mais antiga que a atual ou se a mais de um ano no futuro, se o voo dura mais de 12 horas
    * e se leva mais que 10 e menos que 100 pessoas.Assim, adiciona o voos ,ou no caso de nao receber input, lista os voos
    * por ordem de criacao
*/
void add_flight(flight *flights,airport *airports,int *j,int *i,char date[]){
    long int k,n,hd,md,ht,mt,hc,mc,at,mot,dt,dc,moc,ac,dat,mat,aat;
    char l;
    
    l = getchar();
    if (l == '\n') {
        for(k = 0; k < *j; k++){
            printf("%s %s %s %s %s\n",flights[k].flight_id,flights[k].out_ap_id,flights[k].in_ap_id,flights[k].flight_date,flights[k].flight_time);
        }
    }
    else {
        scanf("%s %s %s %s %s %s %d",flights[*j].flight_id,flights[*j].out_ap_id,flights[*j].in_ap_id,flights[*j].flight_date,flights[*j].flight_time,flights[*j].duration,&flights[*j].capacity);
        
        k = strlen(flights[*j].flight_id);
        
        if ((flights[*j].flight_id[0] < 'A' || flights[*j].flight_id[0] > 'Z') || (flights[*j].flight_id[1] < 'A' || flights[*j].flight_id[1] > 'Z' ) || (k < 3) || (k > 6 )){
            for (n = 2; n < k; n++){
                if(flights[*j].flight_id[n] >= '0' && flights[*j].flight_id[n] <= '9'){
                    printf("invalid flight code\n");
                    return;
                }
            }
        }
        
        for(n = 0; n < *j; n++){
            if(strcmp(flights[n].flight_id,flights[*j].flight_id) == 0 && strcmp(flights[n].flight_date,flights[*j].flight_date) == 0){
                printf("flight already exists\n");
                return;
            }
        }

        if (*j == MAX_FLIGHTS-1){
            printf("too many flights\n");
            return;
        }
        
        for (k = 0; k < *i; k++){
            if (strcmp(flights[*j].in_ap_id,airports[k].id) == 0){
                break;
            }
            else if(k == *i-1 && strcmp(flights[*j].in_ap_id,airports[k].id) != 0 ){ 
                printf("%s: no such airport ID\n",flights[*j].in_ap_id);
                return;
            }      
        }
        
        for (k = 0; k < *i; k++){
            if (strcmp(flights[*j].out_ap_id,airports[k].id) == 0){
                break;
            }
            else if(k == *i-1 && strcmp(flights[*j].out_ap_id,airports[k].id) != 0 ){ 
                printf("%s: no such airport ID\n",flights[*j].out_ap_id);
                return;
            }      
        }
        sscanf(flights[*j].duration,"%ld:%ld",&hd,&md);
        
        sscanf(flights[*j].flight_time,"%ld:%ld",&ht,&mt);
        
        sscanf(flights[*j].flight_date,"%ld-%ld-%ld",&dt,&mot,&at);
        
        sscanf(date,"%ld-%ld-%ld",&dat,&mat,&aat);
        
        if (aat > at || at < 2022 || at > 2023){
            printf("invalid date\n");
            return;
        }
        else if (aat == at && mat > mot){
            printf("invalid date\n");
            return;
        }
        else if (aat == at && mat == mot && dat >dt){
            printf("invalid date\n");
            return;
        }
        else if(at-aat == 1 && (mot-mat > 0 || dt - dat > 0)){
            printf("invalid date\n");
            return;
        }
        if(hd > DURATION_TIME){
            printf("invalid duration\n");
            return;
        }
        else if (hd == DURATION_TIME && md > 0){
            printf("invalid duration\n");
            return;
        }
        if (flights[*j].capacity < MIN_PASSENGERS || flights[*j].capacity > MAX_PASSENGERS){
            printf("invalid capacity\n");
            return;
        }
        
        flights[*j].flight_hour = ht;
        
        flights[*j].flight_minutes = mt;
        
        flights[*j].flight_day = dt;
        
        flights[*j].flight_month = mot;
        
        flights[*j].flight_year = at;
        
        mc = md + mt;
        if(mc >= 60){
            mc -= 60;
            hd += 1;
        }
        hc = hd + ht;
        if (hc >= 24){
            hc -= 24;
            dt += 1;
        }
        dc = dt;
        if (dt > 30 && mot%2 ==0 && mot <=7 && mot !=2){
            dc -= 30;
            mot += 1;
        }
        else if (dt > 31 && mot%2 !=0 && mot !=2){
            dc -= 31;
            mot += 1;
        }
        else if (dt > 28 && mot == 2){
            dc -= 28;
            mot += 1;
        }
        else if (dt > 31 && mot%2 ==0 && mot >=7){
            dc -= 31;
            mot += 1;
        }
        else if (dt > 30 && mot%2 !=0 && mot >=7){
            dc -= 30;
            mot += 1;
        }
        moc = mot;
        if (mot > 12 && at <= 2023 && at == 2022){
            moc = mot -12;
            at +=1;
        }
        ac = at;
        
        flights[*j].coming_hour = hc;
        
        flights[*j].coming_minutes = mc;
        
        flights[*j].coming_day = dc;
        
        flights[*j].coming_month = moc;
        
        flights[*j].coming_year = ac;
        (*j)++;
    }
}

/*Funcao que lista todos os voos com partida de um aeroporto por ordem cronologica de partida
    * flight *flights - vetor de structs que armazena os voos
    * airport *airports - vetor de structs que armazena os aeroportos
    * int *j - numero de voos no vetor nao vazios
    * int *i - numero de aeroportos no vetor nao vazios
    * A funcao verifica se o aeroporto dado pelo utilizador esta no sistema e se sim
    * lista todos os voos que partem desse aeroporto
*/
void list_out_flights(airport *airports,flight *flights,int *j,int *i,char date[]){ 
    char out_flight[ID_AIRPORT];
    int n,k;
    flight temp;

    for(n = 0;n < *j;n++){
        for (k = n+1; k < *j; k++){ 
            if (flights[n].flight_year > flights[k].flight_year){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
            else if (flights[n].flight_year == flights[k].flight_year && flights[n].flight_month > flights[k].flight_month){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
            else if (flights[n].flight_year == flights[k].flight_year && flights[n].flight_month == flights[k].flight_month && flights[n].flight_day > flights[k].flight_day){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
            else if (flights[n].flight_year == flights[k].flight_year && flights[n].flight_month == flights[k].flight_month && flights[n].flight_day == flights[k].flight_day &&  flights[n].flight_hour > flights[k].flight_hour){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
            else if (flights[n].flight_year == flights[k].flight_year && flights[n].flight_month == flights[k].flight_month && flights[n].flight_day == flights[k].flight_day &&  flights[n].flight_hour == flights[k].flight_hour && flights[n].flight_minutes > flights[k].flight_minutes){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
        }
    }
    
    scanf("%s",out_flight);

    for (k = 0; k < *i; k++){
        if (strcmp(out_flight,airports[k].id) == 0){
            break;
        }
        else if (k ==*i-1 && strcmp(out_flight,airports[n].id) != 0){
                printf("%s: no such airport ID\n",out_flight);
                return;
        }
    }
    
    for(k = 0; k < *j; k++){
        if (strcmp(out_flight,flights[k].out_ap_id) == 0){
            if(strcmp(flights[k].flight_date,date) == 0 ){ 
                printf("%s %s %s %s\n",flights[k].flight_id,flights[k].in_ap_id,flights[k].flight_date,flights[k].flight_time);
            }
        }
    }
}   

/*Funcao que lista todos os voos com chegada de um aeroporto por ordem cronologica de chegada
    * flight *flights - vetor de structs que armazena os voos
    * airport *airports - vetor de structs que armazena os aeroportos
    * int *j - numero de voos no vetor nao vazios
    * int *i - numero de aeroportos no vetor nao vazios
    * A funcao verifica se o aeroporto dado pelo utilizador esta no sistema e se sim
    * lista todos os voos que chegam a esse aeroporto
*/
void list_in_flights(airport *airports,flight *flights,int *j,int *i){
    char in_flight[ID_AIRPORT];
    int n,k;
    flight temp;

    for(n = 0;n < *j;n++){
        for (k = n+1; k < *j; k++){ 
            if (flights[n].coming_year > flights[k].coming_year){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
                }
            else if (flights[n].coming_year == flights[k].coming_year && flights[n].coming_month > flights[k].coming_month){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
            else if (flights[n].coming_year == flights[k].coming_year && flights[n].coming_month == flights[k].coming_month && flights[n].coming_day > flights[k].coming_day){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
            else if (flights[n].coming_year == flights[k].coming_year && flights[n].coming_month == flights[k].coming_month && flights[n].coming_day == flights[k].coming_day &&  flights[n].coming_hour > flights[k].coming_hour){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
            else if (flights[n].coming_year == flights[k].coming_year && flights[n].coming_month == flights[k].coming_month && flights[n].coming_day == flights[k].coming_day &&  flights[n].coming_hour == flights[k].coming_hour && flights[n].coming_minutes > flights[k].coming_minutes){
                temp = flights[n];
                flights[n] = flights[k];
                flights[k] = temp;
            }
        }
    }
    
    scanf("%s",in_flight);

    for (k = 0; k < *i; k++){
        if (strcmp(in_flight,airports[k].id) == 0){
            break;
        }
        else if (k ==*i-1 && strcmp(in_flight,airports[n].id) != 0){
                printf("%s: no such airport ID\n",in_flight);
                return;
        }
    }


    for(k = 0; k < *j; k++){
        if (strcmp(in_flight,flights[k].in_ap_id)== 0){
            printf("%s %s %s %s\n",flights[k].flight_id,flights[k].out_ap_id,flights[k].coming_date,flights[k].coming_time);
        }
    }
}

/*Funcao que atualiza a data do sistema
    * char date[] - data atual do sistema
    * A funcao verifica se a data dada pelo utilizador nao e anterior
    * a data ja existente e se ela nao pertence aos anos fora do 
    * range(2022,2023)
*/    
void set_date(char date[]){
    char n_date[11];
    int d,m,a,nd,nm,na;
    
    scanf("%s",n_date);
    sscanf(date,"%d-%d-%d",&d,&m,&a);
    sscanf(n_date,"%d-%d-%d",&nd,&nm,&na);
    
    if(na > 2023){
        printf("invalid date\n");
    }
    else if(na < a){
        printf("invalid date\n");
    }
    else if(na == a && nm < m){
        printf("invalid date\n");
    }
    else if(na == a && nm == m && nd < d){
        printf("invalid date\n");
    }
    else if(na == a && nm == m && nd == d){
        printf("invalid date\n");
    }
    else{
        strcpy(date,n_date);
        printf("%s\n",date);
    }

    
}

/*Funcao auxiliar que organiza as reservas por ordem lexicográfica
    *reservation *reservations- vetor de structs que armazena reservas
    * int *k - numero de reservas no vetor nao vazios
    * A funcao compara as reservas,caracter a caracter, e procura se organizar por ordem lexicografica o vetor
*/
void sort_reservations(reservation *reservations,int *k){
    int i, j;
    reservation temp;


    for (i = 0; i < *k; i++){
        for(j = i+1; j <= *k ; j++){
            if (strcmp(reservations[i].reservation_id,reservations[j].reservation_id) > 0){
                temp = reservations[i];
                reservations[i] = reservations[j];
                reservations[j] = temp;
            }
        }
    }
}

/*Funcao que adiciona ou lista as reservas de um voo
    * flight *flights - vetor de structs que armazena os voos
    * reservation *reservations- vetor de structs que armazena reservas
    * int *j - numero de voos no vetor nao vazios
    * int *k - numero de reservas no vetor nao vazios
    * char date[] - data atual do sistema
    * A funcao distingue se recebe o input para listar ou adicionar reservas e verifica se o codigo
    de reserva e menor que 10 caracteres e se esses sao todos maisculos ou digitos. Verifica tambem se
    o codigo do voo existe na data especificada, se o codigo de reserva e repetido,se o numero de passageiros
    da reserva criada excede o limite de passageiros no voo,se a data e mais antiga que a atual ou se a mais 
    de um ano no futuro e se o numero de passegeiros e um inteiro superior a 0
*/
void add_or_list_flight_reservation(flight *flights,reservation *reservations,int *k,int *j,char date[]){
    char l, temp_id[FLIGHT_CODE], temp_date[DATE_LEN];
    int m,dt,mot,at,dat,mat,aat,curr_passengers = 0;
    long unsigned int i;
    
    scanf("%s %s", temp_id,temp_date);

    l = getchar();
    if (l == '\n'){
        sscanf(reservations[*k].flight_date,"%d-%d-%d",&dt,&mot,&at);
        
        sscanf(date,"%d-%d-%d",&dat,&mat,&aat);
        
        if (aat > at || at < 2022 || at > 2023){
            printf("invalid date\n");
            return;
        }
        else if (aat == at && mat > mot){
            printf("invalid date\n");
            return;
        }
        else if (aat == at && mat == mot && dat >dt){
            printf("invalid date\n");
            return;
        }
        else if(at-aat == 1 && (mot-mat > 0 || dt - dat > 0)){
            printf("invalid date\n");
            return;
        }
        for (m = 0; m < *k; m++){
            if (strcmp(temp_id,reservations[m].flight_id) == 0 && strcmp(temp_date,reservations[m].flight_date) == 0){ 
                printf("%s %d\n", reservations[m].reservation_id, reservations[m].passengers);
            }
        }
    }
    else if ( l == ' '){
        strcpy(reservations[*k].flight_id,temp_id);
        strcpy(reservations[*k].flight_date,temp_date);
        
        reservations[*k].reservation_id = (char *) malloc(sizeof(reservations[*k].reservation_id)+10);
        scanf("%s %d", reservations[*k].reservation_id,&reservations[*k].passengers);

        for (i = 0; i < strlen(reservations[*k].reservation_id); i++){
            if (reservations[*k].reservation_id[i] < 'A' || reservations[*k].reservation_id[i] > 'Z'){
                if (reservations[*k].reservation_id[i] < '1' || reservations[*k].reservation_id[i] > '9'){
                    printf("invalid reservation code\n");
                    return;
                }
            }
        }
        if (strlen(reservations[*k].reservation_id) < 10){
            printf("invalid reservation\n");
            return;
        }
        for (m = 0; m <= *j; m++){
            if ((strcmp(flights[m].flight_id,reservations[*k].flight_id) == 0) && (strcmp(flights[m].flight_date,reservations[*k].flight_date) == 0)){
                break;
            }
            else if((m == *j) && (strcmp(flights[m].flight_id,reservations[*k].flight_id) != 0)){
                printf("%s: flight does not exist\n",reservations[*k].flight_id);
                return;
            }
            else if((m == *j) && (strcmp(flights[m].flight_date,reservations[*k].flight_date) != 0)){
                printf("%s: flight does not exist\n",reservations[*k].flight_id);
                return;
            }
        }
        for (m = 0; m < *k; m++){
            if (strcmp(reservations[*k].reservation_id,reservations[m].reservation_id) == 0){
                printf("%s: flight reservation already used\n",reservations[*k].reservation_id);
                return;
            }
        }
        for(m= 0; m < *k;m++){
            if((strcmp(reservations[m].flight_id,reservations[*k].flight_id) == 0) && (strcmp(reservations[m].flight_date,reservations[*k].flight_date) == 0)){
                curr_passengers += reservations[m].passengers;
            }
        }
        for(m = 0; m < *j; m++){
            if ((strcmp(flights[m].flight_id,reservations[*k].flight_id) == 0) && (strcmp(flights[m].flight_date,reservations[*k].flight_date) == 0)){
                if(curr_passengers + reservations[*k].passengers > flights[m].capacity){
                    printf("too many reservations\n");
                    return;
                }
            }
        }
        sscanf(reservations[*k].flight_date,"%d-%d-%d",&dt,&mot,&at);
        
        sscanf(date,"%d-%d-%d",&dat,&mat,&aat);
        
        if (aat > at || at < 2022 || at > 2023){
            printf("invalid date\n");
            return;
        }
        else if (aat == at && mat > mot){
            printf("invalid date\n");
            return;
        }
        else if (aat == at && mat == mot && dat >dt){
            printf("invalid date\n");
            return;
        }
        else if(at-aat == 1 && (mot-mat > 0 || dt - dat > 0)){
            printf("invalid date\n");
            return;
        }
        if (reservations[*k].passengers < 1){
        printf("invalid passenger number\n");
        return;
        }
        
        sort_reservations(reservations,k);
        (*k)++;
    }
}

/*Funcao que elimina reservas ou voos do sistema
    * flight *flights - vetor de structs que armazena os voos
    * reservation *reservations- vetor de structs que armazena reservas
    * int *j - numero de voos no vetor nao vazios
    * int *k - numero de reservas no vetor nao vazios
    * A funcao vai receber input de um codigo de reserva ou de voo e vai procurar no vetor de reservas ou no
    vetor de voos pelo codigo e vai apaga-lo do sistema e reorganiza o vetor e o seu tamanho
*/
void eliminate_flights_or_reservations(flight *flights,reservation *reservations,int *k,int *j,char date[]){
    char temp[65535];
    int i,m,dat,mat,aat,dt,mot,at;
    
    scanf("%s", temp);

    sscanf(date,"%d-%d-%d",&dat,&mat,&aat);

    
    for(i = 0; i < *j; i++){
        sscanf(flights[i].flight_date,"%d-%d-%d",&dt,&mot,&at);
        if(strcmp(temp,flights[i].flight_id) == 0){
            if (at < aat){ 
                for (m = i; m < *j; m++){
                    flights[m] = flights[m+1];
                }
            }
            else if(at == aat && mot < mat){
                for (m = i; m < *j; m++){
                    flights[m] = flights[m+1];
                }
            }  
            else if(at == aat && mot == mat && dt < dat){
                for (m = i; m < *j; m++){
                    flights[m] = flights[m+1];
                }
            }
            else{
                printf("not found\n");
                return;
            }   
        }
        (*j)--;
        return;
    }
    for(i = 0; i < *k; k++){
        if(strcmp(temp,reservations[i].reservation_id) == 0){
            for (m = i; m < *j; m++){
                reservations[m] = reservations[m+1];
            }
        (*k)--;
        return;
        }
    }
    printf("not found\n");
}

/*Funcao que trata dos comandos do sistema
    *a: adiciona aeroportos
    *l: lista aeroportos
    *v: adiciona voos
    *p: lista os voos com parida de um aeroporto
    *c: lista os voos com chegada a um aeroporto
    *r: adiciona uma reserva ou lista as reservas correspondentes a um voo
    *e: elimina um voo ou uma reserva
    *q: fecha o sistema
    *A funcao inicializa os vetores dos aeroportos,dos voos e as reservas e as posicoes nao vazias.Inicializa tambem
    a data do sistema e usa o char c para, atraves do input do utilizador, realizar as acoes do programa
*/
int main(){
    airport airports[MAX_AIRPORTS] = {{{' '},{' '},{' '},0}};
    flight flights[MAX_AIRPORTS] = {{{' '},{' '},{' '},{' '},{' '},{' '},{' '},{' '},0,0,0,0,0,0,0,0,0,0,0}};
    reservation* reservations = (reservation* )malloc(sizeof *reservations);
    int i = 0,j = 0,k = 0,m;
    char c;
    char date[11] = "01-01-2022";

    if (reservations == NULL){
        fprintf(stderr,"No memory\n");
        return 1;
    }

    while(1){
    c = getchar();

        switch(c){
                case 'a':
                    add_airport(airports,&i);
                    break;
                case 'l':
                    list_airports(flights,airports,&j,&i);
                    break;
                case 'v':
                    add_flight(flights,airports,&j,&i,date);
                    break;
                case 'p':
                    list_out_flights(airports,flights,&j,&i,date);
                    break;
                case 'c':
                    list_in_flights(airports,flights,&j,&i);
                    break;
                case 't':
                    set_date(date);
                    break;
                case 'r':
                    add_or_list_flight_reservation(flights,reservations,&k,&j,date);
                    break;
                case 'e':
                    eliminate_flights_or_reservations(flights,reservations,&k,&j,date);
                    break;
                case 'q':
                    if (k > 0){ 
                        for (m = 0;m < k; m++){ 
                        free(reservations[m].reservation_id);
                        }
                        free(reservations);
                    }
                    return 0;
        } 
    }
    return 0;
}
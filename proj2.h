/*  * File: proj1.h
    * Autor: Gustavo Manuel Cabral de Mascarenhas Diogo
    * Descricao: ficheiro header que contem as constantes e structs usadas no proj1.c 
*/


#define ID_AIRPORT 6
#define MAX_COUNTRY_LEN 31
#define MAX_CITY_LEN 51
#define MAX_AIRPORTS 41

#define FLIGHT_CODE 7

#define MIN_PASSENGERS 10
#define MAX_PASSENGERS 100

#define MAX_FLIGHT_DURATION 12
#define MAX_FLIGHTS 3001

#define DATE_LEN 11
#define TIME_LEN 6
#define DURATION 6
#define DURATION_TIME 12

/*struct de aeroportos*/
typedef struct{
    char id[ID_AIRPORT];
    char country[MAX_COUNTRY_LEN];
    char city[MAX_CITY_LEN];
    int n_flight;
} airport;


/*struct de voos*/
typedef struct{
    char flight_id[FLIGHT_CODE];
    char out_ap_id[ID_AIRPORT];
    char in_ap_id[ID_AIRPORT];
    char flight_date[DATE_LEN];
    char flight_time[TIME_LEN];
    char coming_date[DATE_LEN];
    char coming_time[TIME_LEN];
    char duration[DURATION];
    int capacity;
    int flight_hour;
    int flight_minutes;
    int flight_day;
    int flight_month;
    int flight_year;
    int coming_hour;
    int coming_minutes;
    int coming_day;
    int coming_month;
    int coming_year;

} flight;


/*struct de copia de IDs de aeroportos*/
typedef struct{
    char c_id[ID_AIRPORT];
} copy_id;

typedef struct {
	char flight_id[FLIGHT_CODE];
	char flight_date[DATE_LEN];
	int passengers;
    char *reservation_id;
} reservation;
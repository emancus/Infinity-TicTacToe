#include <stdio.h>
#include <string.h>

#define OLDEST_MV 5 /*5 By Default*/

// Function declaration
void print_screen(void);
void print_victory_screen(int result);
void print_deleting_screen(int position);
void clear_screen(void);
void selector(void);
void initialize_board(void);
int check_result(void);
int new_game(void);
int marker_changer(int position);
void marker_deleter(int position);

// Global variable
char a1=' ', a2=' ', a3=' ', b1=' ', b2=' ', b3=' ', c1=' ', c2=' ', c3=' ';
int curr_player=0, mv[10];

// MAIN Function
int main(){
    int new_game_flag=0;
    do{
        selector();
        new_game_flag = new_game();
    }while(new_game_flag!=0);
    return 0;
}

// Function implementation
void print_screen(void){
    printf(" %c | %c | %c ", a1, a2, a3);
    printf("\n-----------\n");
    printf(" %c | %c | %c ", b1, b2, b3);
    printf("\n-----------\n");
    printf(" %c | %c | %c ", c1, c2, c3);
}

void selector(void){
    int position=0, move_counter=0, is_a_valid_move=0, partita_avviata=0;;
    
    //inizializzazione nuova partita
    initialize_board(); 
    curr_player = 1, move_counter = 0, partita_avviata = 1;
    
    // Logica di controllo delle mosse e gestore della partita avviata
    while(partita_avviata == 1){
        curr_player = (move_counter%2 == 0) ? 1 : 2;
        do{
            do{
                clear_screen();
                move_counter < OLDEST_MV ? print_screen() : print_deleting_screen(mv[0]);
                printf("\tMossa N°=%d", move_counter);
                //printf("\t[Debug] - Array=[%d][%d][%d][%d][%d][%d][%d]", mv[0],mv[1],mv[2],mv[3],mv[4],mv[5],mv[6]);
                if(is_a_valid_move == 1){
                    printf("\n\nLa mossa non è valida, casella occupata!");
                }
                printf("\n\nGiocatore %d, fa la tua mossa: ", curr_player);
                scanf("%d", &position);
            }while(position <= 0 || position >= 10);
            is_a_valid_move = marker_changer(position);
        }while(is_a_valid_move == 1);
        move_counter++;
        
        //Logica di cancellazione della mossa 
        if(move_counter < OLDEST_MV+1){
            mv[move_counter-1] = position; 
        }else{
            marker_deleter(mv[0]);
            mv[OLDEST_MV] = position;
            for (int i=0; i<OLDEST_MV+1; i++){
                mv[i]=mv[i+1];
            }
        }    
        
        //Logica di controllo sul punteggio
        partita_avviata = check_result(); //se ritorna 1 si continua a giocare, altrimenti torna il risultato;  
    }
    
    // Stampa del risultato della partita
    clear_screen();
    print_victory_screen(partita_avviata);
    if(partita_avviata!=50){
        printf("\n\nHai vinto Giocatore %d\n", curr_player);
    }else{
        printf("\n\nGioco finito con un pareggio!\n");
    }
}

// marker_changer ritorna 1 se la mossa non è valida, altrimenti setta la mossa effettuata e ritorna 0 
int marker_changer(int position){
    switch (position) { 	
        case 1: 
            if(a1=='X' || a1=='O'){
                return 1;
            }else{
                a1 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            }
            break; 
        case 2: 
            if(a2=='X' || a2=='O'){
                return 1;
            }else{
                a2 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            }
            break; 
        case 3: 
            if(a3=='X' || a3=='O'){
                return 1;
            }else{
                a3 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            }
            break; 
        case 4: 
            if(b1=='X' || b1=='O'){
                return 1;
            }else{
                b1 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            } 
            break; 
        case 5: 
            if(b2=='X' || b2=='O'){
                return 1;
            }else{
                b2 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            }
            break; 
        case 6: 
            if(b3=='X' || b3=='O'){
                return 1;
            }else{
                b3 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            }
            break; 
        case 7: 
            if(c1=='X' || c1=='O'){
                return 1;
            }else{
                c1 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            } 
            break; 
        case 8: 
            if(c2=='X' || c2=='O'){
                return 1;
            }else{
                c2 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            }
            break; 
        case 9: 
            if(c3=='X' || c3=='O'){
                return 1;
            }else{
                c3 = (curr_player==1) ? 'X' : 'O'; 
                return 0;
            }
            break; 
        default:
            printf("[ERRORE] - Catastrophe in marker_changer");
            break;
    }
}

// marker_deleter cancella la prima mossa effettuta 5 mosse prima 
void marker_deleter(int position){
    switch (position) { 	
        case 1: 
            a1 = ' ' ; 
            break; 
        case 2: 
            a2 = ' ' ; 
            break; 
        case 3: 
            a3 = ' ' ; 
            break; 
        case 4: 
            b1 = ' ' ; 
            break; 
        case 5: 
            b2 = ' ' ; 
            break; 
        case 6: 
            b3 = ' ' ; 
            break; 
        case 7: 
            c1 = ' ' ; 
            break; 
        case 8: 
            c2 = ' ' ; 
            break; 
        case 9: 
            c3 = ' ' ; 
            break; 
        default:
            printf("[ERRORE] - Catastrophe in marker_deleter");
            break;
    }
}

int check_result(void){
   //      Controllo righe uguali           Controllo che celle non sono vuote
   if(      a1==a2 && a1==a3 && a2==a3      && a1!=' ' && a2!=' ' && a3!=' '){ 
       return 12;
   }else if(b1==b2 && b1==b3 && b2==b3      && b1!=' ' && b2!=' ' && b3!=' '){ 
       return 13;
   }else if(c1==c2 && c1==c3 && c2==c3      && c1!=' ' && c2!=' ' && c3!=' '){ 
       return 14;
   //      Controllo colonne uguali         Controllo che celle non sono vuote       
   }else if(a1==b1 && a1==c1 && b1==c1      && a1!=' ' && b1!=' ' && c1!=' '){ 
       return 22;
   }else if(a2==b2 && a2==c2 && b2==c2      && a2!=' ' && b2!=' ' && c2!=' '){ 
       return 23;
   }else if(a3==b3 && a3==c3 && b3==c3      && a3!=' ' && b3!=' ' && c3!=' '){ 
       return 24;
   //      Controllo diagonali uguali       Controllo che celle non sono vuote
   }else if(a1==b2 && a1==c3 && b2==c3      && a1!=' ' && b2!=' ' && c3!=' '){ 
       return 31;
   }else if(a3==b2 && a3==c1 && b2==c1      && a3!=' ' && b2!=' ' && c1!=' '){ 
       return 32;    
   //      Controllo caso di parità
   }else if(a1!=' ' && a2!=' ' && a3!=' ' && b1!=' ' && b2!=' ' && b3!=' '  && c1!=' ' && c2!=' ' && c3!=' '){ 
       return 50;   
   // Altrimenti si continua a giocare    
   }else{
       return 1;
   }
}


// Come print_screen() ma evidenzia la tripletta vincente
void print_victory_screen(int result){
    //Prima riga
    if(result==12){ 
        printf(" \x1b[31m%c | %c | %c\x1b[0m ", a1, a2, a3); 
    }else if(result==22 || result==31){
        printf(" \x1b[31m%c\x1b[0m | %c | %c ", a1, a2, a3); 
    }else if(result==23){
        printf(" %c | \x1b[31m%c\x1b[0m | %c ", a1, a2, a3); 
    }else if(result==24 || result==32){
        printf(" %c | %c | \x1b[31m%c\x1b[0m ", a1, a2, a3); 
    } else { 
        printf(" %c | %c | %c ", a1, a2, a3); 
    }
    printf("\n-----------\n");
    //Seconda riga
    if(result==13){ 
        printf(" \x1b[31m%c | %c | %c\x1b[0m ", b1, b2, b3); 
    }else if(result==22){
        printf(" \x1b[31m%c\x1b[0m | %c | %c ", b1, b2, b3);  
    }else if(result==23 || result==31 || result==32){
        printf(" %c | \x1b[31m%c\x1b[0m | %c ", b1, b2, b3);  
    }else if(result==24){
        printf(" %c | %c | \x1b[31m%c\x1b[0m ", b1, b2, b3);  
    } else { 
        printf(" %c | %c | %c ", b1, b2, b3);  
    }
    //Terza riga
    printf("\n-----------\n");
    if(result==14){ 
        printf(" \x1b[31m%c | %c | %c\x1b[0m ", c1, c2, c3);  
    }else if(result==22 || result==32){
        printf(" \x1b[31m%c\x1b[0m | %c | %c ", c1, c2, c3);   
    }else if(result==23){
        printf(" %c | \x1b[31m%c\x1b[0m | %c ", c1, c2, c3);  
    }else if(result==24 || result==31){
        printf(" %c | %c | \x1b[31m%c\x1b[0m ", c1, c2, c3);   
    } else { 
        printf(" %c | %c | %c ", c1, c2, c3);   
    }
}

// Come print_screen() ma evidenzia la prossima cancellazione
void print_deleting_screen(int position){
    switch (position) { 	
        case 1: 
            printf(" \x1b[34m%c\x1b[0m | %c | %c ", a1, a2, a3); printf("\n-----------\n"); printf(" %c | %c | %c ", b1, b2, b3); printf("\n-----------\n"); printf(" %c | %c | %c ", c1, c2, c3);  
            break; 
        case 2: 
            printf(" %c | \x1b[34m%c\x1b[0m | %c ", a1, a2, a3); printf("\n-----------\n"); printf(" %c | %c | %c ", b1, b2, b3); printf("\n-----------\n"); printf(" %c | %c | %c ", c1, c2, c3);  
            break; 
        case 3: 
            printf(" %c | %c | \x1b[34m%c\x1b[0m ", a1, a2, a3); printf("\n-----------\n"); printf(" %c | %c | %c ", b1, b2, b3); printf("\n-----------\n"); printf(" %c | %c | %c ", c1, c2, c3);  
            break; 
        case 4: 
            printf(" %c | %c | %c ", a1, a2, a3); printf("\n-----------\n"); printf(" \x1b[34m%c\x1b[0m | %c | %c ", b1, b2, b3); printf("\n-----------\n"); printf(" %c | %c | %c ", c1, c2, c3);  
            break; 
        case 5: 
            printf(" %c | %c | %c ", a1, a2, a3); printf("\n-----------\n"); printf(" %c | \x1b[34m%c\x1b[0m | %c ", b1, b2, b3); printf("\n-----------\n"); printf(" %c | %c | %c ", c1, c2, c3);  
            break; 
        case 6: 
            printf(" %c | %c | %c ", a1, a2, a3); printf("\n-----------\n"); printf(" %c | %c | \x1b[34m%c\x1b[0m ", b1, b2, b3); printf("\n-----------\n"); printf(" %c | %c | %c ", c1, c2, c3);  
            break; 
        case 7: 
            printf(" %c | %c | %c ", a1, a2, a3); printf("\n-----------\n"); printf(" %c | %c | %c ", b1, b2, b3); printf("\n-----------\n"); printf(" \x1b[34m%c\x1b[0m | %c | %c ", c1, c2, c3);  
            break; 
        case 8: 
            printf(" %c | %c | %c ", a1, a2, a3); printf("\n-----------\n"); printf(" %c | %c | %c ", b1, b2, b3); printf("\n-----------\n"); printf(" %c | \x1b[34m%c\x1b[0m | %c ", c1, c2, c3);  
            break; 
        case 9: 
            printf(" %c | %c | %c ", a1, a2, a3); printf("\n-----------\n"); printf(" %c | %c | %c ", b1, b2, b3); printf("\n-----------\n"); printf(" %c | %c | \x1b[34m%c\x1b[0m ", c1, c2, c3);  
            break; 
        default:
            printf("[ERRORE] - Catastrophe in print_deleting_screen");
            break;
    }
}


void initialize_board(void){
    a1=' ', a2=' ', a3=' ', b1=' ', b2=' ', b3=' ', c1=' ', c2=' ', c3=' ';
}


void clear_screen(void){
    for(int i=0; i<20; i++)
        printf("\n");
}


int new_game(void){
    int flag=0;
    do{
        printf("\nVuoi giocare una nuova partita?\n[0] esci - [1] si\n");
        scanf("%d", &flag);
    }while(flag!=0 && flag!=1);
    return flag;
}

#include <stdio.h>
#include <stdlib.h>

typedef void(*operatii) (unsigned int *a, unsigned int b);

void rotatie(unsigned int *a, unsigned int b) {
    unsigned int aux = b;
    while(aux) {
        *(a) = (((*a) << 1) | ((*a)  >> 3)) & 15;
        /*se elimina cel mai semnficativ, respectiv cel
        mai nesemnficativ bit si se forteaza introducerea
        celui mai semnficativ bit pe pozitia 0*/
        aux--;
    }
}

 void interschimbare(unsigned int *a, unsigned int b) {
    unsigned int p1 = (b & 12) >> 2, p2 = b & 3;
    unsigned int c = (*a) & (1 << (3 - p1));
    unsigned int d = (*a) & (1 << (3 - p2));
    /*cei doi biti care vor fi interschimbati*/
    if(c == 0 && d != 0) {
      (*a) = ((*a) & (~(1 << (3 - p2)))) | (1 << (3 - p1));
    } else {
      if(d == 0 && c != 0) {
        (*a) = ((*a) & (~(1 << (3 - p1)))) | (1 << (3 - p2));
      }
    }
    /*se interschimba doar daca bitii sunt diferiti, altfel
    aceasta nu ar face nicio modificare*/
}

 void adunare(unsigned int *a, unsigned int b) {
    int i = 0;
    unsigned int bita, bitb, imp = 0;
    while(i < 4) {
      bita = (*a) & (1 << i);
      bitb = b & (1 << i);
      /*se extrag bitii care trebuie adunati*/
      if(bita) {
        if(bitb) {
          if(imp) {
            (*a) = (*a) | (1 << i);
          } else {
            (*a) = (*a) & (~(1 << i));
          }
          imp = 1;
          /*in cazul in care ambii biti sunt 1 rezultatul
          adunarii va fi egal cu "imp", care va ramane 1*/
        } else {
          if(imp) {
            (*a) = (*a) & (~(1 << i));
          } else {
            (*a) = (*a) | (1 << i);
          }
          /*in cazul in care primul bit este 1 si al doilea 0
          rezultatul va fi 0, daca "imp" este 1 sau 1
          in caz contrar, acesta ramanand neschimbat*/
        }
      } else {
        if(!bitb) {
          if(imp) {
            (*a) = (*a) | (1 << i);
          } else {
            (*a) = (*a) & (~(1 << i));
          }
          /*in cazul in care cei doi biti sunt 0 rezultatul
          va fi egal cu "imp", care va deveni 0*/
          imp = 0;
        } else {
          if(imp) {
            (*a) = (*a) & (~(1 << i));
          } else {
            (*a) = (*a) | (1 << i);
          }
        }
        /*in cazul in care primul bit este 0 si al doilea 1
          rezultatul va fi 0, daca "imp" este 1 sau 1
          in caz contrar, acesta ramanand neschimbat*/
      }
      i++;
   }
}

 void xor(unsigned int *a, unsigned int b) {
    int i = 0;
    while(i < 4) {
      if((1 << i) & (*a)) {
         if((1 << i) & b) {
            *a = ((*a) & (~(1 << i))) & 15;
          /*se considera cazul in care ambii biti sunt 1 si
          se introduce 0 pe pozitia "i"*/
         } else {
               (*a) = ((*a) | (1 << i)) & 15;
          /*se considera cazul in care primul bit este 1 si celalalt 0
          si se introduce 1 pe pozitia "i"*/
         }
      } else {
         if(!((1 << i) & (*a))) {
            if(!((1 << i) & b)) {
               (*a) = ((*a) & (~(1 << i))) & 15;
          /*se considera cazul in care ambii biti sunt 0 si
          se introduce 0 pe pozitia "i"*/
            } else {
               (*a) = ((*a) | (1 << i)) & 15;
          /*se considera cazul in care primul bit este 0 si celalalt 1
          si se introduce 1 pe pozitia "i"*/
            }
         } 
      }
      i++;
   }
}

 int main() {
    operatii tp[] = {adunare, interschimbare, rotatie, xor};
    
    unsigned int n, m;
    scanf("%d%u", &n, &m);
    unsigned int a, b, op;
    unsigned int aux = n;
        a = m >> (6 * aux) & 15;
        /*se extrage primul numar*/
        while(aux) {
            op = (m >> (6 * aux - 2)) & 3;
            /*se extrage operatia*/
            b = (m >> (6 * (--aux))) & 15;
            /*se extrage al doilea numar*/
            tp[op](&a, b);
        }
        printf("%u", a);
     
    return 0;

}
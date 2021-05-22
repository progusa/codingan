/* File queues.c */
/* implementasi dari file queues.h */
/* HEAD dan TAIL adalah alamat elemen pertama dan terakhir */
/* Kapasitas Queue=MaxEl bush elemen, dan indeks dibuat "sirkuler" */
#include "stackt.h"
#include <stdio.h>
/* Definisi ABSTRACT DATA TYPE POINT *
Stack S;

/******************* Prototype ****************/
/*** Konstruktor/Kreator ***/
void CreateEmpty(Stack *S){
	Top(*S) = Niil;
}
/* T.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosonq berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+l karena O tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */
/*********** Predikat Untuk test keadaan KOLEKSI **/
boolean IsEmpty (Stack S){
	return Top(S) == Niil;
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFull(Stack S){
	//printf("Top %d Max %d", Top(S),MaxEl);
	return Top(S) == MaxEl;
}
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
/*********** Menambahkan sebuah elemen ke Stack **********/
void Push (Stack *S, info X){
    if(!IsFull(*S)){
        Top(*S) = Top(*S)+1;
        InfoTop(*S) = X;
    } else {
        printf("Sorry Cant Push Cause Stack is Full!");
    }

}
/* Menambahkan X sebagai elemen Stack S. */
/* T.S. S mungkin kosong, tabel penampung elemen stack TTDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
/*********** Menqhapus sebuah elemen Stack **********/
void Pop (Stack *S, info *X){
    if(!IsEmpty(*S)){
        *X = InfoTop(*S);
        Top(*S) = Top(*S)-1;
    }else{
        printf("Cant Pop Cause your Stack is Empty!");
    }

}
/* Menghapus X dari Stack S. */
/* T.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang l */

/********* Print Stack From Bottom to Top *************/
void printStack(Stack S){
    Stack temp;
    CreateEmpty(&temp);
    info x, f;
    int i = 1;
    while(!IsEmpty(S)){
        Pop(&S, &x);
        Push(&temp, x);
    }

    while(!IsEmpty(temp)){
        x = InfoTop(temp);
        printf("%d. %s\n", i, x.Nama);
//        printf("No. KTP  : %s\n", x.ktp);
//        printf("Nama     : %s\n", x.nama);
//        printf("Kategori : %s\n", x.kategori);
//        printf("Info Kategori : %s\n", x.info_kategori);
        Push(&S, x);
        Pop(&temp, &f);
        i++;
    }
}

int nElem(Stack S){
    Stack temp;
    CreateEmpty(&temp);
    info x, f;
    int i = 1;
    while(!IsEmpty(S)){
        Pop(&S, &x);
        Push(&temp, x);
    }

    while(!IsEmpty(temp)){
        x = InfoTop(temp);
        //printf("%d. %s\n", i, x.nama);
//        printf("No. KTP  : %s\n", x.ktp);
//        printf("Nama     : %s\n", x.nama);
//        printf("Kategori : %s\n", x.kategori);
//        printf("Info Kategori : %s\n", x.info_kategori);
        Push(&S, x);
        Pop(&temp, &f);
        i++;
    }

    return i-1;
}

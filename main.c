#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include "list_queue.h"
#include "stackt.h"

int Menu(){
    int x;
    printf("===================================\n");
    printf("| Program By : Arsal Fadilah V.03 |\n");
    printf("===================================\n");
    printf("||     PENDAFTARAN VAKSINASI     ||\n");
    printf("||  1. Tambah Pendaftar          ||\n");
    printf("||  2. Tampilkan Pendaftar       ||\n");
    printf("||  3. Tampilkan Daftar Tunggu   ||\n");
    printf("||  4. Registrasi Peserta        ||\n");
    printf("||  5. Verifikasi Peserta        ||\n");
    printf("||  6. Program Pelayanan Vaksin  ||\n");
    printf("||  7. Exit                      ||\n");
    printf("\n  Pilih Menu : ");
    scanf("%d", &x);
    return x;
}

void MenuSortList(List L){
    int fitur;
    List newTipe;

    printf("Filter by category :\n");
    printf("1. Dosen\n");
    printf("2. Guru\n");
    printf("3. BUMN\n");
    printf("4. Lansia\n");

    printf("Choose : ");scanf("%d", &fitur);

    switch(fitur){
        case 1:
            newTipe = FCopyList(L);
            //del semua yang bukan dosen. yg lainnya pun sama
            DelP(&newTipe, "DOSEN");
            sortListQueue(&newTipe);
            PrintInfo(newTipe);
            break;
        case 2:
            newTipe = FCopyList(L);
            DelP(&newTipe, "GURU");
            sortListQueue(&newTipe);
            PrintInfo(newTipe);
            break;
        case 3:
            newTipe = FCopyList(L);
            DelP(&newTipe, "BUMN");
            sortListQueue(&newTipe);
            PrintInfo(newTipe);
            break;
        case 4:
            newTipe = FCopyList(L);
            DelP(&newTipe, "LANSIA");
            sortListQueue(&newTipe);
            PrintInfo(newTipe);
            break;
        default:
            printf("Wrong Input");
            break;
    }

    printf("\n[ Back To Menu ]\n");

}

void insertPeserta(List L, Stack *S){
    info X;
    infotype pendaftar = L.First->info;
    address temp = Nil;
    infotype tempSearch;
    char choose1, choose2;

    printf("No. KTP             : ");scanf("%s", &X.NoKtp);
    strcpy(pendaftar.NoKtp, X.NoKtp);
    if((temp = Search1(L, pendaftar)) != Nil){
        printf("Nama                : %s\n", temp->info.Nama);
        printf("Kategori            : %s\n", temp->info.Kategori);
        fflush(stdin);
        printf("Fotocopy KTP        : [Y/N] ");scanf("%c", &choose1);
        if(choose1=='Y'){
            temp->info.syarat_1 = true;
        }else{
            temp->info.syarat_1 = false;
        }

        fflush(stdin);
        if(strcmp(temp->info.Kategori, "Lansia")==0){
            printf("Kartu Keluarga      : [Y/N] ");scanf("%c", &choose2);
        } else{
            printf("Surat Pengantar     : [Y/N] ");scanf("%c", &choose2);
        }

        if(choose2=='Y'){
            temp->info.syarat_2 = true;
        } else {
            temp->info.syarat_2 = false;
        }


        if(!(temp->info.syarat_1) && !(temp->info.syarat_2)){
            printf("\nRegistrasi Gagal\n");
        } else {
            tempSearch = temp->info;
            //CopyInfoAja(tempSearch, &X);
            Push(S, tempSearch);
            printf("\nRegistrasi Berhasil\n");
        }

    } else {
        printf("\nData Pendaftar tidak ditemukan\n");
    }

}

void Verifikasi(List L, Stack *S, List *Gate1){
    infotype X;
    char choose='Y';
    char stat = 'N';
    int no;
    address temp = Nil;
    infotype tempInfo;

    system("cls");
    while(choose=='Y' && !IsEmpty(*S)){
      printf("\nPeserta yang sudah Registrasi\n");
      printStack(*S);
        X = InfoTop(*S);
        printf("\nLakukan Verifikasi untuk %s ? [Y/N] ", X.Nama);

        fflush(stdin);
        scanf("%c", &choose);

        if(choose=='Y'){
            stat = 'Y';
            Pop(S, &X);
            strcpy(X.infoVaksin, "Antrian Gate I");
            enqueue(Gate1, X);
                printf("Peserta yang sudah Registrasi\n");

                if(!IsEmpty(*S)){
                    system("cls");
                    printStack(*S);
                } else {
                    printf("[Tidak Ada]\n");
                }

                no = nElem(*S);
                printf("%d. %s dengan informasi \n", nElem(*S)+1, X.Nama);
                strcpy(tempInfo.NoKtp, X.NoKtp);
                //printf("%s", tempInfo.NoKtp);
                temp = Search1(L, tempInfo);
                if(temp != Nil){
                    printf("   a. Nomor Pendaftaran   : %s\n", X.noPendaftar);
                    printf("   b. Nama                : %s\n", X.Nama);
                    printf("   c. Kelompok Masyarakat : %s\n", X.Kategori);
                    printf("   d. Jenis Kelamin       : %c\n", X.lp);
                    printf("   e. Tanggal Vaksin      : "); PrintObj(X.Waktu);
                    printf("\n   f. Gate 1\n");
                } else {
                    printf("Something Error 401\n");
                }
                //getch();
                getch();
                system("cls");
        }
        printf("\n====================================\n");
    }

    if(IsEmpty(*S) && stat != 'Y'){
        printf("\nPeserta yang sudah Registrasi\n");
        printf("[Tidak Ada]\n");
    }

}

void R_Gate1(List *L){
    int sub;
    List Gate1;
    CreateList(&Gate1);
    Gate1 = FCopyList(*L);

    DelStat(&Gate1, "Antrian Gate I");

    printf("Program Pelayanan Vaksin - Gate I\n");
           printf("====================================\n");
           printf("1. Tampilkan Antrian Vaksinasi Gate I\n");
           printf("2. Panggil Antrian (10 Peserta)\n\n");
           printf("Pilih : "); scanf("%d", &sub);

           system("cls");
           switch(sub){
                case 1:
                    printf("Program Pelayanan Vaksin - Gate I - Tampilkan Antrian\n");
                    printf("======================================================\n");
                    sortListQueue(&Gate1);
                    tampilPendaftarGate1(Gate1);
                    getch();
                    break;
                case 2:
                    printf("Program Pelayanan Vaksin - Gate I - Panggil Antrian\n");
                    printf("======================================================\n");
                    PanggilAntrian(L);
                    getch();
                    break;
           }
}

void R_Gate2(List *L){
    int sub;
    List Gate2;
    char q[6];
    boolean lolos;
    infotype infoOrg;
    Gate2 = FCopyList(*L);
    DelStat(&Gate2, "Antrian Gate II");

    address P = First(Gate2);
    address Temp = Nil;

    printf("Program Pelayanan Vaksin - Gate II\n");
    printf("=====================================\n");
    printf("1. Tampilkan Antrian Vaksinasi Gate II\n");
    printf("2. Panggil Antrian Observasi Kesehatan\n\n");

    printf("Pilih : "); scanf("%d", &sub);

    system("cls");
    switch(sub){
        case 1:
            printf("Program Pelayanan Vaksin - Gate II - Tampilkan Antrian\n");
            printf("=====================================================\n");
            sortListQueue(&Gate2);
            tampilPendaftarGate1(Gate2);
            getch();
            break;
        case 2:
            sortListQueue(&Gate2);
            while(sub != 6){
                lolos = true;
                printf("Program Pelayanan Vaksin - Gate II - Panggil Antrian\n");
                printf("=====================================================\n");
                P = First(Gate2);

                if( P !=  Nil){
                    for(int i =1 ; i<6; i++)
                    printf("%d. Observasi Kesehatan - Dokter %d\n", i, i);
                printf("6. Back\n\n");

                printf("Pilih : "); scanf("%d", &sub);

                if(sub < 6){
                    printf("Observasi Kesehatan - Dokter %d\n", sub);
                    printf("===========================================\n");
                    printf("Nomor Antrian %s Masuk Observasi Dokter %d\n", P->info.noPendaftar, sub);
                    infoOrg = P->info;
                    Temp = Search1(*L, infoOrg);

                    fflush(stdin);
                    printf("Apakah anda sedang hamil ?                      : [Y/N] \n");
                    scanf("%c", &q[0]);

                    fflush(stdin);
                    printf("Apakah anda sedang menyusui ?                   : [Y/N] \n");
                    scanf("%c", &q[1]);

                    fflush(stdin);
                    printf("Apakah anda sedang mengikuti program hamil  ?   : [Y/N] \n");
                    scanf("%c", &q[2]);

                    fflush(stdin);
                    printf("Apakah sebelumnya anda pernah positif Covid ?   : [Y/N] \n");
                    scanf("%c", &q[3]);

                    fflush(stdin);
                    printf("Jika pernah positif covid, Apakah anda sekarang masih positif ? : [Y/N] \n");
                    scanf("%c", &q[4]);

                    fflush(stdin);
                    printf("Jika pernah positif covid, Apakah Covid anda kurang dari 3 bulan ? [Y/N] \n");
                    scanf("%c", &q[5]);

                    for(int i = 0; i<6 ; i++){
                        if(q[i] == 'Y'){
                            lolos = false;
                        }
                    }

                    if(lolos){
                        printf("Nomor Pendaftaran %s Masuk Ruang Bilik Vaksinasi\n", Temp->info.noPendaftar);
                        printf("status : Berhasil Vaksin");
                        strcpy(Temp->info.infoVaksin, "Berhasil Vaksin");
                    } else {
                        printf("Nomor Pendaftaran %s Tidak Masuk Ruang Bilik Vaksinasi. Silahkan menuju Pintu Keluar\n", Temp->info.noPendaftar);
                        printf("status : Batal Vaksin");
                        strcpy(Temp->info.infoVaksin, "Batal Vaksin");
                    }

                        dequeue(&Gate2, &P);
                    }

                } else {
                    sub = 6;
                    printf("Yeah tidak ada antrian yang menunggu\n");
                }

                getch();
                system("cls");
            }

            break;
    }
}

void pelayananVaksin(List *L){
    int choose = 0;

    system("cls");
    while(choose != 4){
        printf("=================================\n");
        printf("||   Program Pelayanan Vaksin  ||\n");
        printf("=================================\n");
        printf("1. Gate I (Ruang Tunggu)\n");
        printf("2. Gate II (Observasi Kesehatan)\n");
        printf("3. Daftar Peserta Vaksin\n");
        printf("4. Back\n\n");

        printf("Pilih : "); scanf("%d", &choose);

        system("cls");
        switch(choose){
            case 1:
                R_Gate1(L);
               break;
            case 2:
                R_Gate2(L);
                break;
            case 3:
                printf("Program Pelayanan Vaksin - Daftar Peserta Vaksin\n");
                printf("===============================================\n");
                tampilPesertaVaksin(*L);
                getch();
                break;
        }
        system("cls");
    }

}

//void initPendaftar(List *L){
//    infotype x;
//    int no = NbElmt(*L) + 1;
//    char strNo[5];
//    char temp;
//    sprintf(strNo, "%d", no);
//
//    if(no > 999){
//        strcpy(x.noPendaftar, strNo);
//    } else if(no > 99){
//        for(int i = 3; i<0; i--){
//            strNo[i] = strNo[i-1];
//        }
//        strNo[0]='0';
//
//        strcpy(x.noPendaftar, strNo);
//    } else if(no > 9){
//        for(int i = 3; i<1; i--){
//            strNo[i] = strNo[i-1];
//        }
//        strNo[0]='0';
//        strNo[1]='0';
//
//        strcpy(x.noPendaftar, strNo);
//    } else {
//        temp = strNo[0];
//        strNo[0]='0';
//        strNo[1]='0';
//        strNo[2]='0';
//        strNo[3]=temp;
//        strcpy(x.noPendaftar, strNo);
//    }
//    //Auto Random No KTP
//    srand(time(0));
//    int randomNum = rand()&10000;
//    sprintf(strNo, "%d", randomNum);
//    strcpy(x.NoKtp, strNo);
//    printf("No. KTP             : %s\n", x.NoKtp);
//    strcpy(x.Nama, "Arsal Fadilah");
//    printf("Nama                : %s\n", x.Nama);
//    x.lp = 'L';
//    printf("Jenis Kelamin       : %c\n", x.lp);
//    strcpy(x.NoTelp, "08123124124");
//    printf("Nomor Telepon       : %s\n", x.NoTelp);
//    //Scan Auto
//    SetDateLoc(&x.Waktu);
//    NextDate(&x.Waktu);
//    printf("Tanggal Kedatangan  : ");PrintObj(x.Waktu);
//    printf("\nJam Kedatangan      : ");BacaDateJam(&x.Waktu);
//
//    while(!isValidJamSesi(x.Waktu)){
//        printf("No session in this time\n");
//        printf("Jam Kedatangan      : ");BacaDateJam(&x.Waktu);
//    }
//    printf("Kategori            : ");scanf("%s", x.Kategori);
//
//    toUpperStr(x.Kategori);
//    fflush(stdin);
//
//    if(strcmp(x.Kategori, "LANSIA")==0){
//        printf("Usia                : ");scanf("%s", x.InfoKategori);
//    } else {
//        printf("Instansi            : ");scanf("%34[^\n]", x.InfoKategori);
//    }
//
//    InsVLast(L, x);
//}

int main(){
    char ActiveSortCategory;
    List pendaftar, queue_list, queue_Gate1;
    Stack Peserta;
    CreateEmpty(&Peserta);
    CreateList(&pendaftar);
    CreateList(&queue_Gate1);

    system("cls");

    int m;
    while((m = Menu()) != 7){
        switch(m){
            case 1:
                printf("\n!!! Isilah data pendaftar di bawah dengan BENAR !!!\n");
                insertPendaftar(&pendaftar);
                //initPendaftar(&pendaftar);
                break;
            case 2:
                tampilPendaftar(pendaftar);
                break;
            case 3:
                //Melihat daftar antrian seluruhnya
                queue_list = FCopyList(pendaftar);
                sortListQueue(&queue_list);
                tampilPendaftar(queue_list);

                //Melihat antrian per kategori
                printf("Do u want to filter this queue (y/t) ? ");
                fflush(stdin);
                scanf("%c", &ActiveSortCategory);
                if(ActiveSortCategory=='y'){
                    system("cls");
                    MenuSortList(pendaftar);
                }
                break;
            case 4:
                insertPeserta(pendaftar, &Peserta);
                break;
            case 5:
                Verifikasi(pendaftar, &Peserta, &queue_Gate1);
                break;
            case 6:
                pelayananVaksin(&queue_Gate1);
                break;
            default :
                printf("Wrong input menu, please try again . . .\n");
                break;
        }
        system("pause");
        system("cls");
    }

    DelAll(&pendaftar);

    return 0;
}

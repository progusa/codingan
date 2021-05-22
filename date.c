#include "date.h"
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
/***************************/
/*  S P E S I F I K A S I  */
/***************************/

/*********** Operasi Primitif ************/
void CreateDate (date * D){
    /* Constructor Membentuk sebuah DATE, dengan nilai default adalah 01/01/1900 */
    D->Bln = 1;
    D->Tgl = 1;
    D->Thn = 1900;
    D->Hour = 0;
    D->Minute = 0;
    D->Second = 0;
}

/******* Selector komponen **********/
int GetTgl (date D){
/* Mengambil bagian Tgl dari date */
    return D.Tgl;
}

int GetBln (date D){
/* Mengambil bagian Bln dari date */
    return D.Bln;
}

int GetThn (date D){
/* Mengambil bagian Thn dari date */
    return D.Thn;
}

int GetHour(date D){
    return D.Hour;
}

int GetMinute(date D){
    return D.Minute;
}

int GetSecond(date D){
    return D.Second;
}

int getSesi(date D){
//Date D pasti sudah valid
    if((D.Hour==8 && D.Minute>=0)
       ||
       (D.Hour > 8 && D.Hour<10)
       ||
       (D.Hour==10 && D.Minute==0)){
        return 1;
    } else if((D.Hour==11 && D.Minute>=0)
       ||
       (D.Hour > 11 && D.Hour<13)
       ||
       (D.Hour==13&& D.Minute==0)){
        return 2;
    } else if((D.Hour==14 && D.Minute>=0)
       ||
       (D.Hour > 14 && D.Hour<16)
       ||
       (D.Hour==16 && D.Minute==0)){
        return 3;
    } else {
        //error
        return 0;
    }
}

/****** Pengubah komponen ******/
void SetDateLoc(date * D){
   time_t rawtime;
   struct tm *info;
   time( &rawtime );
   info = localtime( &rawtime );

   //assign into this var
   SetThn(info->tm_year+1900, D);
   SetBln(info->tm_mon+1, D);
   SetTgl(info->tm_mday, D);
   SetHour(info->tm_hour, D);
   SetMinute(info->tm_min, D);
   SetSecond(info->tm_sec, D);

}

void SetTgl (int NewTgl, date * D){
/* Memberi nilai untuk Tgl */
    D->Tgl = NewTgl;
}

void SetBln (int NewBln, date * D){
/* Memberi nilai untuk Bln */
    D->Bln = NewBln;
}

void SetThn (int NewThn, date * D){
/* Memberi nilai untuk Thn */
    D->Thn = NewThn;
}

void SetHour(int NewHour, date * D){
    D->Hour = NewHour;
}

void SetMinute(int NewMinute, date *D){
    D->Minute = NewMinute;
}

void SetSecond(int NewSecond, date *D){
    D->Second = NewSecond;
}
/****** Kelompok Interaksi dengan I/O device, BACA/TULIS ******/
void BacaDateTgl(date * D){
/* Membentuk DATE dari iTgl, iBln dan iThn yang dibaca dari keyboard */
    int i;

    printf("New Tanggal : "); scanf("%d", &i);
    D->Tgl = i;
    printf("New Bulan   : "); scanf("%d", &i);
    D->Bln = i;
    printf("New Tahun   : "); scanf("%d", &i);
    D->Thn = i;

    //Cek apakah format tanggal yang diinputkan adalah benar atau tidak
    //Guard jika salah input tanggal
    if(!isValidTgl(*D)){
        printf("\nAnda salah memasukkan format tanggal !\n");
        printf("Silahkan coba lagi\n");
        BacaDateTgl(D);
    }

}

void BacaDateJam(date *D){
    int h,m;

    scanf("%d:%d", &h, &m);
    D->Hour = h;
    D->Minute = m;
    D->Second = 0;


    //Cek Format Jam
    if(!isValidJam(*D)){
        printf("\nAnda salah memasukkan format jam !\n");
        printf("Silahkan coba lagi\n");
        BacaDateJam(D);
    }

}

bool isValidTgl(date D){
/* Memeriksa apakah suatu tanggal valid, yaitu dengan memperhatikan batas akhir per bulan */

    //Apakah bulan antara 1 - 12 ?
    if(D.Bln >= 1 && D.Bln <= 12){
        //Apakah bulan 1 - 7
        if(D.Bln >= 1 && D.Bln <=7){
            //Apakah bulan februari ?
            if((D.Bln) == 2){
                //Apakah tahun kabisat ?
                if(isKabisat(D) && ((D.Tgl) >= 1 && (D.Tgl) <= 29)){
                    return true;
                } else if ((D.Tgl) >= 1 && (D.Tgl) <= 28){
                    return true;
                } else {
                    return false;
                }
            } else if((D.Tgl) >=1 && (D.Tgl) <=30){
                return true;
            } else {
                return false;
            }
        } else {
            //Apakah bulan genap atau ganjil dari 8 - 12
            if(D.Bln % 2 == 0){
                if((D.Tgl) >=1 && (D.Tgl) <=31){
                    return true;
                } else {
                    return false;
                }
            } else if ((D.Tgl) >=1 && (D.Tgl) <=30){
                return true;
            } else {
                return false;
            }
        }
    } else {
        return false;
    }

}

bool isValidJam(date D){

    if(D.Hour > 24 || D.Minute > 60 ||  D.Second > 60){
        return false;
    } else if(D.Hour==24 && D.Minute>0 || D.Hour==24 && D.Second>0){
        return false;
    } else if(D.Minute==60 && D.Second > 0){
        return false;
    } else if(D.Hour < 0 || D.Minute < 0 || D.Second < 0){
        return false;
    } else{
        return true;
    }
}
bool isValidJamSesi(date D){

//    if(D.Hour > 24 || D.Minute > 60 ||  D.Second > 60){
//        return false;
//    } else if(D.Hour==24 && D.Minute>0 || D.Hour==24 && D.Second>0){
//        return false;
//    } else if(D.Minute==60 && D.Second > 0){
//        return false;
//    } else if(D.Hour < 0 || D.Minute < 0 || D.Second < 0){
//        return false;
//    } else{
//        return true;
//    }
    if((D.Hour==8 && D.Minute>=0)
       ||
       ((D.Hour > 8 && D.Hour<10) && (D.Minute<60))
       ||
       (D.Hour==10 && D.Minute==0)){
        return true;
    } else if((D.Hour==11 && D.Minute>=0)
       ||
       ((D.Hour > 11 && D.Hour<13) && (D.Minute<60))
       ||
       (D.Hour==13&& D.Minute==0)){
        return true;
    } else if((D.Hour==14 && D.Minute>=0)
       ||
       ((D.Hour > 14 && D.Hour<16) && (D.Minute<60))
       ||
       (D.Hour==16 && D.Minute==0)){
        return true;
    } else {
        //error format no sesion
        return false;
    }
}

void PrintObj (date D){
/* Print nilai D dengan format dd/mm/yyyy */
    if((D.Tgl >=1 && D.Tgl <=9) && (D.Bln >=1 && D.Bln <=9)){
        printf("0%d/0%d/%d", D.Tgl, D.Bln, D.Thn);
    } else if(D.Tgl >=1 && D.Tgl <=9){
        printf("0%d/%d/%d", D.Tgl, D.Bln, D.Thn);
    } else if (D.Bln >=1 && D.Bln <=9) {
        printf("%d/0%d/%d", D.Tgl, D.Bln, D.Thn);
    } else {
        printf("%d/%d/%d", D.Tgl, D.Bln, D.Thn);
    }

}

void PrintJam(date D){
    if(D.Hour > 9 && D.Minute > 9)
        printf("%d:%d",D.Hour, D.Minute);
    else if(D.Hour > 9 && D.Minute<= 9)
        printf("%d:0%d",D.Hour, D.Minute);
    else if(D.Hour <= 9 && D.Minute > 9)
        printf("0%d:%d",D.Hour, D.Minute);
    else
        printf("0%d:0%d",D.Hour, D.Minute);

}

/****** Operator Relasional ******/
bool isKabisat (date D){
/* Memeriksa apakah suatu tanggal adalah kabisat; Dipakai untuk bulan == 2 saja */
    if(D.Thn % 4 == 0){
        return true;
    } else {
        return false;
    }
}

/***** Predikat lain *******/
int TglAkhir (date D){
/* Memberikan tanggal terakhir dari sebuah bulan */
    //Apakah bulan ganjil atau genap ?
    if(D.Bln >= 1 && D.Bln <=7){
        //Apakah bulan februari ?
        if((D.Bln) == 2){
            //Apakah tahun kabisat ?
            if(isKabisat(D)){
                return 29;
            } else {
                return 28;
            }
        } else if(D.Bln % 2 == 0){
            return 30;
        } else {
            return 31;
        }
    } else {
        //Apakah bulan genap atau ganjil dari 8 - 12
        if(D.Bln % 2 == 0){
            return 31;
        } else {
            return 30;
        }
    }
}


void DateBefore (date D){
/* Menampilkan tanggal sebelumnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal sebelumnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika jan, thn-1 */
	if(D.Bln == 1 && D.Tgl == 1){
        D.Thn = D.Thn - 1;
        D.Bln = 12;
        D.Tgl = TglAkhir(D);
	} else if(D.Tgl == 1){
        D.Bln = D.Bln - 1;
        D.Tgl = TglAkhir(D);
	} else {
        D.Tgl--;
	}

	PrintObj(D);

}


void NextDate (date * D){
/* Menampilkan tanggal berikutnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal berikutnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika des, thn+1 */
    if(D->Bln == 12 && D->Tgl == TglAkhir(*D)){
        D->Thn = D->Thn + 1;
        D->Bln = 1;
        D->Tgl = 1;
	} else if(D->Tgl == TglAkhir(*D)){
        D->Bln = D->Bln + 1;
        D->Tgl = 1;
	} else {
        D->Tgl++;
	}
}


void SelisihDate (date D1, date D2){
/* Menampilkan selisih dua tanggal
	I.S = 2 buah Tanggal tertentu diketahui
	F.S = Tampil selisih dua buah tanggal
	Asumsi : 1 tahun = 365 hari */
    date temp;

    //Nilai D1 harus selalu lebih besar
    if(D2.Thn > D1.Thn){
        temp = D1;
        D1 = D2;
        D2 = temp;
    } else if (D2.Bln > D1.Bln && D1.Thn == D2.Thn){
        temp = D1;
        D1 = D2;
        D2 = temp;

    } else if (D2.Tgl > D1.Tgl && D1.Bln == D2.Bln && D1.Thn == D2.Thn){
        temp = D1;
        D1 = D2;
        D2 = temp;
    }

    //Cara 1 :
    int day_D1, day_D2, selisih;
    day_D1 = D1.Tgl + (365 * (D1.Thn-sumOfKabisat(D1.Thn))) + (366 * sumOfKabisat(D1.Thn));
    day_D2 = D2.Tgl + (365 * (D2.Thn-sumOfKabisat(D2.Thn))) + (366 * sumOfKabisat(D2.Thn));

    for(int i = 1; i<D1.Bln; i++){
        SetBln(i, &temp);
        day_D1 += TglAkhir(temp);
    }

    for(int i = 1; i<D2.Bln; i++){
        SetBln(i, &temp);
        day_D2 += TglAkhir(temp);
    }

    selisih = day_D1 - day_D2;

    //Cara 2 :
    if(D2.Tgl > D1.Tgl){
        D1.Tgl += TglAkhir(D1);
        D1.Bln--;
    }

    if(D2.Bln > D1.Bln){
        D1.Bln += 12;
        D1.Thn--;
    }

    //Selisihnya :
    temp.Tgl = D1.Tgl - D2.Tgl;
    temp.Bln = D1.Bln - D2.Bln;
    temp.Thn = D1.Thn - D2.Thn;

    printf("%d Hari, %d Bulan, %d Tahun", temp.Tgl, temp.Bln, temp.Thn);
    printf(" atau setara dengan %d hari", selisih);

}

int sumOfKabisat (int Years){
/*Menghitung berapa banyak tahun kabisat*/
    int count = 0;

    for(int i = 1; i<=Years; i++){
        if(i % 4 == 0){
            count++;
        }
    }

    return count;
}

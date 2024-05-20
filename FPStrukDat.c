#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define new (struct node*)malloc(1*sizeof(struct node))
#define INF 999

struct node{
    char buah[100];
    int vertek;
    char tekstur[100];
    char rasa[100];
    struct node *next;
};

int main()
{
	FILE* ptr;
    int vertek2, cmp, cmp2, count, pil, v1, v2, m;
    char buah2[100], tekstur2[100], rasa2[100], fav[100];
    struct node *top, *temp, *temp2, *cnode;
    top = NULL;
    count = 0;
    m = 0;
	ptr = fopen("data.txt", "a+");

    //Buka file
	if (NULL == ptr) {
		printf("file can't be opened \n");
        return 0;
	}

    //Memasukkan data pada file
    //ke dalam linked list
    while(!feof(ptr)){
        if(top == NULL){
            top = new;
            fscanf(ptr, "%99s %d %99s %99s", buah2, &vertek2, tekstur2, rasa2);
            strcpy(top->buah, buah2);
            top->vertek = vertek2;
            strcpy(top->tekstur, tekstur2);
            strcpy(top->rasa, rasa2);
            top->next = NULL;
            count++;
        }
        else{
            cnode = new;
            fscanf(ptr, "%99s %d %99s %99s", buah2, &vertek2, tekstur2, rasa2);
            strcpy(cnode->buah, buah2);
            cnode->vertek = vertek2;
            strcpy(cnode->tekstur, tekstur2);
            strcpy(cnode->rasa, rasa2);
            cnode->next = top;
            top = cnode;
            count++;
        }
    }

    fclose(ptr);
	
    //Isi matriks ketetanggaan
    //dengan nilai inf (999) dan 0
    int mt[count][count];
    for(int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            if(i == j){
                mt[i][j] = 0;
            }
            else{
                mt[i][j] = INF;
            }
        }
    }

    //Membuat representasi graf dalam bentuk
    //matriks ketetanggaan sesuai data
    temp = top;
    for(int i=0;i<count;i++){
        v1 = temp->vertek;
        temp2 = top;
        int j = 0;
        while(temp2 != NULL){
            v2 = temp2->vertek;
            if(v2 == v1){
                mt[i][j] = 0;
            }
            else{
                if(strcmp(temp->tekstur, temp2->tekstur) == 0){
                    mt[i][j] = 2;
                }

                if(strcmp(temp->rasa, temp2->rasa) == 0){
                    if(mt[i][j] != 2){
                        mt[i][j] = 2;
                    }
                    else{
                        mt[i][j] = 1;
                    }
                }
            }
            temp2 = temp2->next;
            j++;
        }
        temp = temp->next;
    }


    //Algoritma Floyd Warshall
    for(int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            for(int k=0;k<count;k++){
                if(mt[j][i] + mt[i][k] <= mt[j][k]){
                    mt[j][k] = mt[j][i] + mt[i][k];
                }
            }
        }
    }

    /*for(int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            printf("%5d", mt[i][j]);
        }
        printf("\n");
    }*/

    while(1){
        printf("\n");
        printf("===========================================================\n");
        printf(">>                Program Rekomendasi Buah               <<\n");
        printf("===========================================================\n");
        printf("=                          Menu:                          =\n");
        printf("=                   1. Rekomendasi Buah                   =\n");
        printf("=               2. Daftar Buah Pada Sistem                =\n");
        printf("=                    3. Keluar Program                    =\n");
        printf("===========================================================\n");
        printf(">> Pilihan: ");
        scanf("%d", &pil);
        printf("===========================================================\n");

        switch(pil){
            case 1:
            printf(">>Buah Favorit Anda (Contoh: jambu_air): ");
            scanf(" %[^\n]%*c", fav);
            printf("===========================================================\n");
            
            //Cari buah dalam data
            temp = top;
            while(temp != NULL){
                if(strcmp(fav, temp->buah) == 0){
                    m = 1;
                    break;
                }
                temp = temp->next;
            }

            if(m == 1){
                //Jika ditemukan, cari vertek-vertek
                //yang terhubung dengan vertek buah favorit
                v1 = 19 - temp->vertek;
                int target[2][count];
                for(int i=0;i<count;i++){
                    target[0][i] = mt[v1][i];
                    target[1][i] = 19 - i;
                }

                //Urutkan vertek yang terhubung dengan vertek
                //buah favorit secara ascending berdasar bobot edge
                int s;
                for(int i=0;i<count-1;i++){
                    for(int j=0;j<count-1;j++){
                        if(target[0][j] > target[0][j+1]){
                            s = target[0][j];
                            target[0][j] = target[0][j+1];
                            target[0][j+1] = s;
                            s = target[1][j];
                            target[1][j] = target[1][j+1];
                            target[1][j+1] = s;
                        }
                    }
                }

                //Cari lima nama buah dengan kemiripan
                //tertinggi sesuai representasi verteknya
                printf(">>Rekomendasi Buah Untuk Anda:\n");
                for(int i=1;i<=5;i++){
                    temp = top;
                    while(temp != NULL){
                        if(target[1][i] == temp->vertek){
                            printf(">>%d. %s\n", i, temp->buah);
                            break;
                        }
                        temp = temp->next;
                    }
                }
                printf("===========================================================\n");
            }
            else{
                //Jika buah favorit tidak ditemuka
                //dalam data maka tidak ada eksekusi rekomendasi
                printf(">>Buah Tidak Terdapat Dalam Data\n");
                printf("===========================================================\n");
            }
            break;

            case 2:
            printf(">>Berikut Adalah Daftar Buah Pada Data Sistem\n");
            int h = 1;
            temp = top;
            while(temp != NULL){
                printf(">>%d.\t%s\n", h, temp->buah);
                h++;
                temp = temp->next;
            }
            printf("===========================================================\n");
            break;

            case 3:
            printf(">>Program ditutup\n");
            printf("===========================================================\n");
            return 0;

            default:
            printf(">>Pilihan Invalid, Harap Masukkan Pilihan yang Sesuai\n");
            printf("===========================================================\n");
            break;
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  int choice;     
  int result;                                    // hangi operatoru seçtiğini tutuyor
  int pipefd[2];                                 //eğer pipefd[0] => okuma ,  pipefd[1] => yazma
  pid_t pid;                                     // her operator için ayrı bir pid childler  için yeni çocuk process
   int num1, num2; 
    
    printf("hello which do you choice process \n\n" );
    printf("  CALCULATOR \n");
    printf("1 - addition \n") ;
    printf("2 - subtruction \n");
    printf("3 - multiplication \n");
    printf("4 - divicion \n");
    printf("5 EXIT \n");
    
    scanf("%d", &choice);
    
    printf("please write the number you want to process\n");
    scanf("%d %d", &num1, &num2);
    
    
    
    switch (choice) {
            case 1: // Addition
                if (pipe(pipefd) == -1) { // Toplama için pipe oluştur
                    printf("sikinti yok");
                    perror("pipe");
                    exit(EXIT_FAILURE);
                    
                  
                }

                pid = fork();                // Fork ile subprocess oluştur ikiye böl   //Alt prosesin hesapladığı sonucun okunması gerekiyor. Yazma işlemi alt işlemi yapılıyor.
                    perror("fork");          //Ebeveyn işlemi yazma ucunu kapatmazsa:Parent işlemi kazara pipe'a veri yazmaya çalışır ve bu yanlış bir davranışa yol açar.
                    exit(EXIT_FAILURE); 
                

                if (pid == 0) {                          // Çocuk işlem == 0 sa çocuktur
                    close(pipefd[0]);                    // Okuma ucunu kapat
                    char num1_str[10], num2_str[10];
                    sprintf(num1_str, "%d", num1);       //sayıyı strşnge çevirme çünkü pipeler arası sayı gitmiyor
                    sprintf(num2_str, "%d", num2);

                    // Toplama subprocess'ini başlat
                    execl("./addition", "addition", num1_str, num2_str, NULL);       // execute yapıyor
                    printf("Sending to execl: ./addition %s %s\n", num1_str, num2_str);

                    perror("execl");
                    exit(EXIT_FAILURE);
                } else { // Ana işlem
                    close(pipefd[1]);                               // Yazma ucunu kapat çünkü okuması gerekiyor 
                    read(pipefd[0], &result, sizeof(result));       // Çocuğun gönderdiği sonucu oku
                    printf("Result: %d\n", result);
                    close(pipefd[0]);                               //pipefd[0]okuma ucudur. Çocuk işlemi, yalnızca yazma işleminin yapılması için okuma kapağını kapatır.
                }
                break;

            case 2: // Subtraction
                if (pipe(pipefd) == -1) { // Çıkarma için pipe oluştur
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }

                pid = fork(); // Fork ile subprocess oluştur
                if (pid < 0) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }

                if (pid == 0) {                     // Çocuk işlem
                    close(pipefd[0]);               // Okuma ucunu kapat
                    char num1_str[10], num2_str[10];
                    sprintf(num1_str, "%d", num1);
                    sprintf(num2_str, "%d", num2);

                    // Çıkarma subprocess'ini başlat
                    execl("./subtraction", "subtraction", num1_str, num2_str, NULL);
                    perror("execl");
                    exit(EXIT_FAILURE);
                } else { // Ana işlem
                    close(pipefd[1]); // Yazma ucunu kapat
                    read(pipefd[0], &result, sizeof(result)); // Çocuğun gönderdiği sonucu oku
                    printf("Result: %d\n", result);
                    close(pipefd[0]);
                }
                break;
                
                
            case 3: //multiplication
                if(pipe(pipefd) == -1){ // çarpma işlemi için pipe oluşturyoruz
                   perror("pipe");
                   exit(EXIT_FAILURE);
                   }
                   
                   pid = fork();                 // Fork ile multiplaciton oluştur
                if (pid < 0) {                   // eğer 0dan küçük gelirse hata vardır 
                    perror("fork");
                    exit(EXIT_FAILURE);
                    }
                 
                if (pid == 0) {                     // Çocuk işlem
                    close(pipefd[0]);               // Okuma ucunu kapat
                    char num1_str[10], num2_str[10];
                    sprintf(num1_str, "%d", num1);
                    sprintf(num2_str, "%d", num2);

                    // Çıkarma subprocess'ini başlat
                    execl("./multiplication", "multiplication", num1_str, num2_str, NULL);
                    perror("execl");
                    exit(EXIT_FAILURE);
                } else { // Ana işlem
                    close(pipefd[1]); // Yazma ucunu kapat
                    read(pipefd[0], &result, sizeof(result)); // Çocuğun gönderdiği sonucu oku
                    printf("Result: %d\n", result);
                    close(pipefd[0]);
                }
                break;   
                   
            case 4 : //divicion
                if(pipe(pipefd) == -1){ // çarpma işlemi için pipe oluşturyoruz
                   perror("pipe");
                   exit(EXIT_FAILURE);
                   }
                   
                   pid = fork();                 // Fork ile multiplaciton oluştur
                if (pid < 0) {                   // eğer 0dan küçük gelirse hata vardır 
                    perror("fork");
                    exit(EXIT_FAILURE);
                    }
                 
                if (pid == 0) {                     // Çocuk işlem
                    close(pipefd[0]);               // Okuma ucunu kapat
                    char num1_str[10], num2_str[10];
                    sprintf(num1_str, "%d", num1);
                    sprintf(num2_str, "%d", num2);

                    // Çıkarma subprocess'ini başlat
                    execl("./divicion", "divicion", num1_str, num2_str, NULL);
                    perror("execl");
                    exit(EXIT_FAILURE);
                } else { // Ana işlem
                    close(pipefd[1]); // Yazma ucunu kapat
                    read(pipefd[0], &result, sizeof(result)); // Çocuğun gönderdiği sonucu oku
                    printf("Result: %d\n", result);
                    close(pipefd[0]);
                }
                break;   
          
        }
    }
    


















/*
//*************************************************ÇALIŞAN KOD************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main() {
    
    int pipe_add[2], pipe_sub[2], pipe_mul[2], pipe_div[2], pipe_save[2];                   // Her işlem için bir pipe (boru) tanımlıyoruz
    pid_t pid;                                                                              // Yeni processlerin tanımlanması için process ID'si
    int choice, num1, num2;                                                     
    int result;  



    if (pipe(pipe_add) == -1 || pipe(pipe_sub) == -1 || pipe(pipe_mul) == -1 || pipe(pipe_div) == -1 || pipe(pipe_save) == -1) {  
        perror("pipe"); 
        exit(EXIT_FAILURE); 
    }

    // Saver sürecini başlat
    pid_t saver_pid = fork();                                              // child process oluştur saver sınıfı için
    if (saver_pid == 0) {                                                  // eğer 0 seçilirse çocuk yani child işlem tarafından devam edilir
        close(pipe_save[1]);                                               // Pipe'ın yazma ucunu kapatıyoruz. okuması için
        char buffer[256];                                                  // Veriyi okumak için tampon bellek kullanıyoruz
        FILE *file = fopen("result.txt", "w");                             // Sonuçların yazılacağı dosya yani result.txt dosyası
        if (file == NULL) {
            perror("File opening failed");
            exit(EXIT_FAILURE);                                            // eğer herhangi bir hata ile karşılaşırsak çocuk süreci hatalı bir şekilde sonlandırırız
        }
                                                                           // Pipe'dan veri okuma kısmı
        while (read(pipe_save[0], buffer, sizeof(buffer)) > 0) {
            fprintf(file, "%s", buffer);                                  // veri okunursa dosyaya yaz
            memset(buffer, 0, sizeof(buffer));                            // geçici belleğiyani bufferi Tamponu sıfırlıyoruz ki yeni işlem yapabilelim
        }
        fclose(file);                                                     // Dosyayı kapat
        close(pipe_save[0]);                                              // Pipe'ın okuma ucunu kapatıyoruz
        exit(EXIT_SUCCESS);                                               // alt procesi yani chili başarılı sonlandır
    }
    close(pipe_save[0]);                                                 // Ana süreç yazma yapacağı için okuma ucunu kapatıyoruz çünkü aynı anda çalışamazlar

   
    while (1) {                                                          // exit olana kadar döngüye aldım

        printf("\n  CALCULATOR \n");
        printf("1 - Addition\n");
        printf("2 - Subtraction\n");
        printf("3 - Multiplication\n");
        printf("4 - Division\n");
        printf("5 - EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); 


        if (choice == 5) {                                              // eğer kullanıcı 5 girerse döngüden çık ve ana processi sonlandır
            printf("Exiting...\n");
            break; 
        }


        printf("Enter two numbers: \n");
        scanf("%d %d", &num1, &num2);


        // Toplama işlemi
        if (choice == 1) {
            pid = fork();                                           //parenti 2'e böl yeni process yani child process oluştur
            if (pid == 0) {                                         // Çocuk süreç = 0 seçeneği ile ayırt ederiz
                close(pipe_add[0]);                                 // Okuma ucunu kapatıyoruz
                close(1);                                           // Standart çıkışı kapat
                dup(pipe_add[1]);                                   // Pipe'ın yazma ucunu standart çıkışa yönlendir
                close(pipe_add[1]);                                 // Orijinal yazma ucunu kapat
                char num1_str[10], num2_str[10];
                sprintf(num1_str, "%d", num1);                      // sayıları stringe çevir çünkü pipe ineger olarak göndermiyor o yüzden strinde çevirerek göndermemiz lazım.
                sprintf(num2_str, "%d", num2);                   
                execl("./addition", "./addition", num1_str, num2_str, NULL); // Toplama işlemini yapan programı execute etme
                perror("execl");                                    //başarısız olursa hata mesajı ve çıkma
                exit(EXIT_FAILURE);
            }
            close(pipe_add[1]);                                     // Parent Process Pipe'ının yazma ucunu kapat
            wait(NULL);                                             // Çocuk sürecin tamamlanmasını bekle
            if (read(pipe_add[0], &result, sizeof(result)) <= 0) {  // Sonucu pipe'dan oku
                perror("read");
                continue; 
            }
            close(pipe_add[0]);                                     // Pipe'ın okuma ucunu kapat
        }
        
        // Çıkarma işlemi
        else if (choice == 2) {
            pid = fork();
            if (pid == 0) {
                close(pipe_sub[0]);
                close(1);
                dup(pipe_sub[1]);
                close(pipe_sub[1]);
                char num1_str[10], num2_str[10];
                sprintf(num1_str, "%d", num1);
                sprintf(num2_str, "%d", num2);
                execl("./subtraction", "./subtraction", num1_str, num2_str, NULL);
                perror("execl");
                exit(EXIT_FAILURE);
            }
            close(pipe_sub[1]);
            wait(NULL);
            if (read(pipe_sub[0], &result, sizeof(result)) <= 0) {
                perror("read");
                continue;
            }
            close(pipe_sub[0]);
        }
        
        // Çarpma işlemi
        else if (choice == 3) {
            pid = fork();
            if (pid == 0) {
                close(pipe_mul[0]);
                close(1);
                dup(pipe_mul[1]);
                close(pipe_mul[1]);
                char num1_str[10], num2_str[10];
                sprintf(num1_str, "%d", num1);
                sprintf(num2_str, "%d", num2);
                execl("./multiplication", "./multiplication", num1_str, num2_str, NULL);
                perror("execl");
                exit(EXIT_FAILURE);
            }
            close(pipe_mul[1]);
            wait(NULL);
            if (read(pipe_mul[0], &result, sizeof(result)) <= 0) {
                perror("read");
                continue;
            }
            close(pipe_mul[0]);
        }
        // Bölme işlemi
        else if (choice == 4) {
            pid = fork();
            if (pid == 0) {
                close(pipe_div[0]);
                close(1);
                dup(pipe_div[1]);
                close(pipe_div[1]);
                char num1_str[10], num2_str[10];
                sprintf(num1_str, "%d", num1);
                sprintf(num2_str, "%d", num2);
                execl("./division", "./division", num1_str, num2_str, NULL);
                perror("execl");
                exit(EXIT_FAILURE);
            }
            close(pipe_div[1]);
            wait(NULL);
            if (read(pipe_div[0], &result, sizeof(result)) <= 0) {
                perror("read");
                continue;
            }
            close(pipe_div[0]);
        } else {
            printf("Invalid choice! Please try again.\n");
            continue;
        }

        // Sonucu göster ve saver'a gönder
        printf("Result: %d\n", result);
        char buffer[256];
        if (choice == 1) {
            snprintf(buffer, sizeof(buffer), "Addition: %d + %d = %d\n", num1, num2, result);
        } else if (choice == 2) {
            snprintf(buffer, sizeof(buffer), "Subtraction: %d - %d = %d\n", num1, num2, result);
        } else if (choice == 3) {
            snprintf(buffer, sizeof(buffer), "Multiplication: %d * %d = %d\n", num1, num2, result);
        } else if (choice == 4) {
            snprintf(buffer, sizeof(buffer), "Division: %d / %d = %d\n", num1, num2, result);
        }
        write(pipe_save[1], buffer, strlen(buffer)); // Sonucu saver sürecine yaz
    }


    close(pipe_save[1]);                  // yazma ucu yanipipe(1) kapatıyoruz
    wait(NULL);                           // Saver subprocesin tamamlanmasını bekler
    return 0;                             //finish
}
//**********************************************************************************************************
*/

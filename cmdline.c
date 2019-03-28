#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){   
char command[100]; //gireceğimiz komut
char *parse1;  //parse işlemi yapıldıktan sonra komutun ilk parçası
char *parse2;  //parse işlemi yapıldıktan sonra komutun ilk parçası
char place[100];   //execl fonksiyonunda ilk argüman olarak kullanılacak konum bilgisi
int t;  //clear komutu için kullanılacak
int status; //waitpid fonksiyonunda kullanılacak durum
printf("-----------------------------------\n|\tTaylan GELEKÇİ\t\t  |\n|\t14290037\t\t  |\n|\tTerminalime Hoşgeldiniz\t  |\n-----------------------------------\n");

while(1){

fputs("% ", stdout);	  //prompt oluşturuldu		
fgets(command, 100, stdin);  //komut klavyeden alındı
pid_t childpid=fork();  //child process oluşturulup, fork fonksiyonuna yollandı

if(childpid<0){    //eğer child process id<0 ise hata dönecek
perror("Error");
exit(-1);
}

else if(childpid==0)     //child processin yapacağı işlemler
{

if (command[strlen(command) - 1] == '\n') {   //bu if olmazsa komutları girerken bir adet space karakteri girip sonra enter'a basmamız gerekir. 
command[strlen(command) - 1] = '\0';   //input girilirken doğal olarak gelen \n karakterini silip yerine \0 karakteri koyan kısım
}

parse1=strtok(command, " ");   //klavyeden alınan komut 2 parçaya parse edildi
parse2=strtok(NULL , " ");

sprintf(place, "%s%s", "/bin/", parse1);    //sprintf ile "/bin/" stringi ve parse edilen ilk kısım konum bilgisine atandı

execl(place, parse1, parse2, NULL);    //komutların sistemde tutulduğu konum bilgisi ve komut satırına girilen komuttan parse edilen parçalar, execl fonksiyonuna yollandı ve komutumuz execute edildi

t=strcmp(parse1, "clear");    //bu satır ve altındaki if, clear komutu içindir. parse edilen ilk kısım "clear" ile karşılaştırılır ve if in içinde konum kısmı belirlenerek clear komutu execute edilir 
if(t==0)
{
sprintf(place, "%s%s", "/usr/bin/", parse1);	// "/usr/bin/" stringi ve parse edilen ilk kısım konum bilgisine atandı
execl(place, parse1, NULL, NULL);
}

}

else{    //parent processin yapacağı işlemler 
waitpid(childpid, &status, 0);  //parent process, child processin bitmesini bekler
}

}

}

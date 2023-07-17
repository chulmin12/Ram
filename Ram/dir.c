#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <tchar.h>
#include <locale.h>

//디렉토리 리스트 구조체 
struct File_lst {
    char Desktop_list[100][100];
    char Downloads_list[100][100];
};


//디렉터리 타깃 구조체 
struct File_Target {
    char Desktop[100][100];  
    char Downloads[100][100];
    char Documents[100][100];
    char User[100][100];
};

struct File_Target target = { 0, };

void FileSearch(char* path_list) {
    //WIN32_FIND_DATA fd;
    struct _finddata_t fd;
    char buffer[256] = {0,};
    int i = 0, j=0 ;
    long handle;
    int result = 1;
    /*
    strcpy(aa.test[0], "ABC");
    strcpy(aa.test[1], "DEF");
    
    printf("%s\n", aa.test[0]); //ABC
    printf("%c\n", aa.test[0][0]) //A
    printf("%c\n", aa.test[0][1]); //B
    printf("%s\n", aa.test[1]);//DEF
    exit(0);
    */
    //"C:\\Users\\user\\Desktop\\*.txt"
    handle = _findfirst(path_list, &fd); // 폴더 내현재 모든 파일을 찾는다.

    if (handle == -1)
    {
        printf("There were no files.\n");
        return;
    }
    while (result != -1)
    {   
        char* Desk = strstr(path_list, "Desktop");
        char* Down = strstr(path_list, "Downloads");
        if (Desk != NULL) {
            //int i = 0;
            strcpy(buffer, fd.name);
            //printf("%s\n", buffer);
            char* ptr = strstr(buffer, ".txt");
            if (ptr != NULL) {
                strcpy(target.Desktop[i], buffer);  //aaaa.txt
                i++;
            }
        }
        else if (Down != NULL) {
           
            strcpy(buffer, fd.name);
            //printf("%s\n", buffer);
            char* ptr = strstr(buffer, ".txt");
            if (ptr != NULL) {
                strcpy(target.Downloads[i], buffer);
                i++;
            }
        }

       // printf("File: %s\n", fd.name);
        //printf("%d\n", result);
        
        result = _findnext(handle, &fd);    
     }
    //printf("%s\n", target.Desktop[1]);
    
    //printf("[+] function's target structure %p\n", &target);
    _findclose(handle);
}


int main() {
    DWORD dwsize = 1024;
    char strUserName[100] = { 0, };
    GetUserNameA(strUserName, &dwsize);
    //printf("%s", strUserName);
    char local[100] = "C:\\Users\\";
    strcpy(local + strlen(local), strUserName);
    strcpy(local + strlen(local), "\\Desktop\\*"); //함수 만들기
    printf("%s\n", local);

    
    char* path_list[3] = { local,"C:\\Users\\user\\Downloads\\*","C:\\Users\\user\\AppData\\Local\\Temp\\*" };

    /*
    for (int i = 0; i < strlen(path_list); i++) {
        printf("=================File_list===================\n");
        FileSearch(path_list[i]);
    }
    */

    FileSearch(path_list[0]);
    FileSearch(path_list[1]);
    //printf("[+] main's target structure %p\n", &target);
    printf("Desktop: %s\n", target.Desktop[0]);
    printf("Downloads: %s\n", target.Downloads[1]);
}

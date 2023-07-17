#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>


struct FileList {
    char Desktop[100][100];
    char Downloads[100][100];
    char Dcouments[100][100];
    char Temp[100][100];
};

struct FileList Filelist = { 0, };

char* FilePath(char* d_list) {
    DWORD dwsize = 1024;
    char strUserName[100] = { 0, };
    GetUserNameA(strUserName, &dwsize);

    char* local = (char*)malloc(256);
    strcpy(local, "C:\\Users\\");
    strcat(local, strUserName);
    strcat(local, d_list);

    return local;
}

void FileSearch(char* path) {
    WIN32_FIND_DATA FindData;
    HANDLE hFind;
    int i = 0 ;

    //printf("%s\n", path);
    hFind = FindFirstFileA(path, &FindData);




    if (hFind == INVALID_HANDLE_VALUE) {
        printf("no");
        return;
    }

    while (FindNextFileA(hFind, &FindData)) {
     
        char* Desk = strstr(path, "Desktop");
        char* Down = strstr(path, "Downloads");
        char* Dcou = strstr(path, "Documents");
        char* Temp = strstr(path, "Temp");

        if (Desk != NULL) {
            //printf("%s\n", FindData.cFileName);
            strcpy(Filelist.Desktop[i], FindData.cFileName);
           // printf("[+] Error Check %d\n", GetLastError());
           // printf("Desktop => %s\n", Filelist.Desktop[i]);
            i++;
        }
        else if (Down != NULL) {
            strcpy(Filelist.Downloads[i], FindData.cFileName);
            i++;
            //printf("%s\n", FindData.cFileName);
        }
        else if (Dcou != NULL) {
            strcpy(Filelist.Dcouments[i], FindData.cFileName);
            i++;
           // printf("[+] Error Check %d\n", GetLastError());
           // printf("%s\n", FindData.cFileName);
        }
        else if (Temp != NULL) {
            //printf("%s -> [%d] \n", path,i);  => 파일크기 구하는 함수가 필요 배열 100이였을때 그 값이 넘어서 예외처리됨
            strcpy(Filelist.Temp[i], FindData.cFileName);
            i++;
            //printf("%s\n", FindData.cFileName);
        }

      
    }
    FindClose(hFind);
}



int main() {
    char* Desktop = FilePath("\\Desktop\\*");
    //printf("%s\n", Desktop);
    FileSearch(Desktop);

    char* Downloads = FilePath("\\Downloads\\*");
    FileSearch(Downloads);

    char* Documents = FilePath("\\Documents\\*");
    FileSearch(Documents);
    
    char* Temp = FilePath("\\AppData\\Local\\Temp\\*");
    FileSearch(Temp);
    
    printf("-------DeskTop----------- %s\n", Filelist.Desktop[1]);
    printf("-------Downloads----------- %s\n", Filelist.Downloads[1]);
    printf("-------Documnents----------- %s\n", Filelist.Dcouments[1]);
    printf("-------Temp----------- %s\n", Filelist.Temp[11]);
    
}

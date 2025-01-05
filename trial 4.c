#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXS 10
#define MINS 3
#define MAXB 5
#define MAXTable 10000

typedef char ElementType[MAXS + 1];
//定义文件词汇索引表
typedef struct FileEntry{
    int words;
    struct FileEntry *Next;//指向下一个文件的指针

}WList;
//定义单词索引表
typedef struct WordEntry{
    int FileNo;//文件编号
    struct WordEntry *Next;//指向下一个文件编号的指针
}FList;
//定义哈希表的元素
struct HashEntry{
    ElementType Element;//单词
    int FileNo;
    FList *InvIndex;//单词的倒排索引表
};
//定义哈希表
typedef struct HashTbl{
    int TableSize;//哈希表的大小
    struct HashEntry *TheCells;//哈希表的静态数组
}HashTable;
//初始化哈希表
HashTable* Table_Init(int TableSize){
    HashTable *H = malloc(sizeof(HashTable));
    H->TableSize = TableSize;
    H->TheCells = malloc(sizeof(struct HashEntry) * H->TableSize);
    while (TableSize){
        H->TheCells[--TableSize].FileNo = 0;
        H->TheCells[TableSize].InvIndex = NULL;
    }
    return H;
}
//初始化文件词汇索引表
WList* FileIndex_Init(int Size){
    WList *F = malloc(sizeof(FList) * Size);
    while (Size){
        F[--Size].words = 0;
        F[Size].Next = NULL;
    }
    return F;
}
//读取单词
int GetWord(ElementType Word){
    char c;
    int p = 0;
    scanf("%c", &c);
    while (!isalpha(c) && (c!= '#'))
        scanf("%c", &c);
    if (c == '#')
        return 0;
    while (isalpha(c) && (p < MAXS)){
        Word[p++] = tolower(c);
        scanf("%c", &c);
    }
    while (isalpha(c))
        scanf("%c", &c);
    if (p < MINS)
        return GetWord(Word);
    else{
        Word[p] = '\0';
        return 1;
    }
}
//字符串移位法
int Hash(char *key,int p){
    unsigned int h = 0;
    while (*key!= '\0')
        h = (h << MAXB) + (*key++ - 'a');
    return h % p;
}
//在哈希表中分配单词并查找单词
int Find(ElementType key, HashTable *H){
    int pos = Hash(key, H->TableSize);
    while (H->TheCells[pos].FileNo && strcmp(H->TheCells[pos].Element, key)){
        pos++;
        if (pos == H->TableSize)
            pos -= H->TableSize;
    }
    return pos;
}
//在哈希表中插入单词并建立倒排索引表

int InsertAndIndex(int FileNo, ElementType key, HashTable *H){
    FList *F;
    int pos = Find(key, H);
    if (H->TheCells[pos].FileNo!= FileNo){
        if (!H->TheCells[pos].FileNo)
            strcpy(H->TheCells[pos].Element, key);
        H->TheCells[pos].FileNo = FileNo;
        F = malloc(sizeof(FList));
        F->FileNo = FileNo;
        F->Next = H->TheCells[pos].InvIndex;
        H->TheCells[pos].InvIndex = F;
        return pos;
    }
    else
        return -1;
}
//将单词
void FileIndex(WList *File, int FileNo, int pos){
    WList *W;
    if (pos < 0)
        return;
    W = malloc(sizeof(WList));
    W->words = pos;
    W->Next = File[FileNo-1].Next;
    File[FileNo-1].Next = W;
    File[FileNo-1].words++;
}

double work(WList *File, int F1, int F2, HashTable *H){
    int temp;
    WList *W;
    FList *F;
    if (File[F1-1].words > File[F2-1].words){
        temp = F1;
        F1 = F2;
        F2 = temp;
    }
    temp = 0;
    W = File[F1-1].Next;
    while (W) {
        F = H->TheCells[W->words].InvIndex;
        while (F) {
            if (F->FileNo == F2)
                break;
            F = F->Next;
        }
        if (F)
            temp++;
        W = W->Next;
    }
    return ((double)(temp * 100)/ (double)(File[F1 - 1].words + File[F2 - 1].words - temp));
}

int main(){
    int n, m, f1, f2;
    ElementType word;
    HashTable *H;
    WList *File;
    scanf("%d", &n);
    File = FileIndex_Init(n);
    H = Table_Init(MAXTable);
    int i;
    for ( i = 0; i < n; i++)
        while(GetWord(word))
            FileIndex(File, i + 1, InsertAndIndex(i+1, word, H));
    scanf("%d", &m);
    double similarity[m];
    for ( i = 0 ; i < m; i++){
        scanf("%d %d", &f1, &f2);
        similarity[i] = work(File, f1, f2, H);
    }
    for ( i = 0 ; i < m; i++){
        printf("%.1f%c\n", similarity[i], '%');
    }
    return 0;
}

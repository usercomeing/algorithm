#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100000

// 定义学生结构体
typedef struct {
    char id[7];
    char name[9];
    int score;
} Student;

// 全局变量，用于存储列号
int c;

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;

    // 根据指定的列号进行比较
    switch (c) {
        case 1:
            return strcmp(studentA->id, studentB->id);
        case 2:
            // 按照姓名的 ASCII 码大小进行非递减排序
            int nameCompare = strcmp(studentA->name, studentB->name);
            if (nameCompare == 0) {
                // 姓名相同时，按照学号进行递增排序
                return strcmp(studentA->id, studentB->id);
            } else {
                return nameCompare;
            }
        case 3:
            // 按照成绩进行非递减排序
            if (studentA->score == studentB->score) {
                // 成绩相同时，按照学号进行递增排序
                return strcmp(studentA->id, studentB->id);
            } else {
                return studentA->score - studentB->score;
            }
        default:
            return strcmp(studentA->id, studentB->id);
    }
}



int main() {
    int n;
    scanf("%d %d", &n, &c);

    // 动态分配内存来存储学生信息
    Student *students = (Student *)malloc(n * sizeof(Student));
    if (students == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // 输入学生信息
    int i;
    for ( i = 0; i < n; i++) {
        scanf("%s %s %d", students[i].id, students[i].name, &students[i].score);
    }

    // 排序
    qsort(students, n, sizeof(Student), compare);

    // 输出排序后的结果
    for ( i = 0; i < n; i++) {
        printf("%s %s %d\n", students[i].id, students[i].name, students[i].score);
    }

    // 释放内存
    free(students);
    system("pause");
    return 0;
}
#include <stdio.h>
#include <string.h>

typedef struct
{
  long int id;
  char name[50];
  int totalScore;
  int Number;
} Student;

Student students[3];

Student InitStudent(Student *student, long int id, char name[], int score)
{
  student->id = id;
  strcpy(student->name, name);
  student->totalScore = score;
  student->Number++;
  return *student;
}

double equalScore(Student *students, int count)
{
  double totalScore = 0;
  for (int i = 0; i < count; i++)
  {
    totalScore += students[i].totalScore;
  }
  return totalScore / students->Number ;
}

void SortScore(Student *students, int count)
{
  // 排序算法实现（例如冒泡排序）
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = 0; j < count - i - 1; j++)
    {
      if (students[j].totalScore < students[j + 1].totalScore)
      {
        Student temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
}

int main()
{
  Student student1 = InitStudent(&students[0], 123456, "张三", 100);
  Student student2 = InitStudent(&students[1], 123457, "李四", 90);
  Student student3 = InitStudent(&students[2], 123458, "王五", 95);

  double avgScore = equalScore(students, 3);
  printf("平均分: %f\n", avgScore);

  SortScore(students, 3);
  printf("按成绩排序:\n");
  for (int i = 0; i < 3; i++)
  {
    printf("ID: %ld, Name: %s, Score: %d\n", students[i].id, students[i].name, students[i].totalScore);
  }

  return 0;
}
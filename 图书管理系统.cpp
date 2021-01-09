#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book{
  int    id;
  char   name[20];
  double  price;
  char    author[20];
}BOOK;

struct node
{
  BOOK book;
  struct node* next;
};

void showMenu(struct node *head);
void addBook(struct node *head);
void queryBook(struct node *head);
void deleteBook(struct node *head);
void updateBook(struct node *head);
struct node* createBookNode(BOOK *book);
struct node* insertBookNode(struct node* head, BOOK *book);
struct node* createBookList();
void freeBookList(struct node* head);
struct node* queryBookListById(struct node* head, int id);
int deleteBookLstById(struct node* head, int id);
int getBookListLength(struct node* head);
void printBookLstInfo(struct node* head);
void saveBookListToFile(struct node* head);
void readBookListFromFile(struct node* head);
void error(const char* err);

int main() {
  system ("color 8b");
  struct node* list = createBookList();
  // 当文件books.txt已有图书信息时
  // 先全部读取所有书本信息
  readBookListFromFile(list);
  showMenu(list);
  int choice;
  while (1) {
    printf("\t\t\t\t****************请选择你想要的操作***************\n");
    scanf("%d",&choice);
      switch (choice) {
      case 0:
        freeBookList(list);
        system("cls");
        printf("\t\t\t\t****************欢迎下次继续使用***************\n");
        exit(0);
      case 1:
        addBook(list);
        break;
      case 2:
        queryBook(list);
        break;
      case 3:
        deleteBook(list);
        break;
      case 4:
        updateBook(list);
        break;
      default:
        printf("\n\t\t\t   输入错误，请重新输入\n\n\t\t\t    ");
		system("PAUSE");
      }
  }
  return 0;
}

struct node* createBookNode(BOOK *book)
{
  struct node* p = (struct node*)calloc(1,sizeof(struct node));
  BOOK *b;
  if(p != NULL)
  {
    if(book != NULL)
    {
      b = &(p->book);
      b->id = book->id;
      strcpy(b->name, book->name);
      b->price = book->price;
      strcpy(b->author, book->author);
    }
    p->next = NULL;
  }
  return p;
}


// 表尾增加图书结点
struct node* insertBookNode(struct node* head, BOOK *book)
{
  if(head != NULL)
  {
    struct node* node = createBookNode(book);
    BOOK *b = &(node->book);
    if(node != NULL)
    {
      struct node* p = head;

      while(p->next != NULL)
        p = p->next;

      p->next = node;
      return node;
    }
  }
  return NULL;
}


// 创建带头结点的图书空链表
struct node* createBookList()
{
  // 创建头结点
  return createBookNode(NULL);
}


// 释放图书链表内存空间
void freeBookList(struct node* head)
{
  struct node* p = head;
  while(p != NULL)
  {
    head = p->next;
    free(p);
    p = head;
  }
}


// 根据图书ID查找图书结点
struct node* queryBookListById(struct node* head, int id)
{

  struct node *p = NULL;
  if(head != NULL)
  {
    p = head->next;
    while(p != NULL)
    {
      if(p->book.id == id)
        break;
      p = p->next;
    }
  }
  return p;
}


// 根据图书ID删除图书结点
int deleteBookListById(struct node* head, int id)
{
  struct node *p = NULL, *pre = NULL;
  int status = 0;
  if(head != NULL)
  {
    pre = head;
    p = head->next;
    while(p != NULL)
    {
      if(p->book.id == id)
      {
        pre->next = p->next;
        free(p);
        status = 1;
        break;
      }
      pre = p;
      p = p->next;
    }
  }
  return status;
}


// 获取图书链表的长度
int getBookListLength(struct node* head)
{
  int n = 0;
  struct node *p = NULL;
  if(head != NULL)
  {
    p = head->next;
    while(p != NULL)
    {
      n++;
      p = p->next;
    }
  }
  return n;
}


// 打印出链表所有结点保存的图书信息
void printBookListInfo(struct node* head)
{
  struct node* p = head->next;
  printf("图书编号                 书名     价格     作者\n");
  BOOK *b;
  while(p != NULL)
  {
    b = &(p->book);


    printf("%8d %20s %8.2f %8s\n", b->id, b->name, b->price, b->author) ;
    p = p->next;
  }
}


// 文件保存图书链表所有信息
void saveBookListToFile(struct node* head)
{
  if(head != NULL)
  {
    struct node *p = head->next;
    FILE* fp = fopen("books.txt", "w+");
    if(fp != NULL)
    {
      while(p != NULL)
      {
        fprintf(fp, "%d %s %f %s\n", (p->book).id,(p->book).name, (p->book).price, (p->book).author);
        p = p->next;
      }
      fclose(fp);

    }else {

      error("打开book.txt文件失败，请检查!\n");
    }
  }
}

// 从文件读取图书信息保存到链表
void readBookListFromFile(struct node* head)
{
  FILE* fp = fopen("books.txt", "r+");
  BOOK book;
  if (fp != NULL) {
    while (fscanf(fp, "%d%s%lf%s%d", &book.id, book.name, \
      &book.price, book.author) != EOF) {

      insertBookNode(head, &book);
    }
    fclose(fp);
  }else {
    error("打开book.txt文件失败，请检查!\n");
  }
}


// 在屏幕显示各类出错信息，并退出程序
void error(const char* err)
{
  printf(err);
  exit(-1);
 }


void showMenu(struct node *head) {
  printf("----------欢迎使用图书管理系统----------\n\n");
  printf("当前系统共用图书%d本！\n\n", getBookListLength(head));
  printf("系统提供以下功能：\n");
  printf("1:添加图书\n");
  printf("2:查看图书\n");
  printf("3:删除图书\n");
  printf("4:修改图书\n");
  printf("0:退出系统\n\n");
}

void addBook(struct node *head) {

  printf("请您按提示添加图书信息：\n");
  printf("依次输入编号 书名 价格 作者信息，以空格分隔:\n");

  BOOK book;

   scanf("%d%s%lf%s", &book.id, book.name,&book.price,book.author);
    if (queryBookListById(head, book.id) != NULL)
      printf("该编号对应的图书信息已经存在，无法增加!\n");
    else {
      insertBookNode(head, &book);
      saveBookListToFile(head);
      printf("添加成功!\n");
    }
}
void queryBook(struct node *head) {


  printBookListInfo(head);
}


void deleteBook(struct node *head) {
  printf("请输入要删除的图书编号：");
  char a[1024];
  int id;
  scanf("%d",&id);

    if (deleteBookListById(head, id))
    {
      printf("该编号%d对应的图书信息删除成功!\n", id);

    }else
    {
      printf("该编号对应的图书信息不存在!\n");
    }
}
void updateBook(struct node *head) {
  printf("请输入要修改的图书编号：");
  int id ;
    scanf("%d", &id);
    struct node *p = queryBookListById(head, id);


    if (p == NULL)
      printf("该编号对应的图书信息不存在!\n");
    else {
      printf("该编号对应的图书信息如下，请按照提示修改：\n");
      printf("图书编号                 书名     价格     作者\n");
      BOOK *book = &(p->book);
      printf("%8d %20s %8.2f %8s\n",book->id, book->name, \
          book->price, book->author);

      printf("依次输入修改后的书名、价格、作者信息，以空格分隔:\n");
          scanf("%s%lf%s",book->name, &book->price, book->author);
        saveBookListToFile(head);
        printf("修改成功，修改后的图书信息如下：\n");
        printf("图书编号                 书名     价格     作者\n");
        printf("%8d %20s %8.2f %8s\n", book->id, book->name, book->price, book->author);
     }

}


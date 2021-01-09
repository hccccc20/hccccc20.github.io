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
  // ���ļ�books.txt����ͼ����Ϣʱ
  // ��ȫ����ȡ�����鱾��Ϣ
  readBookListFromFile(list);
  showMenu(list);
  int choice;
  while (1) {
    printf("\t\t\t\t****************��ѡ������Ҫ�Ĳ���***************\n");
    scanf("%d",&choice);
      switch (choice) {
      case 0:
        freeBookList(list);
        system("cls");
        printf("\t\t\t\t****************��ӭ�´μ���ʹ��***************\n");
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
        printf("\n\t\t\t   �����������������\n\n\t\t\t    ");
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


// ��β����ͼ����
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


// ������ͷ����ͼ�������
struct node* createBookList()
{
  // ����ͷ���
  return createBookNode(NULL);
}


// �ͷ�ͼ�������ڴ�ռ�
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


// ����ͼ��ID����ͼ����
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


// ����ͼ��IDɾ��ͼ����
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


// ��ȡͼ������ĳ���
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


// ��ӡ���������н�㱣���ͼ����Ϣ
void printBookListInfo(struct node* head)
{
  struct node* p = head->next;
  printf("ͼ����                 ����     �۸�     ����\n");
  BOOK *b;
  while(p != NULL)
  {
    b = &(p->book);


    printf("%8d %20s %8.2f %8s\n", b->id, b->name, b->price, b->author) ;
    p = p->next;
  }
}


// �ļ�����ͼ������������Ϣ
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

      error("��book.txt�ļ�ʧ�ܣ�����!\n");
    }
  }
}

// ���ļ���ȡͼ����Ϣ���浽����
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
    error("��book.txt�ļ�ʧ�ܣ�����!\n");
  }
}


// ����Ļ��ʾ���������Ϣ�����˳�����
void error(const char* err)
{
  printf(err);
  exit(-1);
 }


void showMenu(struct node *head) {
  printf("----------��ӭʹ��ͼ�����ϵͳ----------\n\n");
  printf("��ǰϵͳ����ͼ��%d����\n\n", getBookListLength(head));
  printf("ϵͳ�ṩ���¹��ܣ�\n");
  printf("1:���ͼ��\n");
  printf("2:�鿴ͼ��\n");
  printf("3:ɾ��ͼ��\n");
  printf("4:�޸�ͼ��\n");
  printf("0:�˳�ϵͳ\n\n");
}

void addBook(struct node *head) {

  printf("��������ʾ���ͼ����Ϣ��\n");
  printf("���������� ���� �۸� ������Ϣ���Կո�ָ�:\n");

  BOOK book;

   scanf("%d%s%lf%s", &book.id, book.name,&book.price,book.author);
    if (queryBookListById(head, book.id) != NULL)
      printf("�ñ�Ŷ�Ӧ��ͼ����Ϣ�Ѿ����ڣ��޷�����!\n");
    else {
      insertBookNode(head, &book);
      saveBookListToFile(head);
      printf("��ӳɹ�!\n");
    }
}
void queryBook(struct node *head) {


  printBookListInfo(head);
}


void deleteBook(struct node *head) {
  printf("������Ҫɾ����ͼ���ţ�");
  char a[1024];
  int id;
  scanf("%d",&id);

    if (deleteBookListById(head, id))
    {
      printf("�ñ��%d��Ӧ��ͼ����Ϣɾ���ɹ�!\n", id);

    }else
    {
      printf("�ñ�Ŷ�Ӧ��ͼ����Ϣ������!\n");
    }
}
void updateBook(struct node *head) {
  printf("������Ҫ�޸ĵ�ͼ���ţ�");
  int id ;
    scanf("%d", &id);
    struct node *p = queryBookListById(head, id);


    if (p == NULL)
      printf("�ñ�Ŷ�Ӧ��ͼ����Ϣ������!\n");
    else {
      printf("�ñ�Ŷ�Ӧ��ͼ����Ϣ���£��밴����ʾ�޸ģ�\n");
      printf("ͼ����                 ����     �۸�     ����\n");
      BOOK *book = &(p->book);
      printf("%8d %20s %8.2f %8s\n",book->id, book->name, \
          book->price, book->author);

      printf("���������޸ĺ���������۸�������Ϣ���Կո�ָ�:\n");
          scanf("%s%lf%s",book->name, &book->price, book->author);
        saveBookListToFile(head);
        printf("�޸ĳɹ����޸ĺ��ͼ����Ϣ���£�\n");
        printf("ͼ����                 ����     �۸�     ����\n");
        printf("%8d %20s %8.2f %8s\n", book->id, book->name, book->price, book->author);
     }

}


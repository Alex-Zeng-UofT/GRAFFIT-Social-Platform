/**
 * CSC A48 - Intro to Computer Science II, Summer 2021
 * 
 * Assignment 3 - Graffit
 * 
 * Graphs &
 * Recursion
 * Assignment
 * For
 * Freshmen
 * In
 * Toronto
 *
 * (I am so proud of that initialism.)
 * 
 * This is the program file where you will implement your solution for
 * Assignment 3. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will also need to have read the handout carefully. 
 * 
 * Parts where you have to implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive
 * and will check that your solution is *correct*, not only that it
 * provides functionality.
 * 
 * (c) 2020 William Song, Mustafa Quraish
 * (c) 2021 Charles Xu
 **/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3 // A small graph
#endif

typedef struct user_struct
{
  char name[MAX_STR_LEN];
  struct friend_node_struct *friends;
  struct brand_node_struct *brands;
  bool visited;
  struct friend_node_struct* userList;
} User;

typedef struct friend_node_struct
{
  User *user;
  struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct
{
  char brand_name[MAX_STR_LEN];
  struct brand_node_struct *next;
} BrandNode;

FriendNode *allUsers = NULL;

int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Given the head to a FriendNode linked list, returns true if a
 * given user's name exists in the list. Returns false otherwise.
 */
bool in_friend_list(FriendNode *head, User *node)
{
  for (FriendNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->user->name, node->name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a BrandNode linked list, returns true if a
 * given brand's name exists in the list. Returns false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name)
{
  for (BrandNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->brand_name, name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a FriendNode linked list, inserts a given user
 * into the linked list and returns the head of the new linked list.
 * The insertion is done in alphabetical order. If the user already
 * exists, no modifications are made and the list is returned as is.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (in_friend_list(head, node))
  {
    printf("User already in list\n");
    return head;
  }

  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->user->name, node->name) > 0)
  {
    fn->next = head;
    return fn;
  }

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a BrandNode linked list, inserts a given brand into
 * the linked list and returns the head of the new linked list. The
 * insertion is done in alphabetical order. If the brand already exists,
 * no modifications are made and the list is returned as is.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (in_brand_list(head, node))
  {
    printf("Brand already in list\n");
    return head;
  }

  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->brand_name, node) > 0)
  {
    fn->next = head;
    return fn;
  }

  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a FriendNode linked list, removes a given user from
 * the linked list and returns the head of the new linked list. If the user
 * does not exist, no modifications are made and the list is returned as is.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (!in_friend_list(head, node))
  {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0)
  {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given the head to a BrandNode linked list, removes a given brand from
 * the linked list and returns the head of the new linked list. If the brand
 * does not exist, no modifications are made and the list is returned as is.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (!in_brand_list(head, node))
  {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0)
  {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given a user, prints their name, friends, and liked brands.
 */
void print_user_data(User *user)
{
  printf("User name: %s\n", user->name);

  printf("Friends:\n");
  for (FriendNode *f = user->friends; f != NULL; f = f->next)
  {
    printf("   %s\n", f->user->name);
  }

  printf("Brands:\n");
  for (BrandNode *b = user->brands; b != NULL; b = b->next)
  {
    printf("   %s\n", b->brand_name);
  }
}

/**
 * Given a brand, returns the index of the brand inside the brand_names array.
 * If it doesn't exist in the array, return -1
 */
int get_brand_index(char *name)
{
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (strcmp(brand_names[i], name) == 0)
    {
      return i;
    }
  }

  printf("Brand '%s' not found\n", name);
  return -1; // Not found
}

/**
 * Given a brand, prints their name, index (inside the brand_names
 * array), and the names of other similar brands.
 */
void print_brand_data(char *brand_name)
{
  int idx = get_brand_index(brand_name);
  if (idx < 0)
  {
    printf("Brand '%s' not in the list.\n", brand_name);
    return;
  }

  printf("Brand name: %s\n", brand_name);
  printf("Brand idx: %d\n", idx);

  printf("Similar brands:\n");
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (brand_adjacency_matrix[idx][i] == 1 && strcmp(brand_names[i], "") != 0)
    {
      printf("   %s\n", brand_names[i]);
    }
  }
}

/**
 * Read from a given file and populate a the brand list and brand matrix.
 **/
void populate_brand_matrix(char *file_name)
{
  // Read the file
  char buff[MAX_STR_LEN];
  FILE *f = fopen(file_name, "r");
  fscanf(f, "%s", buff);
  char *line = buff;
  // Load up the brand_names matrix
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (i == MAT_SIZE - 1)
    {
      strcpy(brand_names[i], line);
      break;
    }
    int index = strchr(line, ',') - line;
    strncpy(brand_names[i], line, index);
    line = strchr(line, ',') + sizeof(char);
  }
  // Load up the brand_adjacency_matrix
  for (int x = 0; x < MAT_SIZE; x++)
  {
    fscanf(f, "%s", buff);
    for (int y = 0; y < MAT_SIZE; y++)
    {
      int value = (int)buff[y * 2];
      if (value == 48)
      {
        value = 0;
      }
      else
      {
        value = 1;
      }
      brand_adjacency_matrix[x][y] = value;
    }
  }
}



/**
 * TODO: Complete this function
 * Creates and returns a user.
 */
User *create_user(char *name)
{ 
  FriendNode *h=allUsers;
  while(h!=NULL){
    if(strcmp(h->user->name, name)==0){
      return NULL;
    }
    h=h->next;
  }
  User *p=(User*)calloc(1, sizeof(User));
  strcpy(p->name, name);
  p->friends=NULL;
  p->brands=NULL;
  p->visited=false;
  allUsers=insert_into_friend_list(allUsers, p);
  p->userList=allUsers;
  return p;
}

int num_of_set_false()
{
  FriendNode *h;
  int count=0;
  for(h=allUsers;h!=NULL;h=h->next)
  { 
    h->user->visited=false;
    count++;
  }
  return count;
}

/**
 * TODO: Complete this function
 * Deletes a given user.
 */
int delete_user(User *user)
{ 
  if(!in_friend_list(allUsers,user)){
    return -1;
  }
  FriendNode *p=user->friends,*q=NULL;
  while(p!=NULL){
    q=p->next;
    free(p);
    p=q;
  }
  BrandNode *i=user->brands,*j=NULL;
  while(i!=NULL){
    j=i->next;
    free(i);
    i=j;
  }
  user->friends=NULL;
  user->brands=NULL;
  allUsers=delete_from_friend_list(allUsers,user);
  FriendNode *h=NULL;
  for(h=allUsers; h!=NULL; h=h->next){
    if(in_friend_list(h->user->friends, user)){
      h->user->friends=delete_from_friend_list(h->user->friends, user);
    }
  }
  free(user);
  return 0;
}

/**
 * TODO: Complete this function
 * Create a friendship between user and friend.
 */
int add_friend(User *user, User *friend)
{
  if(in_friend_list(user->friends,friend)&&in_friend_list(friend->friends,user)){
    return -1;
  }
  user->friends=insert_into_friend_list(user->friends, friend);
  friend->friends=insert_into_friend_list(friend->friends, user);
  return 0;
}

/**
 * TODO: Complete this function
 * Removes a friendship between user and friend.
 */
int remove_friend(User *user, User *friend)
{
  if(!in_friend_list(user->friends,friend)&&!in_friend_list(friend->friends,user)){
    return-1;
  }
  user->friends=delete_from_friend_list(user->friends, friend);
  friend->friends=delete_from_friend_list(friend->friends, user);
  return 0;
}

/**
 * TODO: Complete this function
 * Creates a follow relationship, the user follows the brand.
 */
int follow_brand(User *user, char *brand_name)
{ 
  if(in_brand_list(user->brands, brand_name)||get_brand_index(brand_name)==-1){
    return -1;
  }
  user->brands=insert_into_brand_list(user->brands,brand_name);
  return 0;
}

/**
 * TODO: Complete this function
 * Removes a follow relationship, the user unfollows the brand.
 */
int unfollow_brand(User *user, char *brand_name)
{
  if(!in_brand_list(user->brands, brand_name)||get_brand_index(brand_name)==-1){
    return -1;
  }
  user->brands=delete_from_brand_list(user->brands, brand_name);
  return 0;
}

/**
 * TODO: Complete this function
 * Return the number of mutual friends between two users.
 */
int get_mutual_friends(User *a, User *b)
{ 
  FriendNode *friend=NULL;
  int count=0;
  for(friend=a->friends; friend!=NULL; friend=friend->next){
    if(in_friend_list(b->friends,friend->user)){
      count++;
    }
  }
  return count;
}

/**
 * TODO: Complete this function
 * A degree of connection is the number of steps it takes to get from
 * one user to another. Returns a non-negative integer representing
 * the degrees of connection between two users.
 */
int get_user_in(User *user) 
{
  if(!in_friend_list(allUsers, user)) 
  { 
    return -1;
  }
  FriendNode *h;
  int count=0;
  for (h=allUsers;h!=NULL;h=h->next)
  {
    if(strcmp(user->name,h->user->name) == 0) 
    { 
      return count;
    }
    count++;
  }
  return -1; 
}

FriendNode *insert_at_tail(FriendNode *head, User *user) 
{
  FriendNode *friend=(FriendNode*)calloc(1, sizeof(FriendNode));
  friend->user=user;
  friend->next=NULL;
  if(head==NULL){ 
    return friend;
  }
  FriendNode *h=head;
  while(h->next!=NULL){
    h=h->next;
  }
  h->next=friend;
  return head;
}

FriendNode *del_head(FriendNode *head) 
{
  if(head==NULL){
    return NULL;
  }
  FriendNode *del=head,*p=head->next; 
  free(del);
  return p;
}

int get_degrees_of_connection(User *a, User *b) 
{
  int nodes = num_of_set_false(); 
  int arr[nodes];
  int *lst=&arr[0]; 
  for(int i=0;i<nodes;i++){
    *(lst+i)=0; 
  }
  FriendNode *head_node=NULL,*cur,*del; 
  a->visited=true; 
  head_node=insert_at_tail(head_node,a);
  while(head_node!=NULL){
    User *u=head_node->user;
    head_node=del_head(head_node);
    cur=u->friends;
    while(cur != NULL){
      if(cur->user->visited==false){
        cur->user->visited=true;
        head_node=insert_at_tail(head_node,cur->user);
        *(lst+get_user_in(cur->user))+=1+*(lst+get_user_in(u));
        if(strcmp(cur->user->name,b->name)==0){
          int best=*(lst+get_user_in(cur->user));
          while(head_node!=NULL){
            del=head_node;
            head_node = head_node->next;
            free(del);
          }
          free(lst);
          num_of_set_false();
          return best;
        } 
      }
      cur=cur->next;
    }
  }
  free(lst);
  num_of_set_false();
  return -1;
}


/**
 * TODO: Complete this function
 * Marks two brands as similar.
 */
void connect_similar_brands(char *brandNameA, char *brandNameB)
{
  int b1=get_brand_index(brandNameA);
  int b2=get_brand_index(brandNameB);
  if(b1!=-1&&b2!=-1){
    brand_adjacency_matrix[b1][b2]=1;
    brand_adjacency_matrix[b2][b1]=1;
  }
  return;
}

/**
 * TODO: Complete this function
 * Marks two brands as not similar.
 */
void remove_similar_brands(char *brandNameA, char *brandNameB)
{
  int b1=get_brand_index(brandNameA);
  int b2=get_brand_index(brandNameB);
  if(b1!=-1&&b2!=-1){
    brand_adjacency_matrix[b1][b2]=0;
    brand_adjacency_matrix[b2][b1]=0;
  }
  return;
}

/**
 * TODO: Complete this function
 * Returns a suggested friend for the given user.
 */
User *get_suggested_friend(User *user)
{ 
  FriendNode *u=NULL;
  int cur_max=0;
  User *best=NULL;
  for(u=allUsers; u!=NULL; u=u->next){
    if(u->user!=user&&!in_friend_list(user->friends,u->user)){
      int count=0;
      BrandNode *b=NULL;
      for(b=u->user->brands;b!=NULL;b=b->next){
        if(in_brand_list(user->brands,u->user->brands->brand_name)){
          count++;
        }
      }
      if(count>=cur_max){
        cur_max=count;
        best=u->user;
      }
    }
  }
  return best;
}

/**
 * TODO: Complete this function
 * Adds n suggested friends for the given user.
 * Returns how many friends were successfully followed.
 */
int add_suggested_friends(User *user, int n)
{ 
  int count=0;
  while(count<n){
    User *suggestion=get_suggested_friend(user);
    if(suggestion==NULL){
      break;
    }
    add_friend(user,suggestion);
    count++;
  }
  return count;
}

char *get_suggested_brand(User *user){
  char *best=NULL;
  int cur=0;
  BrandNode *head=NULL;
  for(int i=0; i<MAT_SIZE; i++){
    head=insert_into_brand_list(head, brand_names[i]);
  }
  BrandNode *h=NULL;
  for(h=head;h!=NULL;h=h->next){
    if(!in_brand_list(user->brands,h->brand_name)){
      int count=0;
      BrandNode *p=NULL;
      int i=get_brand_index(h->brand_name);
      for(p=user->brands;p!=NULL;p=p->next){
        int j=get_brand_index(p->brand_name);
        if(brand_adjacency_matrix[i][j]==1){
          count++;
        }
      }
      if(count>=cur){
        cur=count;
        best=h->brand_name;
      }
    }
  }
  return best;
}
/**
 * TODO: Complete this function
 * Follows n suggested brands for the given user.
 * Returns how many brands were successfully followed.
 */
int follow_suggested_brands(User *user, int n)
{
  int count=0;
  while(count<n){
    if(get_suggested_brand(user)==NULL){
      break;
    }
    follow_brand(user, get_suggested_brand(user));
    count++;
  }
  return count;
}

void print_followed_brands(User* user){
  BrandNode *p=NULL;
    for(p=user->brands;p!=NULL;p=p->next){
        printf("%s\n",p->brand_name);
    }
  return;
}
void print_friends(User* user){
  FriendNode *p=NULL;
  for(p=user->friends;p!=NULL;p=p->next){
    printf("%s\n", p->user->name);
  }
  return;
}

int num_friends(User *user){
  int i=0;
  FriendNode *p=NULL;
  for(p=user->friends;p!=NULL;p=p->next){
    i++;
  }
  return i;
}

int num_followed_brands(User *user){
  int i=0;
  BrandNode *p=NULL;
  for(p=user->brands;p!=NULL;p=p->next){
    i++;
  }
  return i;
}
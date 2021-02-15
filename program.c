#include <stdio.h>
#include <stdlib.h>
#include "lib/cs50.h"

//#define DEBUG

int cc[16];
int length = 0;

/*
 *  Zero-ing an array, to make sure its values are 0
 */
void zero_arr(int *a, int length, int offset)
{
  for(int i=offset;i<length;i++)
  {
    a[i] = 0;
  }
}

/*
 *  Print an array on one row
 */
void print_arr(int *a, int len) 
{
  for(int i=0;i<len;i++) 
  {
    printf("%i:", a[i]);
  }
  printf("\n");
}

/*
 * If error occurs, exit program
 */
void exit_error()
{
  printf("INVALID\n");
  exit(1);
}

/* 
 * Check input if length between and including 13 and 17
 */
int check_length_input(int number, int length)
{
  if(number > 0 && length >= 16)
  {
    exit_error();
  }
  else if(number == 0 && length < 13)
  {
    exit_error();
  }  
  else if(number == 0 && (length >= 13 || length <= 16))
  {
    return 1;
  }
  return 0;
}

/*
 * split long into int[]
 */
void preprocess_input(long input_number)
{ 
  zero_arr(cc, 16, 0);

  #ifdef DEBUG
  print_arr(cc, 16);
  #endif

  long number = input_number;
  for(int i=0;i<16;i++)
  {
    cc[i] = number % 10;
    number = number / 10;
    length = i+1;

    #ifdef DEBUG
    printf("nr: %li; cc: %i; len: %i;\n", number, cc[i], length); 
    #endif

    if(check_length_input(number,length) == 1)
    {
      #ifdef DEBUG
      printf("cc array : ");
      print_arr(cc, 16);
      #endif

      return;
    }
  }
}

/*
 * Check syntactical correctness of creditcardnumber
 */
void check_syntax_input()
{ 
  int mul_arr[16];
  int res_arr[16];
  int mul_cnt = 0;
  int res_cnt = 0;
  // second to last, every other,
  for(int j=0;j<length;j++)
  {
    if(j%2 == 0)
    {
      res_arr[res_cnt]=cc[j];
      res_cnt++;
    }
    else
    {
      mul_arr[mul_cnt]=cc[j];
      mul_cnt++;
    }
  }
  zero_arr(mul_arr, 16, mul_cnt);
  zero_arr(res_arr, 16, res_cnt);

  #ifdef DEBUG
  printf("mul_array: ");
  print_arr(mul_arr, 16);
  printf("mul_cnt: %i\n", mul_cnt);
  printf("res_array: ");
  print_arr(res_arr, 16);
  printf("res_cnt: %i\n", res_cnt);
  #endif

  // multiply by two,
  for(int i=0;i<mul_cnt;i++)
  {
    // a single left shift == times 2 (*2) operand.
    int tmp = mul_arr[i] << 1;
    // split if two decimals are used
    if(tmp > 9)
    {
      mul_arr[i] = tmp / 10;
      mul_arr[mul_cnt+i] = tmp % 10;
    } 
    // otherwise just overwrite value
    else
    {
      mul_arr[i] = tmp;
    }
  } 

  #ifdef DEBUG
  printf("mul_array: ");
  print_arr(mul_arr, 16);
  #endif
  
  // cumulative sum
  int sum = 0;
  for(int i=0;i<16;i++)
  {
    sum+=mul_arr[i]+res_arr[i];
  }

  #ifdef DEBUG
  printf("sum: %i\n",sum);
  #endif
  
  // the final validation  
  if(sum % 10 != 0)
  {
    exit_error();    
  }
}

/*
 * Check brand_nr against each value of brand_arr
 */
int check_brand_array(int *brand_arr, int length, int brand_nr)
{
  for(int i=0;i<length;i++)
  {
    if(brand_nr == brand_arr[i])
    {
      return 1;
    }
  }
  //if somehow ending up here, means the card is valid, 
  // but not one of the big brands mentioned in exercise.
  return 0;
}

/*
 * Check for major brands, by first decimals
 */
void check_brand()
{
  int mastercard[5] = {51,52,53,54};
  int amer_exprs[2] = {34,37};
  int visa[1]       = {4};
  
  int brand = cc[length-1]*10+(cc[length-2]);

  #ifdef DEBUG
  printf("len: %i; first two dec: %i %i -> %i\n",
         length, cc[length-1]*10, cc[length-2], cc[length-1]*10+cc[length-2]);
  printf("brandnr: %i\n", brand);
  #endif

  // VISA check (bit different than other)
  if(brand/10 == visa[0])
  {
    printf("VISA\n");
    return;
  } 
  // American Express check
  else if(check_brand_array(amer_exprs,2,brand) == 1)
  {
    printf("AMERICAN EXPRESS\n");
    return;
  }
  // MasterCard check
  else if(check_brand_array(mastercard,5,brand) == 1)
  {
    printf("MASTERCARD\n");
    return;
  }
  else
  {
    printf("UNKNOWN\n");
    return;
  }
}

int main(void) 
{
  long input = 0;
  input = get_long("Number: ");
  printf("%li\n", input);
  preprocess_input(input);
  check_syntax_input();
  check_brand();
  exit(0);
}

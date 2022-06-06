#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Initializing Status Array
    unsigned char s[256];
    printf("Step1: Initializing Status Array:\n");
    for(int i = 0; i<sizeof(s); i++)
    {
        s[i] = i;
    }
    printCharArray(&s, sizeof(s));

    //Input Text to Encrypt
    printf("Step2: Input the text to encrypt: ");
    unsigned char *text = malloc(sizeof(unsigned char));
    int text_size = safeinput(text,sizeof(s)-1);

    //Input of the Key
    printf("Step3: Input the key to encrypt the text with: ");
    unsigned char *key = malloc(sizeof(unsigned char));
    int key_size = safeinput(key,sizeof(s)-1);

    //Key Sheduling Algorithm
    printf("\nStep3: Key Sheduling Algorithm\n");
    keyShedulingAlgorithm(&s, sizeof(s),key,key_size);
    printf("Status Array after KSA:\n");
    printCharArray(&s, sizeof(s));
    waitForContinue();

    //pseudo-random number generation algorithm(PRGA)
    printf("\nStep4: Generate pseudo-random number to Encrypt(XOR) the input Text\n");
    unsigned char *prn = malloc(text_size);
    prgAlgorithm(&s, sizeof(s), prn,text_size);

    printf("Pseudo-random number: ");
    printCharArray(prn, text_size);

    printf("Input Text: ");
    printCharArrayChar(text, text_size);

    printf("Encrypted Text: ");
    Encrypt(text,prn, text_size);
    printCharArrayChar(text, text_size);

    printf("Decrypted Text: ");
    Encrypt(text,prn, text_size);
    printCharArrayChar(text, text_size);
    return 0;
}

void waitForContinue()
{
    printf("\nPress Enter to continue");
    while(getchar() != '\n'){}
}

void printCharArray(unsigned char *array, size_t size)
{
    for(int i = 0; i<(int)size; i++)
    {
        printf("%3d ",*(array+i));
    }
    printf("\n");
}

void printCharArrayChar(unsigned char *array, size_t size)
{
    for(int i = 0; i<(int)size; i++)
    {
        printf("%c",*(array+i));
    }
    printf("\n");
}

void keyShedulingAlgorithm(unsigned char *s, size_t size, unsigned char *key, size_t key_size )
{
    int j = 0;
    for(int i = 0; i< size; i++)
    {
        j = ( j + (int)*(s+i) + (int)*(key+(i%key_size)))%size;
        printf("Swapping %3d(Value: %3d) with %3d(Value: %3d) \n", i,(int)*(s+i),j,(int)*(s+j));
        swap(s, i, j);
    }
}

void prgAlgorithm(unsigned char *s, size_t size, unsigned char *prn, int text_size)
{
    int i = 0;
    int j = 0;

    for(int k = 0;k<text_size;k++)
    {
        i = (i+1) % size;
        j = (j + (int)*(s+i)) % size;
        swap(s, i, j);
        *(prn+k) ^= *(s+((int)*(s+i)+(int)*(s+j))%size);
    }

}

void swap(unsigned char *s, int index1, int index2)
{
    *(s+index1) ^= *(s+index2);
    *(s+index2) ^= *(s+index1);
    *(s+index1) ^= *(s+index2);
}

int safeinput(unsigned char *word, unsigned int max)
{

  unsigned char character;
  int loops = 0;


  while((character = getchar()) != '\n' && character != EOF)
  {
      if((int)character >= 0 && (int)character < max)
      {
          strcpy(word + loops,&character);
          loops = loops + 1;
          word = realloc(word,(loops +1)*sizeof(char));
      }
      else
      {
        printf("Wrong Input detected!\n");
        return EXIT_FAILURE;
      }
  }
  if(loops == 0)
  {
      printf("No Input detected!\n");
      return EXIT_FAILURE;
  }
  return loops;

}

void Encrypt(unsigned char *text, unsigned char *prn,int text_size)
{
    for(int i = 0; i<text_size;i++)
    {
        *(text+i) = *(text+i)^*(prn+i);
    }
}


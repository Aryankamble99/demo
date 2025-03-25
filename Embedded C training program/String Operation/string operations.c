//strcpy

#include<stdio.h>
#include<string.h>
/*int main()
{
    char a[]="Aryan Kamble";
    char b[10];
    strcpy(b,a);
    printf("\n %s",b);
}*/

// Strcmp 

/*int main()
{
    char str1[]="Aryan";
    char str2[]="Aryan";
    int res = strcmp(str1,str2);
    if(res==0)
    printf("\n Strings are Same");
    else
    printf("\n Strings are not same");
}*/


//strlen

/*int main()
{
    char arr[]="ABSooE";
    
    printf("\n%d",strlen(arr));
}*/

//strcat and strncat (Concatenation)

/*int main()
{
    char dest[20]="hello";
    char source[] ="world";
    strcat(dest,source);
    printf("%s\n",dest);

    char dest1[10]="hi ";
    strncat(dest1, "Aryan",2);
    printf("%s\n",dest1);
    return 0;
}*/


//strtok  (tokenizaton)
/*int main()
{
    char arr[]="Apple,Banana,Mango";
    char *token = strtok(arr,",");

    while(token!=NULL)
    {
        printf("%s\n",token);
        token = strtok(NULL,",");
    }
    return 0;
}*/

/*int main() {
    char str[] = "apple,banana,grape";
    char *token = strtok(str, ",");  // First token

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");  // Get next token
    }
    return 0;
}*/

//strncmp

/*int main()
{
    if(strncmp("apple","appricot",3)==0)
    printf("First 3 char are equal\n");
    else
    printf("First 3 Char are not equal");
}*/
#include <stdio.h>
#include<math.h>


int gcd(int a,int h)
{
    int temp;
	while (1) {
		temp = a % h;
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
}
int main()
{   double prime1=2;
    double prime2=11;

    double n = prime1*prime2;
    double e=2;

    double phi=(prime1 -1)*(prime2-1);

    while(e<phi)
    {
        if(gcd(e,phi)==1)
        {
            break;
        }
        else
        {
            e++;
        }
    }
    int k=2;

    double d= ((k*phi) + 1) / e;

    double msg = 9;
 
    printf("Message data = %lf \n", msg);

    double cipheredtext= pow(msg,e);
    cipheredtext= fmod(cipheredtext,n);

    printf("Ciphered Text = %lf \n", cipheredtext);

    //decryption

    double message= pow(cipheredtext,d);
    message=fmod(message,n);

    printf("Decrypted Message = %lf \n",message);


    
    return 0;
}
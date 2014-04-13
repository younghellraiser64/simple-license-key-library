/*
    Simple License Key Library
	By Martin Coleman (www.martincoleman.com). Dedicated to the public domain.

	Created 2012-06-25
	- This was made for a small programing job, which later fell through.

	Version 0.9 - 2012-07-01
	- No functional changes, just releasing it under the GNU LGPL v3.
	- At some point I may add full hexadecimal support.

    Version 0.9a - 2013-05-19
    - Changed to the BSD 2-Clause license.

    Version 0.9b - 2014-04-13
    - Dedicated to the public domain.
*/
#include <windows.h>
#ifdef V_DEBUG
#include <stdio.h>
#endif
#include <string.h>

int is_even(int num)
{
	if((num & 1) == 0)
	{
		/* is even */
		return 1;
	} else {
		return 0;
	}
}

int key_check(char *serial_key)
{ 
	char *s_num1, *s_num2, *s_num3, *s_num4;
	// char *c_num1, *c_num2, *c_num3, *c_num4;
	int d_num1, d_num2, d_num3, d_num4, d_num12, d_num44;
	int d_num13, d_num23, d_num33, d_num43;
	char *tok;

	if(strlen(serial_key)<23)	/* is it even the required length? */
	{
		printf("Error validating key.\n");
		return 0;
	}

	/* get the number segments into strings */
	s_num1=strtok(serial_key, "-");
	s_num2=strtok(NULL, "-");
	s_num3=strtok(NULL, "-");
	s_num4=strtok(NULL, "-");

	/* convert to decimals */
	d_num1=s_num1[0]-'0';
	d_num2=s_num2[0]-'0';
	d_num3=s_num3[0]-'0';
	d_num4=s_num4[0]-'0';
	d_num12=s_num1[1]-'0';
	d_num44=s_num4[4]-'0';

	d_num13=s_num1[2]-'0';
	d_num23=s_num2[2]-'0';
	d_num33=s_num3[2]-'0';
	d_num43=s_num4[2]-'0';


	/* FOR DEBUGGING */
	#ifdef V_DEBUG
	printf("%d\n", d_num1);
	printf("%d\n", d_num2);
	printf("%d\n", d_num3);
	printf("%d\n", d_num4);
	printf("%d %d\n", d_num1, (d_num2 + d_num3 + d_num4));
	#endif

	/* old routine
	if(d_num1 == (d_num2 + d_num3 + d_num4))
	{
		if(d_num12 % 2)
		{
			if(d_num44 % 2)
			{
				if( (is_even(d_num13)) && (is_even(d_num13)) && (is_even(d_num13)) && (is_even(d_num13)) )
				{
					return 1;
				} else {
					return 0;
				}
			}
		}
	}
	*/
	if(d_num1 == (d_num2 + d_num3 + d_num4))
	{
		if( (!is_even(d_num12)) && (!is_even(d_num44)) )
		{
			if( (is_even(d_num13)) && (is_even(d_num13)) && (is_even(d_num13)) && (is_even(d_num13)) )
			{
				return 1;
			} else {
				return 0;
			}
		}
	}
	return 0;
}

#ifdef V_DEBUG
int main_test(int argc, char *argv[])
{
	// char lic_key[]="31245-12445-12645-12847";
	char *lic_key;
	if(argc<2)
	{
		printf("No license key specified.\n");
		return 0;
	}
	lic_key=argv[1];
	printf("Validating %s\n", lic_key);
	if(key_check(lic_key))
	{
		printf("Key is valid!\n");
	} else {
		printf("Error: Key is invalid.\n");
	}
	return 0;
}
#else
// DLL entry function (called on load, unload, ...)
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
    return TRUE;
}
 
extern "C" __declspec(dllexport) int verify_key(char *key)
{
	return key_check(key);
}
#endif

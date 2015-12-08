#include <stdio.h>
#include <stdlib.h>

/** author: mayukh
 * github.com/mayukh42
 */

/** A simple file encrypter
 * based on the Caesar Cipher
 * usage: 
 	$ ./sealer -e rawfile key
 	$ ./sealer -d encryptedfile key
 */

const char * efile = "text/sealed.txt";
const char * dfile = "text/unsealed.txt";


void encrypt (const char * file, int k) {
	FILE * inp = fopen (file, "r");
	FILE * out = fopen (efile, "w");
	int c;
	while ((c = getc(inp)) != EOF) 
		putc (c+k, out);
	fclose (out);
	fclose (inp);
}


void decrypt (const char * file, int k) {
	FILE * inp = fopen (file, "r");
	FILE * out = fopen (dfile, "w");
	int c;
	while ((c = getc(inp)) != EOF) 
		putc (c-k, out);
	fclose (out);
	fclose (inp);
}


void runTests() {
	char * inp = "text/letter.txt";
	int k = rand () % 255;
	encrypt (inp, k);
	decrypt (efile, k);
}


int main(int c, char ** argv) {
	if (c != 4) {
		printf ("usage: ./sealer -e/-d inputfile key\n");
		return 1;
	}
	
	char * command = argv[1];
	char * inp = argv[2];
	int k = atoi (argv[3]);
	if (command[0] == '-' && command[1] == 'e')
		encrypt (inp, k);
	else if (command[0] == '-' && command[1] == 'd')
		decrypt (inp, k);

	return 0;
}

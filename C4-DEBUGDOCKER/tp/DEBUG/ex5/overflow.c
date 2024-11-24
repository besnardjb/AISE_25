#include <stdio.h>

void vulnerable_function() {
    char buffer[8];
	 int password_is_good = 0;
    printf("Entrez une chaîne de caractères : ");
    scanf("%s", buffer);
    printf("Vous avez entré : %s\n", buffer);
	 if(password_is_good == 98)
	 {
		printf("Vous avez cassé le MDP !");
	 }
	 else
	 {
		printf("password_is_good == %d", password_is_good);
	 }
}

int main() {
    vulnerable_function();
    return 0;
}
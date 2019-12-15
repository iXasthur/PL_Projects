%option noyywrap
%{
	#include <string.h>
	char *yytext;
	char newText[1024];
%}
%%
\n return 0;
[a-zA-Z] 	{
			char newCharacterString[2];
			strcpy(newCharacterString, " ");
			char newCharacter = yytext[0];
			switch (newCharacter) {
			case 'z': {
				newCharacter = 'a';
				break;
			}
			case 'Z': {
				newCharacter = 'A';
				break;
			}
			default: {
				newCharacter = newCharacter + 1;
				break;
			}
			}
			newCharacterString[0] = newCharacter;
			strcat(newText, newCharacterString);
		}
. 		{
			strcat(newText, yytext);
		}
%%

int main() {
	printf(">Launched analyzer!\n");
	strcpy(newText, "");
	printf(" Initial string: ");
	yylex();
	printf("  Edited string: %s\n", newText);
	printf(">Terminating analyzer!\n");
	return 0;
}
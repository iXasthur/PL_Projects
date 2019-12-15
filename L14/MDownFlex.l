%option noyywrap
%{
    #include <stdio.h>
	#include <string.h>
	char *yytext;
    FILE *yyin;
    
    char headingsList[1024];
    char boldItalicList[1024];
    char boldList[1024];
    char italicList[1024];
    char strikedList[1024];
    char markedList[1024];
    char quotedList[1024];
    char inlineList[1024];
    char linkList[1024];
    char imageList[1024];
%}
%%
^##*[ ].* {printf("Found heading: "); ECHO; strcat(headingsList, "\n         "); strcat(headingsList, yytext), printf("\n");} // Heading style 1
^[ ][ ]*#+[ ].* {printf("Found heading: "); ECHO; strcat(headingsList, "\n         "); strcat(headingsList, yytext), printf("\n");} // Heading style 2

[*]{3}.*[*]{3} {printf("Found bold italic text: "); ECHO; strcat(boldItalicList, "\n                     "); strcat(boldItalicList, yytext), printf("\n");} // Bold italic text style 1
[_]{3}.*[_]{3} {printf("Found bold italic text: "); ECHO; strcat(boldItalicList, "\n                     "); strcat(boldItalicList, yytext), printf("\n");} // Bold italic text style 2

[*]{2}.*[*]{2} {printf("Found bold text: "); ECHO; strcat(boldList, "\n             "); strcat(boldList, yytext), printf("\n");} // Bold text style 1
[_]{2}.*[_]{2} {printf("Found bold text: "); ECHO; strcat(boldList, "\n             "); strcat(boldList, yytext), printf("\n");} // Bold text style 2

[*]{1}.*[*]{1} {printf("Found italic text: "); ECHO; strcat(italicList, "\n                "); strcat(italicList, yytext), printf("\n");} // Italic text style 1
[_]{1}.*[_]{1} {printf("Found italic text: "); ECHO; strcat(italicList, "\n                "); strcat(italicList, yytext), printf("\n");} // Italic text style 2

[~]{2}.*[~]{2} {printf("Found striked text: "); ECHO; strcat(strikedList, "\n                "); strcat(strikedList, yytext), printf("\n");} // Striked text style 1

[=]{2}.*[=]{2} {printf("Found marked text: "); ECHO; strcat(markedList, "\n               "); strcat(markedList, yytext), printf("\n");} // Marked text style 1

>[ >]*.* {printf("Found quoted text: "); ECHO; strcat(quotedList, "\n               "); strcat(quotedList, yytext), printf("\n");} // Quoted text style 1

[`]{1}[^`]*[`]{1} {printf("Found inline text: "); ECHO; strcat(inlineList, "\n               "); strcat(inlineList, yytext), printf("\n");} // Inline text style 1

^[\[].*[\]]\(.*\) {printf("Found link: "); ECHO; strcat(linkList, "\n      "); strcat(linkList, yytext), printf("\n");} // Link style 1
^[ ][ ]*[\[].*[\]]\(.*\) {printf("Found link: "); ECHO; strcat(linkList, "\n      "); strcat(linkList, yytext), printf("\n");} // Link style 2

^![\[].*[\]]\(.*\) {printf("Found image: "); ECHO; strcat(imageList, "\n       "); strcat(imageList, yytext), printf("\n");} // Image style 1
^[ ][ ]*![\[].*[\]]\(.*\) {printf("Found image: "); ECHO; strcat(imageList, "\n       "); strcat(imageList, yytext), printf("\n");} // Image style 2

\n ;
. ;
<<EOF>> printf("Reached EOF\n"); return 0;
%%

int main() {
    if ((yyin = fopen("MD_Source.markdown", "r")) == NULL) {
        printf (">Cannot open file.\n");
        return 1;
    }
    strcpy(headingsList,"Headings: ");
    strcpy(boldItalicList,"Bold intalic strings: ");
    strcpy(boldList,"Bold strings: ");
    strcpy(italicList,"Intalic strings: ");
    strcpy(strikedList,"Striked strings: ");
    strcpy(markedList,"Marked strings: ");
    strcpy(quotedList,"Quoted strings: ");
    strcpy(inlineList,"Inline strings: ");
    strcpy(linkList,"Links: ");
    strcpy(imageList,"Images: ");
    
	printf(">Launched analyzer!\n");
	yylex();
    
    printf("\n---------------------------------------------------------------------------------------------------\n");
    printf("%s\n---------------------------------------------------------------------------------------------------\n",headingsList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",boldItalicList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",boldList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",italicList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",strikedList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",markedList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",quotedList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",inlineList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",linkList);
    printf("%s\n---------------------------------------------------------------------------------------------------\n",imageList);
    printf("\n");
    
	printf(">Terminating analyzer!\n");
	return 0;
}

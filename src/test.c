#include <stdio.h>
void fortune_cookie(char msg[]){
		printf("Message reads:%s\n",msg);
}
int main(){
		int x = 1;
		int *address = &x;
		int y = *address;
		printf("x 变量的地址： %p\n", address);
		printf("%d\n",y);
		char quote[] = "Cookies make you fat";
		printf("%p bytes\n",quote);
		fortune_cookie(quote);
}

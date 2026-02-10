#include <stdio.h>

int get_print_sum(int, int);
void print_chars(char, int);

int main(void)
{
	int n = 1, layers = 1, remainder = 0;
	char c = '\0';
	scanf("%d %c", &n, &c);
	// printf("%d\n", get_print_sum(n, 2));
	for (layers = 1; get_print_sum(layers + 2, 2) <= n; layers += 2);
	remainder = n - get_print_sum(layers, 2);

	int layers0 = layers;
	for (bool flag = true; layers >= 1 && layers <= layers0; layers = flag ? layers - 2 : layers + 2)
	{
		if (layers == 1) flag = false;
		print_chars(' ', (layers0 - layers) / 2);
		print_chars(c, layers);
		putchar('\n');
	}
	printf("%d\n",  remainder);

	return 0;
}

int get_print_sum(int layers, int dif)
{
	if (!(layers & 1))
		layers--;
	layers = (layers + 1) / 2;
	return 2 * (layers + 0.5 * layers * (layers - 1) * dif) - 1;
}

void print_chars(char c, int n)
{
	for (int i = 0; i < n; i++)
		printf("%c", c);
}


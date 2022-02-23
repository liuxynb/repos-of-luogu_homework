#include<stdio.h>
#include<math.h>

void judge(int n, char* win_lose);
int flag = 0;

int main(void)
{
	char c, win_lose[62505];
	int m = 0;
	while ((c = getchar()) != 'E')
		if(c=='W'||c=='L')
			win_lose[m++] = c;
	win_lose[m] = '\0';
	if (m == 0)
	{
		printf("0:0\n\n0:0");
	}
	else 
	{
		judge(11, win_lose);
		if (flag)printf("0:0\n");
		flag = 0;
		puts("");
		judge(21, win_lose);
		if (flag)printf("0:0");
	}
	return 0;
}

void judge(int n,char *win_lose)
{
	
	int cnt=0;
	while (win_lose[cnt] != '\0')
	{
		int w = 0, l = 0;// W 表示华华获得一分，L 表示华华对手获得一分
		int i = 0;
		while(1)
		{
			if (win_lose[i + cnt] == 'W')w++;
			if (win_lose[i + cnt] == 'L')l++;
			if ((w >= n || l >= n) && abs(w - l) >= 2)
			{
				i++;
				if (win_lose[i + cnt] == '\0')flag = 1;
				break;
			}
			if (win_lose[i + 1 + cnt] == '\0')
			{
				i++; 
				break;
			}			
			i++;
		}
		
		printf("%d:%d\n", w, l);
		cnt += i;
	}
	

}
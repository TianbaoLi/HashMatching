#include<cstdio>
#include<ctime>
#include<cstdlib>
const int DataLimit=(int)1e5;
using namespace std;
int main()
{
	freopen("V1.in","w",stdout);
	printf("%d\n",DataLimit);
	srand(time(NULL));
	for(int i=0;i<DataLimit;i++)
		printf("%d\n",rand());
	return 0;
}

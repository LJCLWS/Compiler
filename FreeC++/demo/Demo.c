
//求长方形面积
int res = 1;
int len,wid;

const float PI = 3.14;
//主函数
int main()
{
	int tep = 0;
	len = 5;
	wid = 3;
	tep = (wid+1)*len;
	res = tep;

	if (res < len)res = (len+wid) + res;
	else
	{
		res = 8 - len;
		res = (len + wid) + res;
	}

	return 0;
}

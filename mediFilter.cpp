void _medianfilter(const element* signal, element* result, int N, int Wsize)
{
	if (Wsize % 2 == 0)--Wsize;		//偶数的窗口大小不均匀
	int halfWs = (Wsize - 1) / 2;	//一半窗口大小
	for (int i = 0; i < N; ++i) {
		element *window = new element[Wsize];
		element data;

		if (i<halfWs) {	//左边缘
			for (int j = 0; j < Wsize; ++j) {
				window[j] = signal[j];						//邻近数据提取到窗口
			}
		}	
		else if (i >= N - halfWs) {	//右边缘
			int k = 0;
			for (int j = N - Wsize; j < N; ++j, ++k) {
				window[k] = signal[j];						//邻近数据提取到窗口
			}
		}
		else {			//中间部分
			for (int j = 0; j < Wsize; ++j) {
				window[j] = signal[i - halfWs + j];			//邻近数据提取到窗口
			}
		}

		for (int j = 0; j <= halfWs; ++j) {		//窗口内进行排序 排一半即可
												//丢弃做法
			int pos = j;
			for (int k = j + 1; k < Wsize; ++k)
				if (window[k] < window[pos]) {
					pos = k;
				}
			data = window[pos];
			window[pos] = UINT32_MAX;
		}

		result[i] = data;

		delete window;
	}
}
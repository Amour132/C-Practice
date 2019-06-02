#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

//leetcode 5 ������Ӵ�///////////////////////////////////////////////////////////////
string longestPalindrome(string s) {
	vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), 0));
	if (s.size() == 0 || s.size() == 1)
		return s;
	int start = 0; //��¼���
	int max = 1; //��¼������󳤶�

	//�ȳ�ʼ���������ַ����ǻ��Ĵ����������������ȵ�����Ҳ�ǻ���
	for (int i = 0; i < s.size(); i++)
	{
		dp[i][i] = 1;
		if (i < s.size() - 1 && s[i] == s[i + 1])
		{
			dp[i][i + 1] = 1;
			max = 2;
			start = i;
		}
	}
	//�ӳ���Ϊ3���ִ���ʼ�ж�
	for (int len = 3; len <= s.size(); len++)
	{
		for (int i = 0; i + len - 1 < s.size(); i++)
		{
			int j = i + len - 1;
			if (s[i] == s[j] && dp[i + 1][j - 1])//�ǻ���
			{
				dp[i][j] = 1;
				start = i;
				max = len;
			}
		}
	}
	return s.substr(start, max);
}

//leetcode 53 ��������еĺ�///////////////////////////////////////////////////////////////

int maxSubArray(vector<int>& nums) {
	if (nums.size() == 0)
		return 0;
	int max = nums[0];
	int sum = nums[0];
	for (int i = 1; i < nums.size(); i++)
	{
		if (sum < 0)  // һ����Ϊ���������¿�ʼ��¼
			sum = nums[i];
		else
			sum += nums[i];
		if (max < sum)
			max = sum;

	}
	return max;
}

//leetcode 62 ��ͬ·��///////////////////////////////////////////////////////////////

int uniquePaths(int m, int n) {
	//��¼��ÿһ�����ӵ�·����
	vector<vector<int>> dp(m, vector<int>(n, 0));
	//��ʼ����һ�к͵�һ�еĸ���ֻ��һ��·��
	for (int i = 0; i < m; i++)
	{
		dp[i][0] = 1;
	}
	for (int j = 0; j < n; j++)
	{
		dp[0][j] = 1;
	}
	//��ǰ���ӵ�·��= �� + �Ϸ�
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}


//leetcode 63 ��ͬ·��2///////////////////////////////////////////////////////////////

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	vector<vector<long long>> dp(m, vector<long long>(n, 0));
	if (obstacleGrid[0][0] == 1)
		return 0;
	//��Ȼ�ǳ�ʼ����һ�к͵�һ�У�����һ�������ϰ������޷��������Ķ�Ҫ��Ϊ0
	for (int i = 0; i < m; i++)
	{
		if (obstacleGrid[i][0] == 0)
			dp[i][0] = 1;
		else
			break;
	}
	for (int j = 0; j < n; j++)
	{
		if (obstacleGrid[0][j] == 0)
			dp[0][j] = 1;
		else
			break;
	}
	//��ǰ·�� = ��� + �ϱ�;��Ҫע���ж��ϰ��һ��������Ϊ0
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (obstacleGrid[i][j] == 0)
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			else
				dp[i][j] = 0;
		}
	}
	return dp[m - 1][n - 1];
}

//leetcode 64 ��С·����///////////////////////////////////////////////////////////////

int minPathSum(vector<vector<int>>& grid) {
	int m = grid.size();
	int n = grid[0].size();
	vector<vector<int>> dp(m, vector<int>(n, 0));
	//������ÿһ�������·���ͱ��档
	dp[0][0] = grid[0][0];
	for (int i = 1; i < m; i++)
	{
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	}
	for (int j = 1; j < n; j++)
	{
		dp[0][j] = dp[0][j - 1] + grid[0][j];
	}
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
		}
	}
	return dp[m - 1][n - 1];
}

//leetcode 91 ���뷽ʽ	///////////////////////////////////////////////////////////////

int numDecodings(string s) {
	if (s.size() == 0)
		return 0;
	vector<long long> dp(s.size() + 1, 0);
	dp[0] = 1;
	for (int i = 1; i < s.size() + 1; i++)
	{
		if (s[i - 1] != '0')
			dp[i] += dp[i - 1];
		//����1 ��˵�����Խ������
		if (i > 1)
		{
			//�õ������ַ���ϳɵ�ֵ
			int num = (s[i - 2] - '0') * 10 + s[i - 1] - '0';
			if (num == 0)
				return 0;
			//�ڱ�ʾ��Χ�ھͼ���֮ǰ�����ֵ 
			if (num > 9 && num < 27)
				dp[i] += dp[i - 2];
		}
	}
	return dp[s.size()];
}

//leetcode 139 ���ʲ��///////////////////////////////////////////////////////////////

bool wordBreak(string s, vector<string>& wordDict) {
	vector<bool> dp(s.size() + 1, false);

	dp[0] = true;

	for (int i = 1; i < s.size() + 1; i++)
	{
		//���ֵ��ÿһ�����ʺ�s���ִ�����ƥ��
		for (int j = 0; j < wordDict.size(); j++)
		{
			string ret = wordDict[j];
			//ƥ��ɹ���˵�����Բ��
			if (i >= ret.size() && ret == s.substr(i - ret.size(), ret.size()))
				dp[i] = dp[i] || dp[i - ret.size()];
		}
	}
	return dp[s.size()];
}

int main()
{
	return 0;
}
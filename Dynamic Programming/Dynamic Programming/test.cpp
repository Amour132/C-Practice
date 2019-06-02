#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

//leetcode 5 最长回文子串///////////////////////////////////////////////////////////////
string longestPalindrome(string s) {
	vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), 0));
	if (s.size() == 0 || s.size() == 1)
		return s;
	int start = 0; //记录起点
	int max = 1; //记录回文最大长度

	//先初始化，单个字符都是回文串，如果遇到连续相等的两个也是回文
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
	//从长度为3的字串开始判断
	for (int len = 3; len <= s.size(); len++)
	{
		for (int i = 0; i + len - 1 < s.size(); i++)
		{
			int j = i + len - 1;
			if (s[i] == s[j] && dp[i + 1][j - 1])//是回文
			{
				dp[i][j] = 1;
				start = i;
				max = len;
			}
		}
	}
	return s.substr(start, max);
}

//leetcode 53 最大子序列的和///////////////////////////////////////////////////////////////

int maxSubArray(vector<int>& nums) {
	if (nums.size() == 0)
		return 0;
	int max = nums[0];
	int sum = nums[0];
	for (int i = 1; i < nums.size(); i++)
	{
		if (sum < 0)  // 一旦和为负数则重新开始记录
			sum = nums[i];
		else
			sum += nums[i];
		if (max < sum)
			max = sum;

	}
	return max;
}

//leetcode 62 不同路径///////////////////////////////////////////////////////////////

int uniquePaths(int m, int n) {
	//记录到每一个格子的路线数
	vector<vector<int>> dp(m, vector<int>(n, 0));
	//初始化第一行和第一列的格子只有一种路径
	for (int i = 0; i < m; i++)
	{
		dp[i][0] = 1;
	}
	for (int j = 0; j < n; j++)
	{
		dp[0][j] = 1;
	}
	//当前格子的路径= 左方 + 上方
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}


//leetcode 63 不同路径2///////////////////////////////////////////////////////////////

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	vector<vector<long long>> dp(m, vector<long long>(n, 0));
	if (obstacleGrid[0][0] == 1)
		return 0;
	//仍然是初始化第一行和第一列，但是一旦出现障碍物则无法到达，后面的都要变为0
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
	//当前路径 = 左边 + 上边;但要注意判断障碍物，一旦出现则为0
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

//leetcode 64 最小路径和///////////////////////////////////////////////////////////////

int minPathSum(vector<vector<int>>& grid) {
	int m = grid.size();
	int n = grid[0].size();
	vector<vector<int>> dp(m, vector<int>(n, 0));
	//将到达每一处的最短路径和保存。
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

//leetcode 91 解码方式	///////////////////////////////////////////////////////////////

int numDecodings(string s) {
	if (s.size() == 0)
		return 0;
	vector<long long> dp(s.size() + 1, 0);
	dp[0] = 1;
	for (int i = 1; i < s.size() + 1; i++)
	{
		if (s[i - 1] != '0')
			dp[i] += dp[i - 1];
		//大于1 则说明可以进行组合
		if (i > 1)
		{
			//拿到两个字符组合成的值
			int num = (s[i - 2] - '0') * 10 + s[i - 1] - '0';
			if (num == 0)
				return 0;
			//在表示范围内就加上之前保存的值 
			if (num > 9 && num < 27)
				dp[i] += dp[i - 2];
		}
	}
	return dp[s.size()];
}

//leetcode 139 单词拆分///////////////////////////////////////////////////////////////

bool wordBreak(string s, vector<string>& wordDict) {
	vector<bool> dp(s.size() + 1, false);

	dp[0] = true;

	for (int i = 1; i < s.size() + 1; i++)
	{
		//将字典的每一个单词和s的字串进行匹配
		for (int j = 0; j < wordDict.size(); j++)
		{
			string ret = wordDict[j];
			//匹配成功则说明可以拆分
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
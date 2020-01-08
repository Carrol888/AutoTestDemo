//
//  DDSolution.c
//  AutoTestDemo
//
//  Created by 冯砚伟 on 2020/1/3.
//  Copyright © 2020 冯砚伟. All rights reserved.
//

#include "DDSolution.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// 暴力破解法
//判断一个字符串是不是回文
int IfPlalindrome(char *s) {
    int count = strlen(s);
    int left = 0;
    int right = count - 1;
    while (left < right)
    {
        if (s[left] != s[right])
        {
            return 0; //不是回文返回0，是回文返回1
        }
        left++;
        right--;
    }
    return 1;
}
//反转字符串
char *reverse(char *s, int count)
{
    char *p = (char *)malloc(sizeof(char) * (count + 1));
    int i = 0;
    for (; i < count; i++)
    {
        p[i] = s[count - i - 1];
    }
    p[i] = '\0';
    return p;
}
    
char* longestPalindrome(char* s) {
    int count = strlen(s);
    //arr中存放的是最长的回文子串
    char *arr = (char *)malloc(sizeof(char) * 1001);
    char *p = reverse(s, count);
    unsigned int max = 0;
    //arr1中存放每一次循环遇见的回文子串
    char arr1[2000];
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            int m = i;
            int n = j;
            int k = 0;
            while (s[m] == p[n])
            {
                arr1[k] = s[m];
                k++;
                m++;
                n++;
            }
            arr1[k] = '\0';
            //判断是不是回文子串
            if (IfPlalindrome(arr1))
            {
                //和arr中的回文子串长度作对比，大的话，就更新
                if (strlen(arr1) > max)
                {
                    max = strlen(arr1);
                    strcpy(arr, arr1);
                }
            }
        }
    }
    return arr;
}


// 动态规划法
char* dpLongestPalindrome(char* s)
{
    int len = strlen(s);
    if (len <= 1) { return s; }
    //定义bool类型的dp，只能为true或false
    bool dp[1001][1001];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i < len; i++)
    {
        dp[i][i] = true;
        //一定不要忽略，在下面k=2会用到
        dp[i][i - 1] = true;
    }
    int left = 0;
    int right = 0;
    int max = 0;
    //k表示回文子串的长度
    for (int k = 2; k <= len; k++)
    {
        //i表示回文子串的起始位置
        for (int i = 0; i < len - k + 1; i++)
        {
            if (s[i] == s[k - 1 + i] && dp[i + 1][k + i - 2])
            {
                dp[i][k - 1 + i] = true;
                if (max < k - 1)
                {
                    max = k - 1;
                    left = i;
                    right = k - 1 + i;
                }
            }
        }
    }
   
    char *arr = (char *)malloc(sizeof(int) * (max * 2));
    int i = 0;
    for (; i <= max; i++)
    {
        arr[i] = s[left++];
    }
    arr[i] = '\0';
    return arr;
}


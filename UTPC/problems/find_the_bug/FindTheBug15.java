
import java.io.*;
import java.util.*;

/**
 * 
 * Problem statement:
 * Given an array of 1<=n<=51 integers between -1e9 and 1e9,
 * count the number of longest (strictly) increasing subsequences.
 * Output this number modulo 1e9+7.
 * 
 * Sample Input:
 * 5
 * 1 3 2 2 5
 * Answer:
 * 3
 * Explanation:
 * The 3 longest increasing subsequences are [1 3 5], [1 2 5], and [1 2 5].
 *
 *
 * This problem should be a pretty straightforward dp, but I'm not sure where my bug is.
 * Maybe an off-by-one error somewhere...?
 * Help me find a test case that I fail on!
 * 
 */
public class Solution {
	
	static final long MOD = 100000009;
	
	public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        
        int[] nums = new int[n];
        for(int i = 0; i < n; i++) {
        	nums[i] = in.nextInt();
        }
        
        //dp[i] = number of maximum length increasing subsequences ending at nums[i]
        long[] dp = new long[n];
        
        //len[i] = maximum length of increasing subsequence ending at nums[i]
        int[] len = new int[n];
        
        //longest increasing subsequence we've seen
        int mxLen = 0;
        for(int i = 0; i < n; i++) {
            len[i] = 1;
            dp[i] = 1;
            for(int j = 0; j < i; j++) {
                if(nums[j] < nums[i]) {
                	//longer increasing subsequence(s) found
                    if(len[j]+1 > len[i]) {
                        len[i] = len[j]+1;
                        dp[i] = dp[j];
                    }
                    //same length increasing subsequence(s) found
                    else if(len[j]+1 == len[i]) {
                        dp[i] += dp[j];
                        dp[i] %= MOD;
                    }
                }
            }
            mxLen = Math.max(mxLen, len[i]);
        }
        long ans = 0;
        for(int i = 0; i < n; i++) {
            if(len[i] == mxLen) {
                ans += dp[i];
                ans %= MOD;
            }
        }

        System.out.println(ans);
    }
}
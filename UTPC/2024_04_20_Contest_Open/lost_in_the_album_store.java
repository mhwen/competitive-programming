import java.util.*;
import java.io.*;

public class Solution {
	
	static final long INF = (long)1e18;

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		long[][] grid = new long[n][m];
		for(int r = 0; r < n; r++) {
			st = new StringTokenizer(in.readLine());
			for(int c = 0; c < m; c++) {
				grid[r][c] = Integer.parseInt(st.nextToken());
			}
		}
		long[][] up = new long[n][m];
		long[][] left = new long[n][m];
		for(int r = 0; r < n; r++) {
			for(int c = 1; c < m; c++) {
				left[r][c] = left[r][c-1]+grid[r][c-1];
			}
		}
		for(int c = 0; c < m; c++) {
			for(int r = 1; r < n; r++) {
				up[r][c] = up[r-1][c]+grid[r-1][c];
			}
		}
		
		long[][] dp = new long[n][m];
		for(int r = n-1; r >= 0; r--) {
			for(int c = m-1; c >= 0; c--) {
				if(r != n-1 || c != m-1)
					dp[r][c] = INF;
				if(c < m-1)
					dp[r][c] = Math.min(dp[r][c], left[r][c]*left[r][c]+dp[r][c+1]);
				if(r < n-1)
					dp[r][c] = Math.min(dp[r][c], up[r][c]*up[r][c]+dp[r+1][c]);
			}
		}
		System.out.println(dp[0][0]);
	}
}
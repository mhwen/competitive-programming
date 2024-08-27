import java.util.*;
import java.io.*;

public class Solution {

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		long[] vals = new long[(int)2e5+1];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(in.readLine());
			String s = st.nextToken();
			long val = Long.parseLong(st.nextToken());
			vals[s.length()] = Math.max(vals[s.length()], val);
		}
		long[] dp = new long[m+1];
		for(int i = 1; i <= 2e5; i++) {
			if(vals[i] == 0)
				continue;
			for(int cap = i; cap <= m; cap++) {
				dp[cap] = Math.max(dp[cap], dp[cap-i]+vals[i]);
			}
		}
		System.out.println(dp[m]);
	}
}
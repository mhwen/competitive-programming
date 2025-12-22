import java.util.*;
import java.io.*;

public class Solution {
	
	static int MAX_VAL = (int)1e6;

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(in.readLine());
		Integer[] nums = new Integer[n];
		StringTokenizer st = new StringTokenizer(in.readLine());
		int[] count = new int[MAX_VAL+1];
		for(int i = 0; i < n; i++) {
			int a = Integer.parseInt(st.nextToken());
			count[a]++;
		}
		long ans = 0;
		int remaining = n;
		for(int i = 1; i <= MAX_VAL; i++) {
			if(count[i] > 0) {
				ans += remaining;
				remaining -= count[i];
			}
		}
		System.out.println(ans);
	}
}
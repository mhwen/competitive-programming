import java.util.*;
import java.io.*;

public class Solution {

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(in.readLine());
		Integer[] nums = new Integer[n];
		StringTokenizer st = new StringTokenizer(in.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		int index = 0;
		int curr = -1;
		long ans = 0;
		while(index < n) {
			curr = nums[index];
			ans += (n-index);
			while(index < n && nums[index] == curr)
				index++;
		}
		System.out.println(ans);
	}
}